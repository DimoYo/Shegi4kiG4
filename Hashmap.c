//
// Created by dn on 4/4/22.
//
#include "Hashmap.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Config.h"
#include "HashFucntion.h"
#include "HashElem.h"

struct HashHead *init()
{
    struct HashHead *init = (struct HashHead *)malloc(sizeof(struct HashHead));
    init->size = 0;
    init->list = NULL;
    init->inserted = 0;
    return init;
}
bool is_deleted(Hashmap* hashmap,size_t index){
    return (hashmap->list[index].type == 2);
}
bool has_value(Hashmap* hashmap,size_t index){
    return (hashmap->list[index].type == 1);
}
bool simple_insert(Hashmap* hashmap,unsigned long int hash_code_modulated,unsigned long int hash_code ,void* value){
    hashmap->list[hash_code_modulated].type |= 1;
    hashmap->list[hash_code_modulated].hash = hash_code;
    hashmap->list[hash_code_modulated].value = value;
    return true;
}
int insert_hash(Hashmap* hashmap,size_t sizer,void* value, unsigned long int k){
    ++hashmap->inserted;
    if(!(has_value(hashmap,sizer) || is_deleted(hashmap,sizer))){
        if(hashmap->list[sizer].hash == k){
            return Error_repeating;
        }
        simple_insert(hashmap,sizer,k,value);
        return Ok;
    }else{
        register size_t i = sizer;
        do{
            if(i>=hashmap->size){
                i = 0;
                continue;
            }
            if(hashmap->list[i].hash == k){
                --hashmap->inserted;
                return Error_repeating;
            }
            if(!(has_value(hashmap,i) || is_deleted(hashmap,i))){
                simple_insert(hashmap,i,k,value);
                return Ok;
            }
            ++i;
        }while(i != sizer);

    }

    --hashmap->inserted;
    return Error;
}

bool realoc_list(Hashmap* hashmap){
    if(!hashmap->size){
        hashmap->size = 0x1;
        hashmap->list = malloc(sizeof(struct HashElem)<<1);
        memset(hashmap->list,0,sizeof(struct HashElem)<<1);

    }else{
        struct HashElem* list_old = hashmap->list;
        hashmap->list = malloc(sizeof(struct HashElem)*(hashmap->size<<1));
        memset(hashmap->list,0,sizeof(struct HashElem)*(hashmap->size<<1));
        /*for(size_t i = 0;i<(hashmap->size<<1);++i){
            hashmap->list[i].type = 0;
        }*/
        hashmap->inserted &= 0;
        for(int i = 0;i<(hashmap->size);++i){
            insert_hash(hashmap,(list_old[i].hash)%(hashmap->size<<1),list_old[i].value,list_old[i].hash);
        }
        free(list_old);
    }
    hashmap->size<<=1;
    return Ok;
}
int find_bit(Hashmap* hashmap){
    register size_t sizer = hashmap->size;

    int i =0;
    while(sizer!=0){
        sizer<<=1;
        ++i;
    }

    return i;
}

int insert(Hashmap* hashmap,char* str,void* value){
    if(hashmap->size == hashmap->inserted){
        realoc_list(hashmap);
    }
    unsigned long int k = hash(str);
    size_t sizer = (k<<find_bit(hashmap))>>find_bit(hashmap);
    return insert_hash(hashmap,sizer,value,k);
}

void* get(Hashmap* hashmap,char* str){
    unsigned long int k = hash(str);
    size_t sizer = (k<<find_bit(hashmap))>>find_bit(hashmap);
    if(hashmap->list[sizer].hash == k){
        if(is_deleted(hashmap,sizer)){
            return NULL;
        }
        return hashmap->list[sizer].value;
    }else{
        register size_t i = sizer;
        do{
            if(i==hashmap->size){
                i = 0;
                continue;
            }
            if(hashmap->list[i].hash == k && !is_deleted(hashmap,i)){
                return hashmap->list[i].value;
            }
            ++i;
        }while(i != sizer);
    }
    return NULL;
}
bool delete(Hashmap* hashmap,char* str){
    unsigned long int k = hash(str);
    size_t sizer = (k<<find_bit(hashmap))>>find_bit(hashmap);
    if(hashmap->list[sizer].hash == k){
        hashmap->list[sizer].type=2;
        return Ok;
    }else{
        register size_t i = sizer;
        do{
            if(i==hashmap->size){
                i = 0;
                continue;
            }
            if(hashmap->list[i].hash == k ){
                hashmap->list[i].type=2;
                return Ok;
            }
            ++i;
        }while(i != sizer);
    }
    return Error;
}
bool update(Hashmap* hashmap,char* str,void* value){
    unsigned long int k = hash(str);
    size_t sizer = (k<<find_bit(hashmap))>>find_bit(hashmap);
    if(hashmap->list[sizer].hash == k){
        hashmap->list[sizer].value = value;
        return Ok;
    }else{
        register size_t i = sizer;
        do{
            if(i==hashmap->size){
                i = 0;
                continue;
            }
            if(hashmap->list[i].hash == k && !is_deleted(hashmap,i)){
                hashmap->list[i].value = value;
                return Ok;
            }
            ++i;
        }while(i != sizer);
    }
    return Error;
}
