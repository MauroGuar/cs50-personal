#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *memory_card = fopen(argv[1], "rb");
    if (memory_card == NULL) {
        printf("Error opening the file.");
        return 1;
    }

    uint8_t buffer[512];
    int file_count = 0;
    FILE *output_image = NULL;
    while (fread(buffer, sizeof(uint8_t), sizeof(buffer), memory_card) == 512) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef) {
            file_count++;
            if (output_image != NULL) {
                fclose(output_image);
                output_image = NULL;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", file_count);
            output_image = fopen(filename, "wb");
        }
        if (output_image != NULL) {
            fwrite(buffer, sizeof(uint8_t), sizeof(buffer), output_image);
        }
    }
    if (output_image != NULL) {
        fclose(output_image);
    }
    fclose(memory_card);
    return 0;
}
