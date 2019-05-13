#!/bin/bash

if [[ -f input.txt && -f output.txt ]]
then
    if [[ ! -s input.txt ]]
    then
        #echo "Enter a number: "
        read user_input
        echo $user_input > input.txt
    fi

    while [ 1 ] ; do
        if [ -s output.txt ]
        then
            #echo "Result:"
            cat output.txt
            > output.txt
        fi
    done
else
    echo "Cannot find files input.txt and output.txt"
fi