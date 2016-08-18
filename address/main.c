
/* 
 * File:   main.c
 * Author: Sandip Pandey
 *
 */

#include "uECC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/sha.h"


#define SHA256_BLOCK_LENGTH  64
#define SHA256_DIGEST_LENGTH 32

void vli_print(char *str, uint8_t *vli, unsigned int size) {
    printf("%s ", str);
    for (unsigned i = 0; i < size; ++i) {
        printf("%02X ", (unsigned) vli[i]);
    }
    printf("\n");
}

void sha256(uint8_t * string, uint8_t hash[SHA256_DIGEST_LENGTH]) {
    //uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
//    int i = 0;
//    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
//    }
//    outputBuffer[64] = 0;
    //return hash;
    //hash2=hash;
}

void sha256_2(char *string, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

void sha256_hash_string (uint8_t hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
    int i = 0;

    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[64] = 0;
}

void private_key_to_WIF(uint8_t *private_key, uint8_t * WIF_private_key) {

}

int main0() {
    int i, c;
    uint8_t private[32] = {0};
    uint8_t public[64] = {0};
    uint8_t public_computed[64];

    uint8_t hash[32] = {0};
    uint8_t hash2[65] = {0};
    uint8_t sig[64] = {0};
    uECC_Curve curve = uECC_secp256k1();

    uint8_t private2[32] = {0x0C, 0x28, 0xFC, 0xA3, 0x86, 0xC7, 0xA2, 0x27, 0x60, 0x0B
        , 0x2F, 0xE5, 0x0B, 0x7C, 0xAE, 0x11, 0xEC, 0x86, 0xD3, 0xBF, 0x1F, 0xBE, 0x47, 0x1B
        , 0xE8, 0x98, 0x27, 0xE1, 0x9D, 0x72, 0xAA, 0x1D};
    uint8_t private3[33] = {0x80, 0x0C, 0x28, 0xFC, 0xA3, 0x86, 0xC7, 0xA2, 0x27, 0x60, 0x0B, 0x2F, 0xE5, 0x0B, 0x7C
        , 0xAE, 0x11, 0xEC, 0x86, 0xD3, 0xBF, 0x1F, 0xBE, 0x47, 0x1B, 0xE8, 0x98, 0x27, 0xE1, 0x9D, 0x72, 0xAA, 0x1D};
    uint8_t public2[64] = {0};


    static unsigned char buffer[32];
    static unsigned char buffer2[32];
    static unsigned char abuffer[65];
    static unsigned char abuffer2[65];
    sha256("\x80\x0C\x28\xFC\xA3\x86\xC7\xA2\x27\x60\x0B\x2F\xE5\x0B\x7C\xAE\x11\xEC\x86\xD3\xBF\x1F\xBE\x47\x1B\xE8\x98\x27\xE1\x9D\x72\xAA\x1D", buffer);
    sha256(buffer,buffer2);
    
    sha256_hash_string (buffer, abuffer);
    sha256_hash_string (buffer2, abuffer2);
            
    printf("%s\n", abuffer);
    printf("%s\n", abuffer2);

    sha256_2(private2, hash2);
    vli_print("Hash = ", hash2, sizeof (hash2));
    sha256_hash_string (buffer, abuffer);
    printf("%s\n", abuffer);

    if (!uECC_make_key(public, private, curve)) {
        printf("uECC_make_key() failed\n");

    }

    if (!uECC_compute_public_key(private, public_computed, curve)) {
        printf("uECC_compute_public_key() failed\n");
    }

    if (!uECC_compute_public_key(private2, public2, curve)) {
        printf("uECC_compute_public_key() failed\n");
    }


    //if (memcmp(public, public_computed, sizeof (public)) != 0) {
//    printf("Computed and provided public keys are not identical!\n");
//    vli_print("Computed public key = ", public_computed, sizeof (public_computed));
//    vli_print("Provided public key = ", public, sizeof (public));
//    vli_print("Private key = ", private, sizeof (private));
    //}


//    vli_print("Computed public key = ", public2, sizeof (public2));
    return 0;
}
