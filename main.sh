#!/bin/bash

gcc datafetching.c mail.c -o datafetching -ljansson -lcurl
# Fetch data 24 times
for ((i=0; i<24; i++))
do
	./datafetching

	# Wait for a specified interval (e.g., 10 seconds)
	sleep 5
done

# Perform calculations
gcc calculation2.c -o calculation2
./calculation2

fi

exit 0
