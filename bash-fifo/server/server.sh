#!/bin/bash

server_fifo="serverfifo"

shutdown () {
    rm $server_fifo
    echo "Shutting down..."
    exit 0
}

master_f () {
    trap "" SIGHUP
    trap "" SIGTERM
    trap "" SIGINT
    echo $$ > "server_pid"
    trap shutdown SIGUSR1
    echo "Server"
    mkfifo $server_fifo
    while [ true ] ; do
        read line < $server_fifo
        stringarray=($line)
        client_dir=${stringarray[0]}
        arg=${stringarray[1]}
        ./server.sh $client_dir $arg -s &
    done
}

slave_f () {
    client_fifo="$1/clientfifo"
    arg=$(( $2 ))
    echo "$(( $arg * $arg ))" > $client_fifo
}

if [ "$#" -eq 0 ] ; then
    master_f
elif [ "$#" -eq 3 ] && [ "$3" == "-s" ] ; then
    slave_f $1 $2 # [directory] [arg] -s
else
    echo "Invalid exec"
fi