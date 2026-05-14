#ifndef ITEM_H

#define ITEM_H

#include "../core/core.h"

typedef struct Item
{
    char _symbol;
    string _name;
    int _xposition;
    int _yposition;
    int _damage;
} Item;

Item item_init(const char* name, int X, int Y, int damage);

int item_getxpos(Item*);
int item_getypos(Item*);
char item_getsymbol(Item*);
string item_getname(Item*);
const char* item_getnamecstr(Item*);

void clearitm(size_t i, void* v);

void item_destroy(Item*);

#endif