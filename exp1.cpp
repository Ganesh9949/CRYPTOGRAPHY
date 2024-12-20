#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];

        // Handle uppercase letters
        if (isupper(c)) {
            text[i] = ((c - 'A' + shift) % 26) + 'A';
        }
        // Handle lowercase letters
        else if (islower(c)) {
            text[i] = ((c - 'a' + shift) % 26) + 'a';
        }
        // Non-alphabetic characters remain unchanged
    }
}

int main() {
    char text[100];
    int shift;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character if present
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);

    // Validate shift value
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a number between 1 and 25.\n");
        return 1;
    }

    caesarCipher(text, shift);

    printf("Encrypted text: %s\n", text);

    return 0;
}

