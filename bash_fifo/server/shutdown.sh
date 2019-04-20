#!/bin/bash

pid=$(cat server_pid)
echo "" > server_pid
kill -SIGUSR1 $pid