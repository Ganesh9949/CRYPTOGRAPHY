#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the repeated key
void generateKey(const char *text, const char *key, char *generatedKey) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j = 0;

    for (i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            generatedKey[i] = toupper(key[j % keyLen]);
            j++;
        } else {
            generatedKey[i] = text[i];
        }
    }
    generatedKey[textLen] = '\0';
}

// Function to encrypt text using the Vigenere cipher
void encrypt(const char *text, const char *key, char *encryptedText) {
    char generatedKey[100];
    generateKey(text, key, generatedKey);

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            encryptedText[i] = (toupper(text[i]) - 'A' + (generatedKey[i] - 'A')) % 26 + base;
        } else {
            encryptedText[i] = text[i];
        }
    }
    encryptedText[strlen(text)] = '\0';
}

int main() {
    char text[100], key[100], encryptedText[100];

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    encrypt(text, key, encryptedText);

    printf("Encrypted text: %s\n", encryptedText);

    return 0;
}

