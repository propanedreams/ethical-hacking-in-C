#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using Caesar Cipher
void encrypt(char* message, int shift) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];

        // Encrypt uppercase letters
        if (isupper(ch)) {
            message[i] = ((ch - 'A' + shift) % 26) + 'A';
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            message[i] = ((ch - 'a' + shift) % 26) + 'a';
        }
        // Leave non-alphabetic characters unchanged
    }
}

// Function to decrypt a message using Caesar Cipher
void decrypt(char* message, int shift) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];

        // Decrypt uppercase letters
        if (isupper(ch)) {
            message[i] = ((ch - 'A' - shift + 26) % 26) + 'A';
        }
        // Decrypt lowercase letters
        else if (islower(ch)) {
            message[i] = ((ch - 'a' - shift + 26) % 26) + 'a';
        }
        // Leave non-alphabetic characters unchanged
    }
}

int main() {
    char message[100];
    int shift;
    int choice;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);

    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a number between 1 and 25.\n");
        return 1;
    }

    printf("\nChoose an option:\n");
    printf("1. Encrypt the message\n");
    printf("2. Decrypt the message\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(message, shift);
        printf("\nEncrypted message: %s\n", message);
    } else if (choice == 2) {
        decrypt(message, shift);
        printf("\nDecrypted message: %s\n", message);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
