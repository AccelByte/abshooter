// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

using UnrealBuildTool;
using System.IO;

public class CrashTracker : ModuleRules
{
	public CrashTracker(ReadOnlyTargetRules Target) : base(Target)
    {
		PrivateIncludePaths.Add("Private");

		PublicDependencyModuleNames.Add("Core");

		PrivateDependencyModuleNames.AddRange(
			new string[] {
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
            string MyBinaryPath = Path.Combine(ModulePath, "../Binaries", "Win64");

            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(MyBinaryPath, "CrashClientHelper.exe")));
			RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(MyBinaryPath, "CrashClientHelper.ini")));
		}

    }
}