#!/bin/bash

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
    echo "Cannot find files input.txt and output.txt"
fi