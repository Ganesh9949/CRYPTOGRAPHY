#include <stdio.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/bn.h>
#include <openssl/sha.h>

#define MESSAGE "This is a test message for DSA."

// Function to generate DSA keys
void generate_dsa_keys(DSA **dsa_keypair) {
    *dsa_keypair = DSA_new();
    
    // Generate a DSA key pair with 2048-bit key size and 256-bit counter size
    if (!DSA_generate_parameters_ex(*dsa_keypair, 2048, NULL, 0, NULL, NULL, NULL)) {
        printf("Error generating DSA parameters\n");
        exit(1);
    }
    
    if (!DSA_generate_key(*dsa_keypair)) {
        printf("Error generating DSA keys\n");
        exit(1);
    }
}

// Function to sign a message using DSA private key
int sign_message(DSA *dsa_keypair, const unsigned char *message, unsigned int message_len, unsigned char *sig) {
    unsigned int sig_len;
    
    // Sign the message with DSA private key
    if (DSA_sign(0, message, message_len, sig, &sig_len, dsa_keypair) == 0) {
        printf("Error signing message\n");
        return 0;
    }

    printf("Signature generated successfully\n");
    return sig_len;
}

// Function to verify the DSA signature using the public key
int verify_signature(DSA *dsa_keypair, const unsigned char *message, unsigned int message_len, unsigned char *sig, unsigned int sig_len) {
    // Verify the signature with DSA public key
    if (DSA_verify(0, message, message_len, sig, sig_len, dsa_keypair) == 1) {
        printf("Signature is valid\n");
        return 1;
    } else {
        printf("Signature is invalid\n");
        return 0;
    }
}

int main() {
    DSA *dsa_keypair;
    unsigned char sig[DSA_size(dsa_keypair)];
    unsigned int sig_len;

    // Generate DSA keys
    generate_dsa_keys(&dsa_keypair);
    
    // Print the public key and private key
    printf("Private key: %s\n", BN_bn2hex(dsa_keypair->priv_key));
    printf("Public key: %s\n", BN_bn2hex(dsa_keypair->pub_key));

    // The message to sign
    const unsigned char *message = (unsigned char *)MESSAGE;
    unsigned int message_len = strlen(MESSAGE);
    
    // Sign the message
    sig_len = sign_message(dsa_keypair, message, message_len, sig);
    
    // Verify the signature
    verify_signature(dsa_keypair, message, message_len, sig, sig_len);
    
    // Cleanup
    DSA_free(dsa_keypair);
    
    return 0;
}

