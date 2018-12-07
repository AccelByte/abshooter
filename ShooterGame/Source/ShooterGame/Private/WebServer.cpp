// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

//#include "UnrealEdRemotePrivatePCH.h"
#include "WebServer.h"
#include "Runtime/Core/Public/Misc/CString.h"
#include "GameDelegates.h"

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
		Listener = new FTcpListener(DEFAULT_ENDPOINT);
		Listener->OnConnectionAccepted().BindRaw(this, &FWebServer::HandleListenerConnectionAccepted);
		Stopping = false;
        UE_LOG(LogTemp, Log, TEXT("Web server started...On port 8080"));
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
                TArray<FString> Out;
                Request.ParseIntoArray(Out, TEXT("\n"));
                FString URL = TEXT("");
                for (int i = 0; i < Out.Num(); i++)
                {   
                    FString currentHeader = Out[i];
                    if (currentHeader.Contains("GET /"))
                    {
                        currentHeader = currentHeader.Replace(TEXT("GET /"), TEXT("/"));
                        int32 stop = currentHeader.Find(TEXT("HTTP/"))-1;
                        currentHeader = currentHeader.Left(stop);
                        URL = currentHeader;
                        break;
                    }
                }

                TMap<FString, FString> Response;
                FGameDelegates::Get().GetWebServerActionDelegate().ExecuteIfBound(0, TEXT("GET"), URL, TMap<FString, FString>(), Response);
                FString ResponseString = FString::Printf(TEXT("HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n%s"), *Response[TEXT("Content-Type")], *Response[TEXT("Body")]);
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