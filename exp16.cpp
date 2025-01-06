#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// English letter frequency (approximate percentages)
const double ENGLISH_FREQUENCY[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074};

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(const char *text, int frequency[]) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char letter = toupper(text[i]);
            frequency[letter - 'A']++;
        }
    }
}

// Function to map the most frequent letters in the ciphertext to those in English
void performFrequencyAttack(int frequency[], char substitution[]) {
    // Create an array of indices sorted by frequency in the ciphertext
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }

    // Sort the indices based on the frequency array (descending order)
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[sortedIndices[i]] < frequency[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }

    // Map the sorted indices to English letter frequency order
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[sortedIndices[i]] = 'E' + i; // Start mapping from the most common letter
    }
}

// Function to decrypt the ciphertext using the substitution map
void decrypt(const char *ciphertext, const char substitution[], char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]);
            int index = letter - 'A';
            plaintext[i] = substitution[index];
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain the same
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[1000];
    int frequency[ALPHABET_SIZE] = {0};
    char substitution[ALPHABET_SIZE] = {0};
    char plaintext[1000];

    // Input ciphertext
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    // Calculate letter frequency in the ciphertext
    calculateFrequency(ciphertext, frequency);

    // Perform frequency attack
    performFrequencyAttack(frequency, substitution);

    // Decrypt the ciphertext using the substitution map
    decrypt(ciphertext, substitution, plaintext);

    // Display results
    printf("\nFrequency Analysis:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("%c: %d\n", 'A' + i, frequency[i]);
        }
    }

    printf("\nDecrypted Text (Approximation):\n%s\n", plaintext);

    return 0;
}

