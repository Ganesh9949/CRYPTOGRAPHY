#include <stdio.h>
#include <string.h>

void encryptRailFence(char *text, int key, char *encryptedText) {
    int len = strlen(text);
    int row, col;
    int direction = 1; // 1 for down, -1 for up
    char rail[key][len];

    // Initialize the rail matrix with '\0'
    for (row = 0; row < key; row++) {
        for (col = 0; col < len; col++) {
            rail[row][col] = '\0';
        }
    }

    // Fill the rail matrix in a zigzag pattern
    row = 0;
    for (col = 0; col < len; col++) {
        rail[row][col] = text[col];
        if (row == 0) {
            direction = 1; // Move down
        } else if (row == key - 1) {
            direction = -1; // Move up
        }
        row += direction;
    }

    // Read the encrypted text row-wise
    int index = 0;
    for (row = 0; row < key; row++) {
        for (col = 0; col < len; col++) {
            if (rail[row][col] != '\0') {
                encryptedText[index++] = rail[row][col];
            }
        }
    }
    encryptedText[index] = '\0';
}

int main() {
    char text[100], encryptedText[100];
    int key;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the key (number of rails): ");
    scanf("%d", &key);

    encryptRailFence(text, key, encryptedText);

    printf("Encrypted text: %s\n", encryptedText);

    return 0;
}

