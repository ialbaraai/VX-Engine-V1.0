#include "../include/Item.h"

Item item_init(const char* name, int x, int y, int damage)
{
    Item i = {._name = string_initd(strlen(name) + 1, name),
              ._xposition = x,
              ._yposition = y,
              ._damage = damage,
              ._symbol = name[0]};

    return i;
}
int item_getxpos(Item* item)
{
    if (item != NULL)
    {
        return item->_xposition;
    }
}
int item_getypos(Item* item)
{
    if (item != NULL)
    {
        return item->_yposition;
    }
}
char item_getsymbol(Item* item)
{
    if (item != NULL)
    {
        return item->_symbol;
    }
}
string item_getname(Item* item)
{
    if (item != NULL)
    {
        return item->_name;
    }
}
const char* item_getnamecstr(Item* item)
{
    if (item != NULL)
    {
        return string_get(&item->_name);
    }
}

void clearitm(size_t i, void* v)
{
    if((Item*)v != NULL)
    {
        item_destroy((Item*)v);
    }
}

void item_destroy(Item* item)
{
    item->_symbol = '\0';

    destroy_string(&(item->_name));

    item->_xposition = 0;
    item->_yposition = 0;
    item->_damage = 0;
}