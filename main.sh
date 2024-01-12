#!/bin/bash

if [ "$1" == "-e" ]; then
    ./mail
else
    # Fetch data 24 times
    for ((i=0; i<24; i++))
    do
        # Execute datafetching script
        ./datafetching

        # Wait for a specified interval (e.g., 10 seconds)
        sleep 1
    done

    # Perform calculations
    ./calculation2

fi

exit 0
