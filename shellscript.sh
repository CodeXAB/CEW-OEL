#!/bin/bash

# Configuration file path
config_file="config.txt"
# Define the interval in seconds (e.g., 1 hour = 3600 seconds)
interval=10
while true; do
  # Read the location from the configuration file
  user_location=$(cat "$config_file")

  # API endpoint and key
  API_URL="https://api.weatherapi.com/v1/current.json"
  API_KEY="b611d072009f47d6ac2162632230912"

  # Combine the API URL with the user-entered location
  API_REQUEST="$API_URL?key=$API_KEY&q=$user_location"

  # Retrieve data from API and save visibility in a file
  curl -s -X GET "$API_REQUEST" | jq -r '.current.vis_km' > visibility_data.txt

  # Check if the visibility data file is empty
  if [ -s "visibility_data.txt" ]; then
    # Wait for the specified interval
    sleep "$interval"

    # Read the visibility data from the file
    visibility=$(cat visibility_data.txt)

    # Print the visibility information
    echo "Visibility information for $user_location:"
    echo "Visibility: $visibility km"
  else
    echo "Error: Failed to fetch visibility data for $user_location. Trying again in $interval seconds."
  fi
done
