#ifndef ENTITY_H

#define ENTITY_H

#include "../core/core.h"

typedef struct Entity
{
    char _symbol;
    int _xposition;
    int _yposition;
    int _health;
    int _damage;
    int _id;
} Entity;

Entity entity_init(char symbol, int x, int y, int damage, int id);

int entity_getxpos(Entity*);
int entity_getypos(Entity*);
int entity_gethealth(Entity*);
int entity_getdamage(Entity*);
int entity_getid(Entity*);
char entity_getsymbol(Entity*);

void entity_move(Entity*, int x, int y);
void entity_takedamage(Entity*, int damage);

void clearent(size_t i, void* v);

void entity_destroy(Entity*);

#endif