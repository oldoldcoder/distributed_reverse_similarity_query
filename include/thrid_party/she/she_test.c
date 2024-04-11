#include "she.h"
// #include "../TestEnclave.h"
#define TEST_TIMES 10000
extern SHE_key KEY;



int she_functionTest()
{
        int ret = 0;
        SHE_key key;

        BN_CTX *ctx = BN_CTX_new();
        BN_CTX_start(ctx);

        int space_num;
        char *tmp1, *tmp2;
        BIGNUM *random_plain1 = BN_CTX_get(ctx);
        BIGNUM *random_plain2 = BN_CTX_get(ctx);
        BIGNUM *cipher1 = BN_CTX_get(ctx);
        // BIGNUM *cipher2 = BN_CTX_get(ctx);
        char *plain_str;
        BIGNUM *decrypted_random = BN_CTX_get(ctx);
        // BIGNUM *tmp_result1 = BN_CTX_get(ctx);
        // BIGNUM *tmp_result2 = BN_CTX_get(ctx);

        if (!BN_rand(random_plain1, DEFAULT_K1, 0, 0))
                goto end;
        if (!BN_rand(random_plain2, DEFAULT_K1, 0, 0))
                goto end;

        if (!she_generateRandomKeys(&key, DEFAULT_K0, DEFAULT_K1, DEFAULT_K2, ctx))
                goto end;

        she_encryptBignumSupportNegative(cipher1, random_plain1, &key, ctx);
        she_decryptBignum(decrypted_random, cipher1, &key, ctx);
        printf("Random plain number: ");
        bn_printfHex(random_plain1);
        printf("Decryted number:");
        bn_printfHex(decrypted_random);
        if (BN_cmp(decrypted_random, random_plain1) == 0)
        {
                printf("Bignum Interface Encryption and Decrytpion OK!\n");
        }
        else
        {
                printf("Bignum Interface Encryption and Decrytpion Error!\n");
        }

        space_num = 1025;
        she_generateRandomKeysTee();
        tmp1 = (char *)malloc(sizeof(char) * space_num);
        tmp2 = (char *)malloc(sizeof(char) * space_num);
        plain_str = (char *)malloc(sizeof(char) * space_num);
        memcpy(plain_str, "AA", 3);

        if (!she_encryptTeeString(tmp1, plain_str))
                goto end;
        if (space_num <= strlen(tmp1))
                printf("space is not enough\n");
        if (!she_decryptTeeString(tmp2, tmp1))
                goto end;
        if (space_num <= strlen(tmp2)) // 解密出来是明文，这个长度比密文小很多
                printf("space is not enough\n");
        // printf("len :%d\n",strlen(tmp2));
        printf("Plain: ");
        printf("%s\n", plain_str);
        printf("Decrypted: ");
        printf("%s\n", tmp2);
        if (memcmp(tmp2, plain_str, strlen(plain_str)) == 0)
        {
                printf("EncrytTeeString and DecryptTeeString OK!\n");
        }
        else
        {
                printf("EncrytTeeString and DecryptTeeString Error!\n");
        }

        ///////////// Addition test 同态加正确性测试
        // E(m1)+E(m2) = E(m1+m2)
        if (!she_addTest(&key, ctx))
                goto end;
        ///////////// Multiplication test 同态乘法正确性测试
        // E(m1)*E(m2) = E(m1*m2)
        if (!she_mulTest(&key, ctx))
                goto end;
        BN_CTX_end(ctx);
        BN_CTX_free(ctx);
        ret = 1;
end:
        if (!ret)
        {
                printf("FunctionTest Error\n");
        }
        return ret;
}


int she_test()
{
        int ret = 0;
        if (!she_functionTest())
                goto END_LABEL;

        ret = 1;
END_LABEL:
        if (!ret)
        {
                printf("sheTest Error\n");
        }
        return 1;
}

void bnTest(BIGNUM *t1, BIGNUM *t2, BIGNUM *t3, BIGNUM *mod1)
{
        // BN_add(t1, t2, t3);
        // printf("ENCLAVE:");
        bn_printfHex(t1);
        bn_printfHex(t2);
        bn_printfHex(t3);
        BN_set_word(t1, 111);
        BN_add_word(t1, 2);
        BN_mul_word(t1, 2);

        BIGNUM *tmp1 = BN_new();
        BIGNUM *mod = BN_new();
        BIGNUM *t22 = BN_new();
        BIGNUM *t33 = BN_new();
        BN_CTX *ctx = BN_CTX_new();
        BN_CTX_start(ctx);
        BN_set_word(mod, 99);
        BN_copy(t22, t2);
        BN_copy(t33, t3);
        // BN_add(tmp1, t2, t3);
        BN_mod_mul(tmp1, t2, t3, mod1, ctx);
        // printf("\n");
        BIGNUM *haha = BN_new();
        BN_set_word(haha, 10000000);
        t1 = BN_copy(t1, haha);
        // BN_copy(t1, tmp1);
        BN_free(tmp1);
        BN_CTX_end(ctx);
        BN_CTX_free(ctx);
}

void she_encryptBignumRaw2Test(BIGNUM *c, BIGNUM *m)
{
        BN_CTX *ctx = BN_CTX_new();
        BN_CTX_start(ctx);
        BIGNUM *res = BN_new();
        BIGNUM *dec = BN_CTX_get(ctx);
        she_encryptBignumRaw2(res, m, &KEY, ctx);
        printf("enlcave加密后的结果为：\n");
        bn_printfHex(res);
        char *resStr = BN_bn2hex(res);
        int cut_length = 9000;
        char *tmp_part1 = (char *)malloc(sizeof(char) * cut_length + 1);
        memset(tmp_part1, 0, cut_length + 1);
        memcpy(tmp_part1, resStr, cut_length);
        BIGNUM *res2 = BN_new();
        BN_hex2bn(&res2, tmp_part1);

        printf("enlcave解密后的结果为：\n");
        she_decryptBignum(dec, res, &KEY, ctx);
        bn_printfDec(dec);
        // BIGNUM *haha = BN_new();
        // BN_set_word(haha, 10000000);
        // BN_set_word(res, 10000000000);
        c = BN_copy(c, res2);
        BN_CTX_end(ctx);
        BN_CTX_free(ctx);
        OPENSSL_free(resStr);
}
