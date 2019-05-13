#!/bin/bash

server_dir="../server"
client_dir=$(pwd)
server_fifo="$server_dir/serverfifo"
client_fifo="clientfifo"


if [ "$#" -eq 1 ] ; then
    echo "Sending to server: \"$1\""
    mkfifo $client_fifo
    echo "$klient_dir $1" > $server_fifo
    read ans < $client_fifo
    echo "Answer: \"$ans\""
    rm $client_fifo
else
    echo "client.sh [arg]"
fi
