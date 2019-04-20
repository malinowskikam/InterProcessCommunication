#!/bin/bash
#serwer oblicza wartość funkcji ( f(x)=x^2-2x+1 ) dla danych z pliku input.txt i zapisuje je w pliku output.txt

if [[ -f input.txt && -f output.txt ]]
then
    while [ 1 ] ; do
        if [ -s input.txt ]
        then
            typeset -i user_input=$(cat input.txt)
            value=$(($user_input*$user_input-2*$user_input+1))
            > input.txt
            echo $value > output.txt
        fi
    done
else
    echo "Brak plików input.txt i output.txt"
fi