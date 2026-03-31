#include "../include/Player.h"

void pclearitm(size_t i, void* v)
{
    if((Item*)v != NULL)
    {
        item_destroy((Item*)v);
    }
}
void pclearitmi(void* k, void* v)
{
    if((string*)k != NULL)
    {
        destroy_string((string*)k);
    }
}

Player player_init()
{
    Player plr = {._xposition = 1,
                  ._yposition = 1,
                  ._health = 100,
                  ._damage = 15,
                  ._symbol = 'P',
                  ._inventory = array_init(8, sizeof(Item)),
                  ._items = map_init(8, sizeof(string), sizeof(int))};

    return plr;
}

int player_getxpos(Player* player)
{
    if (player != NULL)
    {
        return player->_xposition;
    }
}
int player_getypos(Player* player)
{
    if (player != NULL)
    {
        return player->_yposition;
    }
}
int player_gethealth(Player* player)
{
    if (player != NULL)
    {
        return player->_health;
    }
}
int player_getdamage(Player* player)
{
    if (player != NULL)
    {
        return player->_damage;
    }
}
char player_getsymbol(Player* player)
{
    if (player != NULL)
    {
        return player->_symbol;
    }
}
map player_getitems(Player* player)
{
    if (player != NULL)
    {
        return player->_items;
    }
}
array player_getinventory(Player* player)
{
    if (player != NULL)
    {
        return player->_inventory;
    }
}

void player_move(Player* player, int x, int y)
{
    player->_xposition += x;
    player->_yposition += y;
}
void player_pickup(Player* player, Item* item)
{
    string itemname = item_getname(item);
    int amount = 0;

    ainsert(&player->_inventory, item);
    if (mfindv(&player->_items, &itemname, NULL))
    {
        amount = (*(int*)mgetv(&player->_items, &itemname) + 1);
        mset(&player->_items, &itemname, &amount);
    }
    else
    {
        amount = 1;
        minsert(&player->_items, &itemname, &amount);
    }
}
void player_takedamage(Player* player, int damage)
{
    if(damage > 0)
    {
        if(damage >= player->_health)
        {
            player->_health -= player->_health;
        }
        else
        {
            player->_health -= damage;
        }
    }
    else
    {
        printf("Damage is less than or equal to 0!\n");
    }
}

void player_destroy(Player* player)
{
    mforeach(&player->_items, pclearitmi);
    destroy_map(&player->_items);

    aforeach(&player->_inventory, pclearitm);
    destroy_array(&player->_inventory);

    player->_symbol = '\0';
    player->_damage = 0;
    player->_health = 0;
    player->_xposition = 0;
    player->_yposition = 0;
}