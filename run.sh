#!/bin/sh

for file in tests/*
do
	if [[ ${file} != *"err"* ]];then
		if [[ ${file} != *"big"* ]];then
			echo "File: $file"
			./lem_in < "$file" 2>&1
		fi
	fi
done
	

