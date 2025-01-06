#include <stdio.h>
#include <string.h>

// Function to perform cyclic rearrangement of text
void cyclicRearrangement(char *text) {
    int len = strlen(text);
    if (len < 2) return;

    char temp = text[len - 1]; // Store the last character
    for (int i = len - 1; i > 0; i--) {
        text[i] = text[i - 1]; // Shift characters to the right
    }
    text[0] = temp; // Place the last character at the beginning
}

// Function to shift characters by a given key
void shiftCharacters(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            // Uppercase letter
            text[i] = 'A' + (text[i] - 'A' + key) % 26;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            // Lowercase letter
            text[i] = 'a' + (text[i] - 'a' + key) % 26;
        }
    }
}

// Function to encrypt text using the chasing cipher
void chasingCipherEncrypt(char *text, int key) {
    // Step 1: Perform cyclic rearrangement
    cyclicRearrangement(text);

    // Step 2: Shift characters by the key
    shiftCharacters(text, key);
}

int main() {
    char text[100];
    int key;

    // Input plaintext and key
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the key (shift amount): ");
    scanf("%d", &key);

    // Encrypt the text
    chasingCipherEncrypt(text, key);

    // Output the ciphertext
    printf("Ciphertext: %s\n", text);

    return 0;
}

