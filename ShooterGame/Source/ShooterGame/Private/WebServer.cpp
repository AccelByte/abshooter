// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

//#include "UnrealEdRemotePrivatePCH.h"
#include "WebServer.h"
#include "Runtime/Core/Public/Misc/CString.h"
#include "GameDelegates.h"
#include "Server/ServerConfig.h"
#include "ShooterGameConfig.h"

FWebServer::FWebServer()
	: Listener(NULL), Thread(NULL)
{
	Thread = FRunnableThread::Create(this, TEXT("FWebServer"), 8 * 1024, TPri_Normal);
}

FWebServer::~FWebServer()
{
	Stop();

	// Stop accepting clients first
	if (Listener != NULL)
	{
		Listener->Stop();
		delete Listener;
		Listener = NULL;
	}

	// Kill all pending connections and current connections
	if (!PendingClients.IsEmpty())
	{
		FSocket *Client = NULL;
		while (PendingClients.Dequeue(Client))
		{
			Client->Close();
		}
	}
	for (TArray<class FSocket*>::TIterator ClientIt(Clients); ClientIt; ++ClientIt)
	{
		(*ClientIt)->Close();
	}

	// And last but not least stop the main thread
	if (Thread != NULL)
	{
		Thread->Kill(true);
		delete Thread;
	}
}

bool FWebServer::HandleListenerConnectionAccepted(class FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint)
{
	PendingClients.Enqueue(ClientSocket);
	return true;
}

bool FWebServer::Init()
{
	if (Listener == NULL)
	{
			uint16 ServerPort = ShooterGameConfig::Get().ServerPort_;
			Listener = new FTcpListener(FIPv4Endpoint(FIPv4Address(0, 0, 0, 0), ServerPort));
			Listener->OnConnectionAccepted().BindRaw(this, &FWebServer::HandleListenerConnectionAccepted);
			Stopping = false;
			UE_LOG(LogTemp, Log, TEXT("Web server started...On port %i"), ServerPort);
	}
	return (Listener != NULL);
}

/** Send a string message over to a socket */
bool SendMessage(FSocket *Socket, const FString& Message)
{
	check(Socket);
	int32 BytesSent = 0;
	return Socket->Send((uint8*)TCHAR_TO_UTF8(*Message), Message.Len(), BytesSent);
}

/** Receive a string message from a socket */
bool RecvMessage(FSocket *Socket, uint32 DataSize, FString& Message)
{
	check(Socket);

	FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
	Datagram->Init(FMath::Min(DataSize, 65507u), 500);

	int32 BytesRead = 0;
	if (Socket->Recv(Datagram->GetData(), Datagram->Num(), BytesRead))
	{
		char* Data = (char*)Datagram->GetData();
		Data[BytesRead] = '\0';
		Message = UTF8_TO_TCHAR(Data);
		return true;
	}
	return false;
}

static FString DefaultResponseCode = "200";
static TMap<FString, FString> HttpCodesMap =
{
	{"200", "OK"},
	{"201", "Created"},
	{"202", "Accepted"},
	{"203", "Non-Authoritative Information"},
	{"204", "No Content"},
	{"205", "Reset Content"},
	{"206", "Partial Content"},
	{"207", "Multi-Status"},
	{"208", "Already Reported"},
	{"300", "Multiple Choices"},
	{"301", "Moved Permanently"},
	{"302", "Found"},
	{"303", "See Other"},
	{"304", "Not Modified"},
	{"305", "Use Proxy"},
	{"306", "Switch Proxy"},
	{"307", "Temporary Redirect"},
	{"308", "Permanent Redirect"},
	{"400", "Bad Request"},
	{"401", "Unauthorized"},
	{"402", "Payment Required"},
	{"403", "Forbidden"},
	{"404", "Not Found"},
	{"405", "Method Not Allowed"},
	{"406", "Not Acceptable"},
	{"407", "Proxy Authentication Required"},
	{"408", "Request Timeout"},
	{"409", "Conflict"},
	{"410", "Gone"},
	{"500", "Internal Server Error"},
	{"501", "Not Implemented"},
	{"502", "Bad Gateway"},
	{"503", "Service Unavailable"},
	{"504", "Gateway Timeout"},
	{"505", "HTTP Version Not Supported"},
};

uint32 FWebServer::Run()
{
	
	while (!Stopping)
	{
		if (!PendingClients.IsEmpty())
		{
			FSocket *Client = NULL;
			while (PendingClients.Dequeue(Client))
			{
				Clients.Add(Client);
			}
		}

		// remove closed connections
		for (int32 ClientIndex = Clients.Num() - 1; ClientIndex >= 0; --ClientIndex)
		{
			if (Clients[ClientIndex]->GetConnectionState() != SCS_Connected)
			{
				Clients.RemoveAtSwap(ClientIndex);
			}
		}

		// Poll data from every connected client
		for (TArray<class FSocket*>::TIterator ClientIt(Clients); ClientIt; ++ClientIt)
		{
			FSocket *Client = *ClientIt;
			uint32 DataSize = 0;
            FString Request = TEXT("");
			while (Client->HasPendingData(DataSize))
			{				
                FString Chunk;
				if (RecvMessage(Client, DataSize, Chunk))
				{                    
                    Request.Append(Chunk);
				}
			}

            if (!Request.IsEmpty())
            {
				FString URL = TEXT("/");
				FString Action;
				TMap<FString, FString> Params;
				FString Header;

				int32 pos = Request.Find("\r\n\r\n");
				if (pos > 0)
				{
					Header = Request.Left(pos);
					Params.Add("Body", Request.RightChop(pos + 4));
				}
				else
				{
					Header = Request;
				}

                TArray<FString> Out;
				Header.ParseIntoArray(Out, TEXT("\r\n"));

				FString currentLine = Out[0];
				pos = currentLine.Find(" ");
				Action = currentLine.Left(pos);

				int32 start = pos + 1;
				pos = currentLine.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromStart, start);
				URL = currentLine.Mid(start, pos - start);

                for (int i = 1; i < Out.Num(); i++)
                {   
					if (currentLine.Len() == 0) break;

					currentLine = Out[i];
					pos = currentLine.Find(":") + 1;
					while (currentLine[pos] == L' ') ++pos;
					Params.Add(currentLine.Left(pos), currentLine.RightChop(pos));
                }
                TMap<FString, FString> Response;
                FGameDelegates::Get().GetWebServerActionDelegate().ExecuteIfBound(0, Action, URL, Params, Response);
				FString ResponseCode;
				Response.RemoveAndCopyValue(TEXT("Code"), ResponseCode);
				FString* ResponseCodeName = nullptr;
				if (ResponseCode.IsEmpty())
				{
					ResponseCode = DefaultResponseCode;
				}
				ResponseCodeName = HttpCodesMap.Find(ResponseCode);

				FString StringHeaders = "";
				FString ContentBody;
				Response.RemoveAndCopyValue(TEXT("Body"), ContentBody);
				for (const TPair<FString, FString>& KeyValue : Response)
				{
					StringHeaders.Append(FString::Printf(TEXT("%s: %s\r\n"), *KeyValue.Key, *KeyValue.Value));
				}
				StringHeaders.RemoveFromEnd(TEXT("\r\n"));

                FString ResponseString = FString::Printf(TEXT("HTTP/1.0 %s %s\r\n%s\r\n\r\n%s"), 
					*ResponseCode,
					**ResponseCodeName,
					*StringHeaders,
					*ContentBody);
                SendMessage(Client, ResponseString);
            }
            Client->Close();
		}

		FPlatformProcess::Sleep(0.2f);
	}

	return 0;
}

FString FWebServer::HandleClientMessage(const FSocket *Socket, const FString& Message)
{
	bool bProcessed = false;
	FString Response;

	const TCHAR* Cmd = *Message;
	if (FParse::Command(&Cmd, TEXT("EXEC")) && HandleExecCommand(Socket, Message.Mid(FCString::Strlen(TEXT("CMD")))))
	{
		bProcessed = true;
	}

	return bProcessed ? TEXT("OK") : TEXT("FAILED");
}

bool FWebServer::HandleExecCommand(const FSocket *Socket, const FString& Command)
{
	if (GEngine != NULL)
	{
		GEngine->DeferredCommands.Add(Command);
		return true;
	}
	return false;
}