#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // For system commands like "system"

int main() {
    // Fetch data 24 times
    for (int i = 0; i < 24; i++) {
        // Execute datafetching.c
        system("./datafetching");

        // Wait for a specified interval (e.g., 10 seconds)
        sleep(1);
    }

    // Perform calculations
    system("./calculation");

    // Clear raw data file
    FILE *file = fopen("raw_data.txt", "w");
    if (file != NULL) {
        fclose(file);
    }

    return 0;
}
