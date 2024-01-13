#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_VALUES 24

int main() {
    FILE *file;
    char *filename = "raw_data.txt";
    FILE *outputFile;
    char *outputFilename = "mean_value.log";

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return 1;
    }

    float sum = 0.0;
    int count = 0;
    float values[MAX_VALUES];

    // Read the last 24 values from the file
    float value;
    while (fscanf(file, "%f", &value) == 1) {
        if (count >= MAX_VALUES) {
            memmove(values, values + 1, (MAX_VALUES - 1) * sizeof(float));
            values[MAX_VALUES - 1] = value;
        } else {
            values[count] = value;
            count++;
        }
    }

    fclose(file);

    if (count < MAX_VALUES) {
        printf("Insufficient values in the file.\n");
        return 1;
    }

    // Calculate the sum of the last 24 values
    for (int i = 0; i < MAX_VALUES; i++) {
        sum += values[i];
    }

    float mean = sum / MAX_VALUES;
    printf("Mean Visiblity: %f\n", mean);

    // Compare mean with previous value
    float previousMean = 1.0; // Initialize previous mean value
    // Read the previous mean from a separate file or any source

    if (mean >= previousMean) {
        printf("Visibility is good.\n");
    } else {
        printf("Visibility is not good.\n");
        
    }

    outputFile = fopen(outputFilename, "a");
    if (outputFile == NULL) {
        printf("Error opening output file %s.\n", outputFilename);
        return 1;
    }

    // Write the mean value to the output file
    fprintf(outputFile, "%f\n", mean);

    fclose(outputFile);

    return 0;
}
