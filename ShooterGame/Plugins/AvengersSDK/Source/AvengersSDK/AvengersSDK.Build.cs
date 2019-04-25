// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class AvengersSDK : ModuleRules
{
	public AvengersSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Json",
                "JsonUtilities",
                "Http"
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "CoreUObject",
                "Json",
                "JsonUtilities",
                "Http",
                "Engine",
                "ImageWrapper",
                "RenderCore",
                "RHI",
                "ShaderCore",
                "Slate",
                "SlateCore",
                "InputCore",
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "D3D11RHI" });
        }

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string ModulePath = ModuleDirectory;
            string MyBinaryPath = Path.Combine(ModulePath, "../../Binaries", "Win64");

            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(MyBinaryPath, "CrashClientHelper.exe")));
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(MyBinaryPath, "CrashClientHelper.ini")));
        }

        PublicAdditionalLibraries.Add("Shlwapi.lib");
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Private//Api//ThirdParty//patch_win32.lib"));

        Definitions.Add("_CRT_SECURE_NO_WARNINGS");

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{			
			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private//Api//ThirdParty//Distorm"));
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "Private//Api//ThirdParty//Distorm"));
			PublicAdditionalLibraries.Add("distorm.lib");
		}
    }
}
