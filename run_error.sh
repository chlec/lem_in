#!/bin/sh

for file in tests/*err*
do
	echo "File: $file"
	./lem_in < "$file" 2>&1
done
	
