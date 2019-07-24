while true; do
    ps -x | grep -v grep | grep ShooterGameServer > /dev/null
    result=$?
    echo "exit code: ${result}"
    if [ "${result}" -eq "0" ] ; then
        echo "`date`: $SERVICE service running, everything is fine"
    else
        echo "`date`: $SERVICE is not running"
        ./LinuxNoEditor/run.sh &
    fi
    sleep 5
done