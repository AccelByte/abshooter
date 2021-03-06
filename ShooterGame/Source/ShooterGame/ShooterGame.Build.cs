// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ShooterGame : ModuleRules
{
	public ShooterGame(ReadOnlyTargetRules Target) : base(Target)
	{
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Error;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/ShooterGame.h";
		//Definitions.Add("UE_ENGINE_DIRECTORY=F:/UE4/UE_4.21/Engine/");

		PrivateIncludePaths.AddRange(
			new string[] { 
				"ShooterGame/Private",
				"ShooterGame/Private/UI",
				"ShooterGame/Private/UI/Menu",
				"ShooterGame/Private/UI/Style",
				"ShooterGame/Private/UI/Widgets",
				"ShooterGame/Private/Models",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"EngineSettings",
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
				"AssetRegistry",
				"NavigationSystem",
				"AIModule",
				"GameplayTasks",
				"Http",
				"InputCore",
				"JsonUtilities",
				"WebBrowser",
				"AccelByteUe4Sdk",
				"Icmp",
				"UMG"
			}
		);


        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
            // Only add steam for windows
            PublicDependencyModuleNames.AddRange(
            new string[] {               
                "OnlineSubsystemSteam",
                "Steamworks",
			}
        );
        }


            PrivateDependencyModuleNames.AddRange(
			new string[] {
				"InputCore",
				"Slate",
				"SlateCore",
				"ShooterGameLoadingScreen",
				"Json",
				"ApplicationCore",
				"ReplicationGraph",
				"AccelByteUe4Sdk",
				"Networking",
				"Sockets",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"OnlineSubsystemNull",
				"NetworkReplayStreaming",
				"NullNetworkReplayStreaming",
				"HttpNetworkReplayStreaming",
				"LocalFileNetworkReplayStreaming"
			}
		);

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"NetworkReplayStreaming",				
			}
		);

		if (Target.bBuildDeveloperTools || (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Configuration != UnrealTargetConfiguration.Test))
		{
			PrivateDependencyModuleNames.Add("GameplayDebugger");
			PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=1");
		}
		else
		{
			PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=0");
		}


		// Accelbyte SDK
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "AccelByteUe4Sdk/Public"), });
		//PublicIncludePaths.AddRange(new string[] { "AvengersSDK" });   
	}
}
