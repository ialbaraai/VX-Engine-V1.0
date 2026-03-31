#ifndef GAME_H

#define GAME_H

#include <stdio.h>
#include "../core/core.h"
#include "Player.h"
#include "Entity.h"
#include "Item.h"

typedef struct Game
{
    string _filepath;
    string _input;
    string _temp;
    bool _IS_COMBAT;
    bool _IS_COLLIDE;
    bool _IS_END;
    bool _IS_RUNNING;
    array _map;
    int _map_lines;
    Player _current_player;
    array _current_entities;
    int _current_entities_amount;
    array _current_items;
    int _current_items_amount;
    bool _is_combat;
} Game;

Game Game_init(const char*, Player*, array* entities, array* items, bool combat, bool collide, bool end);
void clear_screen();

void run(Game*);
void load_map(Game*);
void render(Game*);

void process_input(string*);

void update(Game*);
bool move_player(Game*, int, int);
void move_entities(Game*);
void check_collision(Game*);
void handle_combat(Game*, Entity*, size_t);

void is_game_over(Game*);

void Game_destroy(Game*);

#endif