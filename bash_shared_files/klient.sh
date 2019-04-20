#!/bin/bash
#klient wypełnia plik input.txt i wypisuje dane z pliku output.txt

if [[ -f input.txt && -f output.txt ]]
then
    if [[ ! -s input.txt ]]
    then
        #echo "Wprowadź liczbe: "
        read user_input
        echo $user_input > input.txt
    fi

    while [ 1 ] ; do
        if [ -s output.txt ]
        then
            #echo "Wynik to:"
            cat output.txt
            > output.txt
        fi
    done
else
    echo "Brak plików input.txt i output.txt"
fi