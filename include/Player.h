#ifndef PLAYER_H

#define PLAYER_H

#include <stdio.h>
#include "../core/core.h"
#include "Item.h"

typedef struct Player
{
    char _symbol;
    int _xposition;
    int _yposition;
    int _health;
    int _damage;
    array _inventory;
    map _items;
} Player;

Player player_init();

int player_getxpos(Player*);
int player_getypos(Player*);
int player_gethealth(Player*);
int player_getdamage(Player*);
char player_getsymbol(Player*);
map player_getitems(Player*);
array player_getinventory(Player*);

void player_move(Player*, int x, int y);
void player_pickup(Player*, Item*);
void player_takedamage(Player*, int damage);

void player_destroy(Player*);

#endif