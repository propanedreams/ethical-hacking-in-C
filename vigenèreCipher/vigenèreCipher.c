#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using the Vigenère Cipher
void encrypt(const char* plaintext, const char* keyword, char* ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(keyword);
    int j = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyBase = isupper(keyword[j % keyLen]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (keyword[j % keyLen] - keyBase)) % 26 + base;
            j++; // Move to the next letter in the keyword
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[textLen] = '\0'; // Null-terminate the string
}

// Function to decrypt ciphertext using the Vigenère Cipher
void decrypt(const char* ciphertext, const char* keyword, char* plaintext) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(keyword);
    int j = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyBase = isupper(keyword[j % keyLen]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - (keyword[j % keyLen] - keyBase) + 26) % 26 + base;
            j++; // Move to the next letter in the keyword
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    plaintext[textLen] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[256];
    char keyword[256];
    char ciphertext[256];
    char decryptedText[256];

    // Input plaintext and keyword
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    // Encrypt the plaintext
    encrypt(plaintext, keyword, ciphertext);
    printf("\nEncrypted text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, keyword, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
