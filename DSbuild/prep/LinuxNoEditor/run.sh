#!/bin/sh
UE4_TRUE_SCRIPT_NAME=$(echo \"$0\" | xargs readlink -f)
UE4_PROJECT_ROOT=$(dirname "$UE4_TRUE_SCRIPT_NAME")

CHECK="1"

while [ "$CHECK" -gt "0" ]; do
    number=$(( $(od -A n -N 1 /dev/urandom) + 1))
    export PORT=$(( ( $number % 1000 )  + 15000 ))
    CHECK=$(netstat -anp 2>/dev/null | grep $PORT | wc -l)
    echo "Port $PORT is used.."
done

echo "Using Port $PORT.."

./LinuxNoEditor/register.sh &

echo "$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer"
chmod +x "$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer"
"$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer" Highrise -server -log -nosteam PORT=$PORT $@