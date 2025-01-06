#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepare_matrix(char* key, char matrix[SIZE][SIZE]) {
    int alphabet[26] = {0};  // To track which letters have been used
    int i, j, k = 0;
    

    alphabet['J' - 'A'] = 1;
    
    
    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (isalpha(ch) && alphabet[ch - 'A'] == 0) {
            alphabet[ch - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
    
    
    for (i = 0; i < 26; i++) {
        if (alphabet[i] == 0 && i != 'J' - 'A') {  
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}
void prepare_text(char* text, char* prepared_text) {
    int i, j = 0;
    int length = strlen(text);
    for (i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            prepared_text[j++] = toupper(text[i]);
        }
    }
    prepared_text[j] = '\0';
    if (j % 2 != 0) {
        prepared_text[j++] = 'X';
    }
    prepared_text[j] = '\0';
}
void find_position(char ch, char matrix[SIZE][SIZE], int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt_playfair(char* prepared_text, char matrix[SIZE][SIZE], char* ciphertext) {
    int i, row1, col1, row2, col2;
    
    for (i = 0; i < strlen(prepared_text); i += 2) {
        char ch1 = prepared_text[i];
        char ch2 = prepared_text[i + 1];
        
        find_position(ch1, matrix, &row1, &col1);
        find_position(ch2, matrix, &row2, &col2);
        
        if (row1 == row2) { 
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {  
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {  
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char key[100], text[100], prepared_text[200], ciphertext[200];
    char matrix[SIZE][SIZE];
    
 
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  
    
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  
    
    
    prepare_matrix(key, matrix);
    prepare_text(text, prepared_text);
    encrypt_playfair(prepared_text, matrix, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    
    return 0;
}

