#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <cJSON.h>
// This file is to fetch data specifically for visibility from API
size_t write_callback(void *contents, size_t size, size_t nmemb, cJSON **json)
{
    size_t total_size = size * nmemb;
    *json = cJSON_ParseWithLength(contents, total_size);
    return total_size;}

int main(void)
{
    const char *url = "http://api.weatherapi.com/v1/current.json?key=b611d072009f47d6ac2162632230912&q=London";

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        cJSON *json = NULL;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            cJSON *current = cJSON_GetObjectItem(json, "current");
            if (current != NULL)
            {
                cJSON *visibility_km = cJSON_GetObjectItem(current, "vis_km");
                cJSON *visibility_miles = cJSON_GetObjectItem(current, "vis_miles");

                if (visibility_km != NULL)
                {
                    double visibility_km_val = visibility_km->valuedouble;
                    printf("Visibility (km): %.1f\n", visibility_km_val);
                }

                if (visibility_miles != NULL)
                {
                    double visibility_miles_val = visibility_miles->valuedouble;
                    printf("Visibility (miles): %.1f\n", visibility_miles_val);
                }
            }
            else
            {
                fprintf(stderr, "Failed to parse JSON.\n");
            }

            cJSON_Delete(json);
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
