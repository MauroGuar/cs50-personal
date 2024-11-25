#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cipher(int key);


char get_ciphered_letter(int key, bool lower, char letter);

bool check_args(int argc, string argv[]);


int main(int argc, string argv[]) {
    if (!(check_args(argc, argv))) {
        return 1;
    }
    int key = atoi(argv[1]);
    return cipher(key);
}

int cipher(int key) {
    string plainText = get_string("plaintext: ");
    int textSize = strlen(plainText);
    for (int i = 0; i < textSize; i++) {
        char character = plainText[i];
        if (isalpha(character)) {
            char cipheredLetter = get_ciphered_letter(key, islower(character), character);
            plainText[i] = cipheredLetter;
        } else {
            plainText[i] = character;
        }
    }
    printf("ciphertext: %s\n", plainText);
    return 0;
}

char get_ciphered_letter(int key, bool lower, char letter) {
    char engAlphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabetSize = 26;
    int originalLetterPos = -1;
    for (short i = 0; i < alphabetSize; i++) {
        if (toupper(letter) == engAlphabet[i]) {
            originalLetterPos = i + 1;
        }
    }
    int cipheredLetterPos = (originalLetterPos + key) % alphabetSize;
    if (lower) {
        return tolower(engAlphabet[cipheredLetterPos - 1]);
    }
    return engAlphabet[cipheredLetterPos - 1];
}

bool check_args(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key");
        return false;
    } else if (!(isdigit(argv[1][0]) && isdigit(argv[1][1]))) {
        printf("Usage: ./substitution key");
        return false;
    }
    return true;
}
