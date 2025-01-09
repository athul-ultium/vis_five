
timer()
{
    seconds=$1
    start="$(($(date +%s) + $seconds))"
    while [ "$start" -gt `date +%s` ]; do
        time="$(( $start - `date +%s` ))"
        printf '%s\r' "$(date -u -d "@$time" +%H:%M:%S)"
    done
}

echo "started down count timer starts from $1"
timer $1
echo
echo "done"
