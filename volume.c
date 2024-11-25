/
 Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header_buffer[HEADER_SIZE];

    if (fread(header_buffer, HEADER_SIZE, 1, input) != 1) {
        printf("Error reading the header.\n");
        return 1;
    }

    if (fwrite(header_buffer, HEADER_SIZE, 1, output) != 1) {
        printf("Error writing the header.\n");
        return 1;
    }

    int16_t sample_buffer;
    while (fread(&sample_buffer, sizeof(sample_buffer), 1, input) != 0) {
        sample_buffer *= factor;
        if (fwrite(&sample_buffer, sizeof(sample_buffer), 1, output) != 1) {
            printf("Error writing to output file.\n");
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);
}
