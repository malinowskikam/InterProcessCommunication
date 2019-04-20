#!/bin/bash

server_dir="/home/kamil/wspolbiezne/lab4bash/server"
klient_dir=$(pwd)
server_fifo="$server_dir/serverfifo"
klient_fifo="klientfifo"


if [ "$#" -eq 1 ] ; then
    echo "Wysyłanie do serwera: \"$1\""
    mkfifo $klient_fifo
    echo "$klient_dir $1" > $server_fifo
    read ans < $klient_fifo
    echo "Odpowiedź: \"$ans\""
    rm $klient_fifo
else
    echo "Niepoprawne wywołanie"
fi
