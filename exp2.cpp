#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to prepare the Playfair cipher key matrix
void prepareKeyMatrix(const char *key, char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;

    // Populate the matrix with the key
    for (i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';

        if (!used[c - 'A']) {
            keyMatrix[k / SIZE][k % SIZE] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }

    // Fill the rest of the matrix with remaining letters
    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') continue; // Skip 'J'
        if (!used[i]) {
            keyMatrix[k / SIZE][k % SIZE] = 'A' + i;
            used[i] = 1;
            k++;
        }
    }
}

// Function to find the position of a character in the key matrix
void findPosition(char keyMatrix[SIZE][SIZE], char c, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters
void encryptPair(char keyMatrix[SIZE][SIZE], char *a, char *b) {
    int r1, c1, r2, c2;
    findPosition(keyMatrix, *a, &r1, &c1);
    findPosition(keyMatrix, *b, &r2, &c2);

    if (r1 == r2) {
        // Same row
        *a = keyMatrix[r1][(c1 + 1) % SIZE];
        *b = keyMatrix[r2][(c2 + 1) % SIZE];
    } else if (c1 == c2) {
        // Same column
        *a = keyMatrix[(r1 + 1) % SIZE][c1];
        *b = keyMatrix[(r2 + 1) % SIZE][c2];
    } else {
        // Rectangle swap
        *a = keyMatrix[r1][c2];
        *b = keyMatrix[r2][c1];
    }
}

// Function to prepare the input text by removing spaces and adjusting pairs
void prepareText(const char *input, char *output) {
    int len = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char c = toupper(input[i]);
            if (c == 'J') c = 'I';
            output[len++] = c;
        }
    }
    output[len] = '\0';

    // Insert filler 'X' for duplicate letters in a pair
    char temp[100];
    int k = 0;
    for (int i = 0; i < len; i++) {
        temp[k++] = output[i];
        if (i + 1 < len && output[i] == output[i + 1]) {
            temp[k++] = 'X';
        }
    }
    temp[k] = '\0';

    // Append 'X' if the length is odd
    if (k % 2 != 0) {
        temp[k++] = 'X';
    }
    temp[k] = '\0';

    strcpy(output, temp);
}

int main() {
    char key[50], text[100], preparedText[200];
    char keyMatrix[SIZE][SIZE];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    // Prepare the key matrix
    prepareKeyMatrix(key, keyMatrix);

    // Prepare the text for encryption
    prepareText(text, preparedText);

    // Encrypt the text in pairs
    for (int i = 0; preparedText[i] != '\0'; i += 2) {
        encryptPair(keyMatrix, &preparedText[i], &preparedText[i + 1]);
    }

    printf("Encrypted text: %s\n", preparedText);

    return 0;
}

