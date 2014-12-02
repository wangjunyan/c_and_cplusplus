#!/bin/bash

path=$1

file_list=`find $path -type f -name *.java`
for file_name in $file_list
do
    echo $file_name
    iconv -f UTF-8 -t US-ASCII -c $file_name > $file_name.temp
    mv $file_name.temp $file_name
done

