# AccelByte UE4 Sample Project

## Overview
Using UE4 Version 4.25.3
Using AccelByte Services SDK Version 2.34.0

[Shooter Game](https://docs.unrealengine.com/en-US/Resources/SampleGames/ShooterGame/index.html) is an example of a PC multiplayer first-person shooter from [Epic Games](https://www.epicgames.com/). We are using this sample game to integrate AccelByte’s services we add new menus to show chasing each service available.
The game project test running on UE4 version 4.25.3 If you are going to build a game server also then we recommend using UE4 version 4.25.3 from source. If you are only going to build a game client then UE4 version 4.25.3 from Epic Launcher is faster to set up.
We are using UMG for some menus and some slate from the original shooter game.
The menu that using UMG currently are :
- Login Menu (ShooterGame\Source\ShooterGame\Private\UI\UMG\LoginMenuUI.cpp)
- Main Menu
- Lobby Menu
- Login Menu
- Game Profile Menu
- Gallery Menu

We are still on the progress of migrating the current slate menu to UMG. The next update will be covering these following menus:
- Inventory Menu
- Store Menu
- Setting Menu

## Prerequisites

### Install Visual Studio 2017
Include Game Development with C++.
[Setting up VS for UE4](https://docs.unrealengine.com/en-US/Programming/Development/VisualStudioSetup/index.html)

### Install Windows 10 SDK
Version 4.21 needs 10.0.17xxx.xx & early.
Version 4.23 and above needs 10.0.18xxx.xx.
[Windows 10 SDK archive](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/)

### Install Git LFS
[Git LFS Download Link](https://git-lfs.github.com/)

### Install Clang for Cross-Compiling Linux
To build Linux Client and Linux Server in Windows 10 OS we will need to Install clang version 9.0.1-based for Unreal Engine 4 version 4.25 more to it on UE4 - [Cross-Compiling for Linux.](https://docs.unrealengine.com/en-US/SharingAndReleasing/Linux/AdvancedLinuxDeveloper/LinuxCrossCompileLegacy/index.html)
[Clang version 9.0.1-based Download Link](http://cdn.unrealengine.com/CrossToolchain_Linux/v16_clang-9.0.1-centos7.exe)

### Install UE4
The game project will only work on UE4 version 4.25.3 If you are going to build a game server also then we recommend using UE4 version 4.25.3 from source. If you are only going to build a game client then UE4 version 4.25.3 from Epic Launcher is faster to set up.

#### Install UE4 Version 4.25 from Source (recommended)
Several of these steps may take some time to complete. Some of the steps typically take over an hour, depending on your computer and the speed of your Internet connection. Some non-SSD computers will take more than 2 hours or more to setup.

`1.` Clone UE4 source code from Epic Github repository check on [How to Access Unreal Engine 4 C++ source code via GitHub](https://www.unrealengine.com/ue4-on-github) for details.

`2.` Switch your local branch pointing to 4.25.3-release tag.

`3.` Run Setup.bat (Run this as Administrator).

`4.` Run GenerateProjectFiles.bat (Run this as Administrator also). By default GenerateProjectFiles.bat will create project files for VS2017. `GenerateProjectFiles.bat`

`5.` Launch UE4.sln to open project solution in VS 2017.

`6.` Make sure in configuration manager, active solution configuration is set to Development Editor and active solution platform is set to Win64

`7.` Set the startup projects to UE4 by right click on the UE4 project then Set as Startup Project

`8.` Then again right click on UE4 project and build to start the build process.


Note: Visual Studio 2015 and earlier are no longer supported for UE4 4.15 or later, more info on [UE4 - Visual Studio Setup](https://docs.unrealengine.com/en-US/Programming/Development/VisualStudioSetup/index.html).

#### Install UE4 Version 4.25.3 from Epic Launcher
Follow along with Unreal Engine Installation Documentation [Here](https://docs.unrealengine.com/en-US/GettingStarted/Installation/index.html). Select 4.25.3 as the version to download.

## The Sample Game Project
### The Setup

`1.` Clone or download AB Shooter project from [AccelByte's Public Github](https://github.com/AccelByte/abshooter).

`2.` Right after cloning, switch the unreal engine version to the one that you have downloaded by right click and `switch engine version`, then select the one that you have prepared before. Note that It will take several seconds to complete.

`3.` Set the SDK configuration on `ShooterGame\config\defaultengine`.ini by filling client ID and Client secret for both game client and server. Look for `[/Script/AccelByteUe4Sdk.AccelByteSettings]` for game client config and `[/Script/AccelByteUe4Sdk.AccelByteServerSettings]` for game server config.
Alternatively, you could also set the configuration within the Unreal Editor by going to Edit dropdown menu -> Project Settings -> Plugins Section then Look for AccelByte Unreal Engine 4 Client SDK for Game client config and AccelByte Unreal Engine 4 Server SDK for Game Server config.

Game Client Configuration
``` cpp
[/Script/AccelByteUe4Sdk.AccelByteSettings]
ClientId=CONTACT-US
ClientSecret=CONTACT-US
Namespace=abshooter
RedirectURI="http://127.0.0.1"
PublisherNamespace=accelbyte
IamServerUrl="https://api.demo.accelbyte.io/iam"
PlatformServerUrl="https://api.demo.accelbyte.io/platform"
LobbyServerUrl="wss://demo.accelbyte.io/lobby/"
BasicServerUrl="https://api.demo.accelbyte.io/basic"
CloudStorageServerUrl="https://api.demo.accelbyte.io/binary-store"
GameProfileServerUrl="https://api.demo.accelbyte.io/soc-profile"
StatisticServerUrl="https://api.demo.accelbyte.io/statistic"
QosManagerServerUrl="https://api.demo.accelbyte.io/qosm"
LeaderboardServerUrl="https://api.demo.accelbyte.io/leaderboard"
GameTelemetryServerUrl="https://api.demo.accelbyte.io/game-telemetry"
```

Game Server Configuration
``` cpp
[/Script/AccelByteUe4Sdk.AccelByteServerSettings]
ClientSecret=CONTACT-US
ClientId=CONTACT-US
Namespace=abshooter
PublisherNamespace=accelbyte
RedirectURI="http://127.0.0.1"
IamServerUrl="https://demo.accelbyte.io/iam"
DSMServerUrl="http://justice-dsm-service/dsm"
StatisticServerUrl="https://demo.accelbyte.io/statistic"
PlatformServerUrl="https://demo.accelbyte.io/platform"
```

`4.` Open the shooter game project solution ShooterGame.sln 

`5.` Make sure in configuration manager, active solution configuration is set to Development Editor and active solution platform is set to Win64.

`6.` Set the startup projects to ShooterGame by right click on the ShooterGame project then Set as Startup Project

`7.` Then again right click on ShooterGame project and build to start the build process.

`8.` Kick start the project by running it from VS IDE, click on Local Windows Debugger button, or go to the windows explorer and run ShooterGame\ShooterGame.uproject. 

### Packaging Game Client Build
There are 2 types of build based on how its build :
- Cooked : The game build along with cooked package, all assets are packaged inside the build, and the game is able to run by itself (without editor).
- UnCooked : The game build without the cooked asset, the game essentially run using the editor, all the asset is provided by editor. This type of build is the output from Visual Studio.
There are two ways of build the Cooked version of game build, by CLI and Editor. See more about build operation [UE4 - Build Operations: Cook, Package, Deploy, and Run](https://docs.unrealengine.com/en-US/Engine/Deployment/BuildOperations/index.html).

#### Command Line
To build using CMD we will need to call UAT (Unreal Automation Tool) the project and output path. Here is the sample of the command with DebugGame & Win64 configuration.
``` cpp
SET UAT_PATH=F:\PROJECTS\ENGINES\unreal-engine-4253\Engine\Build\BatchFiles\RunUAT.bat
SET PRJ_PATH=F:\AB_PROJECTS\abshooter-release\ShooterGame\ShooterGame.uproject
SET OUTPUT_PATH=F:\AB_PROJECTS\abshooter-release\Build\Binaries\Win64\windowsclient

%UAT_PATH% -ScriptsForProject=%PRJ_PATH% BuildCookRun -nop4 -platform=Win64 -clientconfig=DebugGame -project=%PRJ_PATH% -cook -stage -archive -archivedirectory=%OUTPUT_PATH% -package -pak -prereqs -targetplatform=Win64 -build -ShooterGame -utf8output
```
#### Editor
First, make sure that you are using Development/DebugGame Build Configuration to package your build under Edit dropdown menu -> Project Settings -> under Project section -> Packaging. Check on include debug files if you want the pdb file generated as well.
To build standalone windows client, go to Editor -> Under File dropdown menu -> Package Project -> Windows -> Windows (64-bit). 

### Packaging Game Server Build

#### Linux
Here is the `sample` of Linux game server build command with Development-Linux Configuration.
``` cpp
SET UAT_PATH=F:\PROJECTS\ENGINES\unreal-engine-4253\Engine\Build\BatchFiles\RunUAT.bat
SET PRJ_PATH=F:\AB_PROJECTS\abshooter-release\ShooterGame\ShooterGame.uproject
SET OUTPUT_PATH=F:\AB_PROJECTS\abshooter-release\Build\Binaries\linuxserver

%UAT_PATH% BuildCookRun -project=%PRJ_PATH% -noP4 -platform=Linux -clientconfig=Development -cook -serverconfig=Development -server -serverplatform=Linux -noclient -build -stage -pak -archive -archivedirectory=%OUTPUT_PATH%
```
#### Windows
Here is the `sample` of Windows server build command with Development - Win64 Windows Configuration.
``` cpp
SET UAT_PATH=F:\PROJECTS\ENGINES\unreal-engine-4253\Engine\Build\BatchFiles\RunUAT.bat
SET PRJ_PATH=F:\AB_PROJECTS\abshooter-pr\ShooterGame\ShooterGame.uproject
SET OUTPUT_DIR=F:\AB_PROJECTS\abshooter-release\Build\Binaries\windowsserver

%UAT_PATH% BuildCookRun -project=%PRJ_PATH% -nop4 -build -compressed -cook -stage -noclient -server -serverplatform=Win64 -serverconfig=Development -pak -archive -archivedirectory=%OUTPUT_DIR% -utf8output
```

## How to Play
Follow the steps below :

`1.` Start the game

`2.` Login with username and password.

`3.` Open the lobby menu.

`4.` In the lobby menu, you can play Team Deathmatch or FFA (Free for all) matchmaking.

`5.` `FFA` Create a party. Select FFA Game mode, a select region that you want to play at (you have to be in the same region if you want to matchmaking with your friends). Then click on Start Play Button.

`6.` `Team Deathmatch` Create a party and invite a friend to the party. The maximum player in the party is depends on which team deathmatch game mode that you choose (if 3vs3 then max num of party member is 3, if 2vs2 max num of party member is 2). Select a region then click on Start Play Button. When a match has been found, click on the ready button in the popup prompt.

`7.` The game is now started, win as many kills as you can (if team deathmatch then kill the opposing team member). The game will end in 5 minutes. Expect a delay when player entering the level in the dedicated server, to ensure the dedicated server already has the player information from matchmaking service.
