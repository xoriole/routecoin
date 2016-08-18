#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecdsa.h"
#include "secp256k1.h"
#include "util.h"

/*
uint8_t *fromhex(const char *str) {}
char *tohex(const uint8_t *bin, size_t l) {}
 */

void printString(char * str) {
    printf("%s\n", str);
}

char * create_secret_value(char * mac_address_hex, char * pre_seed_hex) {
    uint8_t secret[32];

    uint8_t* mac = fromhex(mac_address_hex);
    memcpy(secret, mac, 6);
    uint8_t* preseed = fromhex(pre_seed_hex);
    memcpy(secret + 6, preseed, 26);
    return tohex(secret, 32);
}

char * create_priv_key(char * secret_value_hex, char * priv_key_wif) {
    uint8_t priv_key[32];
    char wif[53];

    memcpy(priv_key, fromhex(secret_value_hex), 32);
    ecdsa_get_wif(priv_key, 0x80, wif, sizeof (wif));
    memcpy(priv_key_wif, wif, 53);
}

void create_pub_key(char * priv_key, char * pub_key1) {
    uint8_t pub_key[65];
    ecdsa_get_public_key65(&secp256k1, priv_key, pub_key);
    memcpy(pub_key1, tohex(pub_key, 130), 130);
}

void get_public_address(char * public_key_hex, char * address) {
    uint8_t pub_key[65];

    memcpy(pub_key, fromhex(public_key_hex), 33);
    ecdsa_get_address(pub_key, 0, address, sizeof (address));

}

int main(int argc, char** argv) {
    char* mac = "0C28FCA386C7";
    char* pre_seed = "A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D";

    // step1: create secret value
    char* secret_value_hex = create_secret_value(mac, pre_seed);
    printString(secret_value_hex);

    // step2: create private key
    char priv_key_wif[53];
    create_priv_key(secret_value_hex, priv_key_wif);
    printString(priv_key_wif);

    // step3: public key from private key
    char pub_key_hex[130];
    create_pub_key(secret_value_hex, pub_key_hex);
    printString(pub_key_hex);

    // step4: address from public key
    char address[36];
    uint8_t * pub_key = fromhex(pub_key_hex);
    ecdsa_get_address(pub_key, 0, address, sizeof (address));
    printString(address);

}

int test_addresses() {
    char address[36];
    uint8_t pub_key[65];

    //    memcpy(pub_key, fromhex("0226659c1cf7321c178c07437150639ff0c5b7679c7ea195253ed9abda2e081a37"), 33);
    //    memcpy(pub_key, fromhex("d0de0aaeaefad02b8bdc8a01a1b8b11c696bd3d66a2c5f10780d95b7df42645cd85228a6fb29940e858e7e55842ae2bd115d1ed7cc0e82d934e929c97648cb0a"), 33);
    memcpy(pub_key, fromhex("04d0de0aaeaefad02b8bdc8a01a1b8b11c696bd3d66a2c5f10780d95b7df42645cd85228a6fb29940e858e7e55842ae2bd115d1ed7cc0e82d934e929c97648cb0a"), 65);
    ecdsa_get_address(pub_key, 0, address, sizeof (address));
    //printf("%s",pub_key);
    //    for (int i = 0; i < 36; i++) {
    //        printf("%c", address[i]);
    //    }
    printf("First:");
    printString(address);
    //ck_assert_str_eq(address, "139MaMHp3Vjo8o4x8N1ZLWEtovLGvBsg6s");

    /* compute public key from private key */

    //void ecdsa_get_public_key65(const ecdsa_curve *curve, const uint8_t *priv_key, uint8_t *pub_key);


    uint8_t priv_key[32];
    char wif[53];

    memcpy(priv_key, fromhex("0C28FCA386C7A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D"), 32);
    //    memcpy(priv_key, fromhex("00c4c5d791fcb4654a1ef5e03fe0ad3d9c598f9827"), 32);
    //    memcpy(priv_key, fromhex("47f7616ea6f9b923076625b4488115de1ef1187f760e65f89eb6f4f7ff04b012"), 32);
    ecdsa_get_wif(priv_key, 0x80, wif, sizeof (wif));
    printf("WIF:");
    printString(wif);
    //ck_assert_str_eq(wif, "KwntMbt59tTsj8xqpqYqRRWufyjGunvhSyeMo3NTYpFYzZbXJ5Hp");

    uint8_t publ_key[65];
    ecdsa_get_public_key65(&secp256k1, priv_key, publ_key);
    printString(tohex(publ_key, 65));


    /*
    int res;
    uint8_t decode[21];
    // byte      0 : address type
    // bytes  1-20 : pubkey hash 160
    res = ecdsa_address_decode("1JwSSubhmg6iPtRjtyqhUYYH7bZg3Lfy1T", decode);
    printString(tohex(decode,21));
    //ck_assert_int_eq(res, 1);
    //ck_assert_mem_eq(decode, fromhex("00c4c5d791fcb4654a1ef5e03fe0ad3d9c598f9827"), 21);
     */
    return (EXIT_SUCCESS);
}

