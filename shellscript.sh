#!/usr/bin/bash

# Configuration file path
config_file="config.txt"
# Define the interval in seconds (e.g., 1 hour = 3600 seconds)
interval=10
count=0

while true; do
  # Read the location from the configuration file
  user_location=$(cat "$config_file")

  # API endpoint and key
  API_URL="https://api.weatherapi.com/v1/current.json"
  API_KEY="b611d072009f47d6ac2162632230912"

  # Combine the API URL with the user-entered location
  API_REQUEST="$API_URL?key=$API_KEY&q=$user_location"

  # Retrieve data from API and append visibility to the file
  visibility=$(curl -s -X GET "$API_REQUEST" | jq -r '.current.vis_km')

  # Check if the visibility data file is empty
  if [ -s "visibility_data.txt" ]; then
    # Append the visibility to the file
    echo "$visibility" >> visibility_data.txt
  else
    # Clear the file and start writing from the 25th value at the beginning
    echo "$visibility" > visibility_data.txt
    count=1
  fi

  # Increment the count
  count=$((count + 1))

  # Check if the count reaches 25
  if [ $count -gt 25 ]; then
    # Remove the first 24 lines from the file
    sed -i '1,24d' visibility_data.txt
    count=25
  fi

  # Wait for the specified interval
  sleep "$interval"

  # Print the visibility information
  echo "Visibility information for $user_location:"
  echo "Visibility: $visibility km"
done
