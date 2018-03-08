#!/bin/sh

for file in tests/*err*
do
	echo "File: $file"
	#./lem_in < "$file" 2>&1
	make >/dev/null && ./lem_in < "$file" >/dev/null &
	leaks lem_in | grep "leaks for" && pkill lem_in
done
	

