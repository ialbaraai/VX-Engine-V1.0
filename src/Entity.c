#include "../include/Entity.h"

#include <stdio.h>

Entity entity_init(char symbol, int x, int y, int damage, int id)
{
    Entity ent = {._symbol = symbol,
                  ._xposition = x,
                  ._yposition = y,
                  ._health = 100,
                  ._damage = damage,
                  ._id = id};

    return ent;
}

int entity_getxpos(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_xposition;
    }
}
int entity_getypos(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_yposition;
    }
}
int entity_gethealth(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_health;
    }
}
int entity_getdamage(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_damage;
    }
}
int entity_getid(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_id;
    }
}
char entity_getsymbol(Entity* entity)
{
    if (entity != NULL)
    {
        return entity->_symbol;
    }
}

void entity_move(Entity* entity, int x, int y)
{
    entity->_xposition += x;
    entity->_yposition += y;
}
void entity_takedamage(Entity* entity, int damage)
{
    if (damage > 0)
    {
        if (damage >= entity_gethealth(entity))
        {
            entity->_health -= entity->_health;
        }
        else
        {
            entity->_health -= damage;
        }
    }
    else
    {
        printf("Damage is less than 0!\n");
    }
}

void clearent(size_t i, void* v)
{
    if((Entity*)v != NULL)
    {
        entity_destroy((Entity*)v);
    }
}

void entity_destroy(Entity* entity)
{
    entity->_damage = 0;
    entity->_health = 0;
    entity->_id = 0;
    entity->_symbol = '\0';
    entity->_xposition = 0;
    entity->_yposition = 0;
}