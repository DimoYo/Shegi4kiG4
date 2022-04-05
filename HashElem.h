//
// Created by dn on 4/4/22.
//

#ifndef HASHMAPCLIONCMAKE_HASHELEM_H
#define HASHMAPCLIONCMAKE_HASHELEM_H


struct HashElem
{
    char *value;
    unsigned long int hash;
    unsigned short int type : 2;
};


#endif //HASHMAPCLIONCMAKE_HASHELEM_H
