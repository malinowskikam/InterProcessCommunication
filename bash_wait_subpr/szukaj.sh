#!/bin/bash

master_f () {
    ./szukaj.sh "$1" "$2" -s
    if [[ "$?" -eq "1" ]] ; then
        echo "Nie znaleziono żadnego pliku $1/**/$2"
    fi
    exit 0
}

slave_f () {
    path="$1/*"
    directory_count=0

    exit_code=1

    for file in $path ; do
        if [ -d "$file" ] ; then
            ./szukaj.sh "$file" "$2" -s &
            directory_count=$(( $directory_count + 1 ))
        else
            if [[ "$file" == "$1/$2" ]] ; then
                echo "$file" | tr -s '/' 
                exit_code=3
            fi
        fi
    done

    for i in seq $directory_count ; do
        wait $!
        exit_code=$(( $exit_code | $? ))
    done

    exit $exit_code
}


is_master=-1
if [ "$#" -eq 2 ] ; then
    is_master=1
elif [ "$#" -eq 3 ] ; then
    if [ "$3" == "-s" ] ; then
        is_master=0
    else
        echo "Błędne wywołanie, użyj -h"
    fi
elif [ "$#" -eq 1 ] && [ "$1" == "-h" ] ; then
    echo "Wywołanie: szukaj.sh [katalog] [plik]"
elif [ "$#" -eq 0 ] ; then
    echo "Wywołanie: szukaj.sh [katalog] [plik]"
else
    echo "Błędne wywołanie, użyj -h"
fi

if [ "$is_master" -eq 0 ] ; then
    slave_f $1 $2
elif [ "$is_master" -eq 1 ] ; then
    master_f $1 $2
fi