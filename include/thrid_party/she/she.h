#ifndef SHE_H
#define SHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/rand.h>


//
#define DEFAULT_K0 2048
#define DEFAULT_K1 60
#define DEFAULT_K2 300

#define M_BITS  40
#define R_BITS  80
#define L_BITS  820
#define P_BITS  1024
#define Q_BITS  33976


/* SHE keys */
typedef struct _SHE_key {
        BIGNUM *p, *q,*l,*n,*e_negative1,*l_2;
} SHE_key;

int she_generateRandomKeys(SHE_key *key, int k0, int k1, int k2, BN_CTX *ctx);
int she_encryptBignumRaw(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx);
int she_encryptBignumSupportNegative(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx);
int she_encryptBignumSupportNegative2(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx);
int she_encryptTeeStringBignum(char *str_c, BIGNUM *m);
int she_encryptTeeString(char *str_c, char *str_m);
int she_decryptBignum(BIGNUM *plain, const BIGNUM *c, const SHE_key *key, BN_CTX *ctx);
int she_addTest(const SHE_key *key, BN_CTX *ctx);
int she_mulTest(const SHE_key *key, BN_CTX *ctx);
int mulString(char *str1, char *str2,char *str3);
int addString(char *str1, char *str2,char *str3);
int she_decryptTeeString(char *str_plain, char *str_c);
int she_encryptTeeString(char *str_c, char *str_m);
int she_generateRandomKeysTee();        //注入tee内的全局变量
void bn_printfHex(BIGNUM *num);
void bn_printfDec(BIGNUM *num);

#endif






















