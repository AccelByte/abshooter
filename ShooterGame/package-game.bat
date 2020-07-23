SET CURDIR=%~dp0
SET ENGINE_UAT="D:\UE Sources\4.21\UnrealEngine\Engine\Build\BatchFiles\RunUAT.bat"
SET PROJECT_PATH=%CURDIR%\ShooterGame.uproject
SET SERVER_PLATFORM=Win64
SET BUILD_CONFIG=Development
SET CLIENT_PLATFORM=Win64
SET CLIENT_OUTPUT=%CURDIR%\%BUILD_CONFIG%%CLIENT_PLATFORM%\
SET SERVER_OUTPUT=%CURDIR%\%BUILD_CONFIG%%SERVER_PLATFORM%\

%ENGINE_UAT% BuildCookRun -Project=%PROJECT_PATH% -nop4 -build -cook -compressed -stage -c -TargetPlatform=%CLIENT_PLATFORM% -Platform=%CLIENT_PLATFORM% -ClientConfig=%BUILD_CONFIG% -archive -archivedirectory=%CLIENT_OUTPUT% -utf8output