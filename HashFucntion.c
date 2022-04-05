//
// Created by dn on 2/10/22.
//
#include <stdlib.h>
#include <memory.h>
#include "HashFucntion.h"


struct SeaHash
{
    unsigned long int state;
    unsigned long int k1;
    unsigned long int k2;
    unsigned long int k3;
    unsigned long int k4;
};

struct SeaHash* HashInit()
{
    struct SeaHash *hash = (struct SeaHash *)malloc(sizeof(struct SeaHash));
    hash->k4 = 1802886206017102246;
    hash->k3 = 8920607189712563318;
    hash->k2 = 80223359080497538;
    hash->k1 = 1669506508102161614;
    hash->state = hash->k1 ^ hash->k3;
    return hash;
}

unsigned long int func(unsigned long int val)
{
    unsigned long int p = 7993060983890856527;
    val = p * val;
    val = val ^ ((val >> 32) >> (val >> 62));
    val = p * val;
    return val;
}
size_t blockup(char *str, unsigned long int list[24])
{
    size_t size = strlen(str);
    memcpy(list, str, sizeof(char) * size);
    return size;
}

unsigned long int hash(char *str)
{
    unsigned long int list[16] = {0};

    struct SeaHash* hash = HashInit();
    size_t val = blockup(str, list);
    for (int i = 0; i < val; i += 4)
    {
        hash->k1 = func(list[i] ^ hash->k1);
        hash->k2 = func(list[i + 1] ^ hash->k2);
        hash->k3 = func(list[i + 2] ^ hash->k3);
        hash->k4 = func(list[i + 3] ^ hash->k4);
    }
    val = func(val ^ hash->k1 ^ hash->k2 ^ hash->k3 ^ hash->k4 ^ hash->state);
    free(hash);
    return val;
}