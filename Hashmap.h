//
// Created by dn on 4/4/22.
//

#ifndef HASHMAPCLIONCMAKE_HASHMAP_H
#define HASHMAPCLIONCMAKE_HASHMAP_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Config.h"
#include "HashFucntion.h"
#include "HashElem.h"
typedef struct HashHead
{
    size_t size;
    size_t inserted;
    struct HashElem *list;
} Hashmap;
struct HashHead *init();
int insert(Hashmap* hashmap,char* str,void* value);
void* get(Hashmap* hashmap,char* str);
bool delete(Hashmap* hashmap,char* str);
bool update(Hashmap* hashmap,char* str,void* value);
#endif //HASHMAPCLIONCMAKE_HASHMAP_H
