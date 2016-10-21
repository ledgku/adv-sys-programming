#! /bin/bash

if [ $# -ne 3 ]
then
    echo "Usage: ./run.sh EXECUTABLE_FILE OUTPUT_FILE REPEAT_COUNT"
    exit
else
    echo "### $1 /tmp/file_0001 /tmp/file_0002 $2 ###"

    num=0

    while [ $num -lt $3 ]
    do
        num=$(($num+1))
	echo "$num"
        ./$1 /tmp/file_0001 /tmp/file_0002 $2
    done
fi
