#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

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

    // Calculate the sum and count of values in the file
    float value;
    while (fscanf(file, "%f", &value) == 1) {
        sum += value;
        count++;
    }

    float mean = sum / count;
    printf("Mean %f\n", mean);
    // Compare mean with previous value
    float previousMean = 1.0; // Initialize previous mean value
    // Read the previous mean from a separate file or any source

        if (mean > previousMean) {
            printf("Visibility is good.\n");
        } else {
            printf("Visibility is not good.\n");
        }
    

    fclose(file);


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
