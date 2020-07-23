SET CURDIR=%~dp0
SET ENGINE_UAT="D:\UE Sources\4.21\UnrealEngine\Engine\Build\BatchFiles\RunUAT.bat"
SET GAME_PROJECT=%CURDIR%\ShooterGame.uproject
SET PLATFORM=Win64
SET BUILD_CONFIG=Development
set SERVER_OUTPUT=%CURDIR%\%BUILD_CONFIG%%PLATFORM%\
%ENGINE_UAT% BuildCookRun -project=%GAME_PROJECT% -nop4 -build -compressed -cook -stage -noclient -server -serverplatform=%PLATFORM% -serverconfig=%BUILD_CONFIG% -archive -archivedirectory=%SERVER_OUTPUT% -utf8output
