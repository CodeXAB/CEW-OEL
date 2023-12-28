#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

size_t write_callback(void *contents, size_t size, size_t nmemb, json_t **json)
{
    size_t total_size = size * nmemb;
    json_error_t error;
    *json = json_loadb(contents, total_size, 0, &error);
    return total_size;
}

int main(void)
{
    const char *api_link = "http://api.weatherapi.com/v1/current.json";
    const char *api_key = "b611d072009f47d6ac2162632230912";
    const char *location_file = "location.txt";
    const char *data_file = "raw_data.txt";

    // Read location from file
    FILE *file = fopen(location_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open location file.\n");
        return 1;
    }

    char location[248];
    if (fgets(location, sizeof(location), file) == NULL) {
        fprintf(stderr, "Failed to read location from file.\n");
        fclose(file);
        return 1;
    }

    // Remove newline character, if present
    size_t len = strlen(location);
    if (len > 0 && location[len - 1] == '\n') {
        location[len - 1] = '\0';
    }

    fclose(file);

    // Construct URL
    char url[256];
    snprintf(url, sizeof(url), "%s?key=%s&q=%s", api_link, api_key, location);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        json_t *json = NULL;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            json_t *current = json_object_get(json, "current");
            if (current != NULL)
            {
                json_t *visibility_miles = json_object_get(current, "vis_miles");

                if (visibility_miles != NULL && json_is_number(visibility_miles))
                {
                    double visibility_miles_val = json_number_value(visibility_miles);

                    // Append visibility data to text file
                    FILE *data_file_ptr = fopen(data_file, "a");
                    if (data_file_ptr == NULL) {
                        fprintf(stderr, "Failed to open data file.\n");
                        json_decref(json);
                        curl_easy_cleanup(curl);
                        curl_global_cleanup();
                        return 1;
                    }
                    fprintf(data_file_ptr, "%.1f\n", visibility_miles_val);
                    fclose(data_file_ptr);

                    printf("Visibility (miles): %.1f\n", visibility_miles_val);
                }
            }
            else
            {
                fprintf(stderr, "Failed to parse JSON.\n");
            }

            json_decref(json);
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
