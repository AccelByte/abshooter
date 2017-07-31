#
# Setup ShooterGame
#

# Binary content
if(!(Test-Path -Path "$pwd\ShooterGame\Content" )) 
{
	$client = new-object System.Net.WebClient
	$contentUrl = "https://s3-us-west-2.amazonaws.com/accelbyte/justice-ue4-shootergame-4.16-content.zip"
	$client.DownloadFile($contentUrl,"$pwd\Content.zip")
	Expand-Archive "$pwd\Content.zip" -DestinationPath "$pwd\ShooterGame"
}

# Cross compling for Linux
if(!(Test-Path -Path "$pwd\UE-Toolchain" )) 
{
	$client = new-object System.Net.WebClient
	$crossUrl = "http://cdn.unrealengine.com/CrossToolchain_Linux/v9_clang-4.0.0-centos7.zip"
	$client.DownloadFile($crossUrl, "$pwd\v9_clang-4.0.0-centos7.zip")
	md -Path "$pwd\UE-Toolchain"
# XXX: why does expand archive not work on this zip file?
#	Expand-Archive ".\v9_clang-4.0.0-centos7.zip" -Destination "$pwd\UE-Toolchain"
        $shell = New-Object -ComObject Shell.Application 
        $shell.Namespace("$pwd\UE-Toolchain").copyhere(($shell.NameSpace("$pwd\v9_clang-4.0.0-centos7.zip")).items()) 
}
[Environment]::SetEnvironmentVariable('LINUX_MULTIARCH_ROOT', "$pwd\UE-Toolchain", "User")

