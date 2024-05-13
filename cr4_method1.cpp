#include <iostream>
#include <windows.h>
#include <cstring> // Include for strlen function

typedef struct {
    unsigned int i;
    unsigned int j;
    unsigned char s[256];
} Rc4Context;

void rc4Init(Rc4Context* context, const unsigned char* key, size_t length) {
    unsigned int i;
    unsigned int j;
    if (context == NULL || key == NULL)
        return;

    // Clear context 
    context->i = 0;
    context->j = 0;

    // Initialize the S array with identity permutation
    for (i = 0; i < 256; i++) {
        context->s[i] = i;
    }

    // s is then processed for 256 iterations
    for (i = 0, j = 0; i < 256; i++) {
        j = (j + context->s[i] + key[i % length]) % 256;
        //swap
        char temp = context->s[i];
        context->s[i] = context->s[j];
        context->s[j] = temp;
    }
}

void rc4Cipher(Rc4Context* context, const unsigned char* input, unsigned char* output, size_t length) {
    unsigned char temp;

    // Restore context 
    unsigned int i = context->i;
    unsigned int j = context->j;
    unsigned char* s = context->s;

    // Encryption loop
    for (size_t k = 0; k < length; k++) {
        // Adjust indices
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        //Swap
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        // Encrypt/Decrypt
        output[k] = input[k] ^ s[(s[i] + s[j]) % 256];
    }
}

int main() {
    // Initialization
    Rc4Context ctx = { 0 };

    // Key used for encryption
    const unsigned char* key = (const unsigned char*)"maldev123";
    rc4Init(&ctx, key, strlen((const char*)key));

    // Plaintext
    const unsigned char* plaintext = (const unsigned char*)"Hello World!!!";
    size_t plaintextLength = strlen((const char*)plaintext);

    // Allocate memory for ciphertext
    unsigned char ciphertext[100];
    // Encryption
    rc4Cipher(&ctx, plaintext, ciphertext, plaintextLength);

    std::cout << "Encrypted text: ";
    for (size_t i = 0; i < plaintextLength; i++) {
        std::cout << ciphertext[i];
    }
    std::cout << std::endl;

    // Allocate memory for decrypted text
    unsigned char decryptedText[100];
    // Decryption
    rc4Init(&ctx, key, strlen((const char*)key)); // Reinitialize context with same key
    rc4Cipher(&ctx, ciphertext, decryptedText, plaintextLength);

    std::cout << "Decrypted text: ";
    for (size_t i = 0; i < plaintextLength; i++) {
        std::cout << decryptedText[i];
    }
    std::cout << std::endl;
}
