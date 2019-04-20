#!/bin/bash

server_fifo="serverfifo"

shutdown () {
    rm $server_fifo
    echo "Wyłączanie serwera..."
    exit 0
}

master_f () {
    trap "" SIGHUP
    trap "" SIGTERM
    trap "" SIGINT
    echo $$ > "server_pid"
    trap shutdown SIGUSR1
    echo "Serwer"
    mkfifo $server_fifo
    while [ true ] ; do
        read line < $server_fifo
        stringarray=($line)
        klient_dir=${stringarray[0]}
        arg=${stringarray[1]}
        ./server.sh $klient_dir $arg -s &
    done
}

slave_f () {
    klient_fifo="$1/klientfifo"
    arg=$(( $2 ))
    echo "$(( $arg * $arg ))" > $klient_fifo
}

if [ "$#" -eq 0 ] ; then
    master_f
elif [ "$#" -eq 3 ] && [ "$3" == "-s" ] ; then
    slave_f $1 $2 # [katalog] [wartosc] -s
else
    echo "Nieprawidłowe wykonanie"
fi