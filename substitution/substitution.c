#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_args(int argc, string argv[]);

int cipher(string key);

int get_alphabet_pos(char letter);

int main(int argc, string argv[]) {
    if (!(check_args(argc, argv))) {
        return 1;
    }
    return cipher(argv[1]);
}

bool check_args(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key");
        return false;
    } else if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.");
        return false;
    }
    return true;
}

int cipher(string key) {
    string plainText = get_string("plaintext: ");
    string cipherText = malloc(1);
    if (cipherText == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    cipherText[0] = '\0';
    int textSize = strlen(plainText);
    for (int i = 0; i < textSize; ++i) {
        char character = plainText[i];
        if (isalpha(character)) {
            int pos = get_alphabet_pos(character);
            if (islower(character)) {
                char tempStr[2];
                tempStr[0] = tolower(key[pos]);
                tempStr[1] = '\0';
                cipherText = realloc(cipherText, strlen(cipherText) + 2);
                if (cipherText == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return 1;
                }
                strcat(cipherText, tempStr);
            } else {
                char tempStr[2];
                tempStr[0] = toupper(key[pos]);
                tempStr[1] = '\0';
                cipherText = realloc(cipherText, strlen(cipherText) + 2);
                if (cipherText == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return 1;
                }
                strcat(cipherText, tempStr);
            }
        } else {
            char tempStr[2];
            tempStr[0] = character;
            tempStr[1] = '\0';
            cipherText = realloc(cipherText, strlen(cipherText) + 2);
            if (cipherText == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            strcat(cipherText, tempStr);
        }
    }
    printf("ciphertext: %s", cipherText);
    free(cipherText);
    return 0;
}


int get_alphabet_pos(char letter) {
    const int alphabet_size = 26;
    const char engAlphabet[26] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    for (int i = 0; i < alphabet_size; i++) {
        if (toupper(letter) == engAlphabet[i]) {
            return i;
        }
    }
}
