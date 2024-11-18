#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Function to calculate the SHA-256 hash of a string
void calculateSHA256(const char* str, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str, strlen(str), hash);

    // Convert hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[SHA256_DIGEST_LENGTH * 2] = '\0';  // Null-terminate the string
}

// Function to perform a dictionary attack
void dictionaryAttack(const char* hashToCrack, const char* dictionaryFile) {
    FILE* file = fopen(dictionaryFile, "r");
    if (!file) {
        printf("Failed to open dictionary file: %s\n", dictionaryFile);
        return;
    }

    char line[256];
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Attempting to crack the password...\n");

    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the dictionary word
        line[strcspn(line, "\n")] = '\0';

        // Calculate the hash of the current dictionary word
        calculateSHA256(line, hashedPassword);

        // Compare the calculated hash with the target hash
        if (strcmp(hashedPassword, hashToCrack) == 0) {
            printf("Password cracked! The password is: %s\n", line);
            fclose(file);
            return;
        }
    }

    printf("Password could not be cracked using the provided dictionary.\n");
    fclose(file);
}

int main() {
    // The hash to crack (SHA-256 of "supernatural123")
    const char* targetHash = "5d275c2de264973ecb679b84a0918cc582dd3a29d06d13efdc6b4b7b365d2557";

    // Dictionary file containing possible passwords
    const char* dictionaryFile = "dictionary.txt";

    dictionaryAttack(targetHash, dictionaryFile);

    return 0;
}
