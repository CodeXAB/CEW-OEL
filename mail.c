#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "send_mail.h"


// Callback function to provide email body data
size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    struct EmailBodyInfo *email_body = (struct EmailBodyInfo *)userdata;
    size_t total_size = size * nmemb;

    if (email_body->size > 0) {
        size_t copy_size = (total_size < email_body->size) ? total_size : email_body->size;
        memcpy(ptr, email_body->data, copy_size);
        email_body->data += copy_size;
        email_body->size -= copy_size;
        return copy_size;
    } else {
        return 0; // Signal end of data
    }
}

int send_email() {
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;
    struct curl_slist *headers = NULL;
    struct EmailBodyInfo email_body_info;
    printf("libcurl version: %s\n", curl_version());

    const char *body;
    body = BODY_BAD;
 

    email_body_info.data = body;
    email_body_info.size = strlen(body);

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the SMTP server and login credentials
        curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);
        curl_easy_setopt(curl, CURLOPT_USERNAME, USERNAME);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWORD);

        // Enable authentication
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        // Set the email details
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, USERNAME);
        recipients = curl_slist_append(recipients, TO_ADDRESS);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        // Set the email subject in the headers
        // Set the email body using the callback function
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &email_body_info);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L); // Set a timeout of 60 seconds (adjust as needed)

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        // Perform the email sending
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf("Email sent successfully!\n");
        // Cleanup
        curl_slist_free_all(recipients);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}

