#!/bin/sh
UE4_TRUE_SCRIPT_NAME=$(echo \"$0\" | xargs readlink -f)
UE4_PROJECT_ROOT=$(dirname "$UE4_TRUE_SCRIPT_NAME")
BASE_URL="<INSERT-YOUR-BASE-URL-HERE>"
BASIC_CREDS="<INSERT-YOUR-BASIC-CREDS-HERE>"
namespace="<INSERT-YOUR-NAMESPACE-HERE>"

CHECK="1"

while [ "$CHECK" -gt "0" ]; do
    number=$(( $(od -A n -N 1 /dev/urandom) + 1))
    export PORT=$(( ( $number % 1000 )  + 15000 ))
    CHECK=$(netstat -antp 2>/dev/null | grep $PORT | wc -l)
    echo "Port $PORT is used.."
done
``

echo "Using Port $PORT.."

echo "$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer"
chmod +x "$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer"
"$UE4_PROJECT_ROOT/ShooterGame/Binaries/Linux/ShooterGameServer" Highrise -server -log -nosteam PORT=$PORT $@ &

echo $CHECK

while [ "$CHECK" -eq "0" ]; do
    CHECK=$(netstat -antp 2>/dev/null | grep $PORT | wc -l)
    echo "Server is not ready yet.."
    sleep 3
done

echo "Server is ready, sending register to DSM service.."

response=$(curl -X POST --header "Content-Type: application/x-www-form-urlencoded" --header "Accept: application/json" --header "Authorization: Basic $BASIC_CREDS" -d "grant_type=client_credentials" "$BASE_URL/iam/oauth/token")
token=$(echo "$response" | grep access_token | cut -d ':' -f 2 | cut -d '"' -f 2)
curl -X POST --header "Content-Type: application/json" --header "Authorization: Bearer $token" -d "{ \"pod_name\": \"$POD_NAME\", \"port\": $PORT }" "$BASE_URL/dsm/namespaces/$namespace/servers/register"
