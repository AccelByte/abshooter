#!/bin/sh
BASE_URL="<INSERT-YOUR-BASE-URL-HERE>"
BASIC_CREDS="<INSERT-YOUR-BASIC-CREDS-HERE>"
namespace="<INSERT-YOUR-NAMESPACE-HERE>"

CHECK=$(netstat -antp 2>/dev/null | grep $PORT | wc -l)

echo $CHECK

while [ "$CHECK" -le "1" ]; do
    CHECK=$(netstat -anp 2>/dev/null | grep $PORT | wc -l)
    echo "Server is not ready yet.."
    sleep 3
done

echo "Server is ready, sending register to DSM service.."

response=$(curl -X POST --header "Content-Type: application/x-www-form-urlencoded" --header "Accept: application/json" --header "Authorization: Basic $BASIC_CREDS" -d "grant_type=client_credentials" "$BASE_URL/iam/oauth/token")
token=$(echo "$response" | grep access_token | cut -d ':' -f 2 | cut -d '"' -f 2)
curl -X POST --header "Content-Type: application/json" --header "Authorization: Bearer $token" -d "{ \"pod_name\": \"$POD_NAME\", \"port\": $PORT }" "$BASE_URL/dsm/namespaces/$namespace/servers/register"
