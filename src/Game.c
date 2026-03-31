#include "../include/Game.h"

void renderInvLoop(void* key, void* value)
{
    string* item = (string*)key;
    int* amount = (int*)value;

    printf(" %s x%d.", string_get(item), *amount);
}
void gclearstr(size_t i, void* v)
{
    if ((string*)v != NULL)
    {
        destroy_string((string*)v);
    }
}

Game Game_init(const char* filepath, Player* player, array* entities, array* items, bool combat, bool collide, bool end)
{
    Game game;

    game._map = array_init(64, sizeof(string));
    game._filepath = string_initd(64, filepath);
    game._input = string_init(4);
    game._current_player = *player;
    
    game._temp = string_init(64);
    
    game._current_entities = array_init(alength(entities), sizeof(Entity));
    game._current_items = array_init(alength(items), sizeof(Item));

    for (size_t i = 0; i < alength(entities); i++)
    {
        ainsert(&game._current_entities, (Entity*)aget(entities, i));
        game._current_entities_amount++;
    }

    for (size_t i = 0; i < alength(items); i++)
    {
        ainsert(&game._current_items, (Item*)aget(items, i));
        game._current_items_amount++;
    }

    game._map_lines = 0;
    game._IS_RUNNING = true;
    game._is_combat = false;

    game._IS_COLLIDE = collide;
    game._IS_COMBAT = combat;
    game._IS_END = end;

    load_map(&game);

    return game;
}
void clear_screen()
{
    printf("\033[2J\033[1;1H");
}

void run(Game* game)
{
    while (game->_IS_RUNNING)
    {
        render(game);

        if (game->_IS_COLLIDE)
        {
            check_collision(game);
        }

        update(game);
        move_entities(game);
    }
}
void load_map(Game* game)
{
    FILE* file = fopen(string_get(&game->_filepath), "r");

    if (file == NULL)
    {
        printf("Failed to open file: %s!\n", string_get(&game->_filepath));

        return;
    }

    string line = string_init(64);

    while(fgets(string_getf(&line), 64, file))
    {
        string curline = string_initd(string_length(&line) + 1, string_get(&line));
        ainsert(&game->_map, &curline);
        game->_map_lines++;
    }

    destroy_string(&line);
    fclose(file);
}
void render(Game* game)
{
    clear_screen();

    printf("-----------------------------------\n");

    for(size_t y = 0; y < alength(&game->_map); y++)
    {
        string_copy(&game->_temp, (string*)aget(&game->_map, y));

        for (size_t x = 0; x < string_length((string*)aget(&game->_map, y)); x++)
        {
            for (size_t i = 0; i < alength(&game->_current_entities); i++)
            {
                if (entity_getxpos((Entity*)aget(&game->_current_entities, i)) == x && entity_getypos((Entity*)aget(&game->_current_entities, i)) == y)
                {
                    string_replacec(&game->_temp, entity_getsymbol((Entity*)aget(&game->_current_entities, i)), x);
                }
            }

            for (size_t i = 0; i < alength(&game->_current_items); i++)
            {
                if (item_getxpos((Item*)aget(&game->_current_items, i)) == x && item_getypos((Item*)aget(&game->_current_items, i)) == y)
                {
                    string_replacec(&game->_temp, item_getsymbol((Item*)aget(&game->_current_items, i)), x);
                }
            }

            if (player_getxpos(&game->_current_player) == x && player_getypos(&game->_current_player) == y)
            {
                    string_replacec(&game->_temp, player_getsymbol(&game->_current_player), x);
            }
        }

        printf("%s", string_get(&game->_temp));
    }

    printf("\nInventory:");
    map plritms = player_getitems(&game->_current_player);
    mforeach(&plritms, renderInvLoop);

    printf("\nPlayer Health: %d/100\n", player_gethealth(&game->_current_player));

    printf("-----------------------------------\n");
}

void process_input(string* str)
{
    printf("Click any key (Q to quit): ");
    string_input(str);
}

void update(Game* game)
{
    if (game->_IS_RUNNING)
    {
        bool result = false;

        process_input(&game->_input);
        string_lower(&game->_input);

        if (strcmp(string_get(&game->_input), "w") == 0)
        {
            result = move_player(game, 0, -1);
        }
        else if (strcmp(string_get(&game->_input), "s") == 0)
        {
            result = move_player(game, 0, 1);
        }
        else if (strcmp(string_get(&game->_input), "a") == 0)
        {
            result = move_player(game, -1, 0);
        }
        else if (strcmp(string_get(&game->_input), "d") == 0)
        {
            result = move_player(game, 1, 0);
        }
        else if (strcmp(string_get(&game->_input), "q") == 0)
        {
            result = true;
            string confirmation = string_init(4);

            printf("Are you sure (y/n)?: ");
            string_input(&confirmation);

            string_lower(&confirmation);

            if (strcmp(string_get(&confirmation), "y") == 0)
            {
                game->_IS_RUNNING = false;
            }
            
            destroy_string(&confirmation);
        }
        else
        {
            printf("Invalid input!\n");
            result = true;
        }

        if (result == false)
        {
            printf("Invalid move!\n");
        }
    }
}
bool move_player(Game* game, int x, int y)
{
    int newX = player_getxpos(&game->_current_player) + x;
    int newY = player_getypos(&game->_current_player) + y;

    if (newY >= 0 && newY < game->_map_lines)
    {
        if (newX >= 0 && newX < string_length((string*)aget(&game->_map, newY)))
        {
            if (string_at((string*)aget(&game->_map, newY), newX) == '#')
            {
                return false;
            }
            else
            {
                player_move(&game->_current_player, x, y);

                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
void move_entities(Game* game)
{

}
void check_collision(Game* game)
{
    for (size_t i = 0; i < alength(&game->_current_entities); i++)
    {
        Entity* entity = (Entity*)aget(&game->_current_entities, i);
        
        if (player_getxpos(&game->_current_player) == entity_getxpos(entity) && player_getypos(&game->_current_player) == entity_getypos(entity))
        {
            if (game->_IS_COMBAT)
            {
                handle_combat(game, entity, i);

                break;
            }
        }
    }

    for (size_t i = 0; i < alength(&game->_current_items); i++)
    {
        Item* item = (Item*)aget(&game->_current_items, i);

        if (player_getxpos(&game->_current_player) == item_getxpos(item) && player_getypos(&game->_current_player) == item_getypos(item))
        {
            player_pickup(&game->_current_player, item);
            aremove(&game->_current_items, i);

            break;
        }
    }
}
void handle_combat(Game* game, Entity* entity, size_t index)
{
    printf("A monster!\n");

    bool PlayerAlive = true;
    bool EntityAlive = true;
    bool runResult = false;

    printf("Press Enter to continue...");
    getchar();

    
    do
    {
        printf("Player Health: %d/100\n", player_gethealth(&game->_current_player));
        printf("Enemy Health: %d/100\n", entity_gethealth(entity));

        printf("What do you want to do? [F]ight or [R]un: ");
        string_input(&game->_input);
        string_lower(&game->_input);

        if (strcmp(string_get(&game->_input), "f") == 0)
        {
            printf("Player chose to fight!\n\n");

            entity_takedamage(entity, player_getdamage(&game->_current_player));

            printf("Player deals %d damage to Enemy!\n", player_getdamage(&game->_current_player));
        
            if (entity_gethealth(entity) <= 0)
            {
                EntityAlive = false;

                break;
            }

            player_takedamage(&game->_current_player, entity_getdamage(entity));

            printf("Enemy deals %d damage to Player!\n", entity_getdamage(entity));

            if (player_gethealth(&game->_current_player) <= 0)
            {
                PlayerAlive = false;

                break;
            }   
        }
        if (strcmp(string_get(&game->_input), "r") == 0)
        {
            runResult = move_player(game, 2, 0);

            if (runResult == false)
            {
                runResult = move_player(game, -2, 0);

                if (runResult == false)
                {
                    runResult = move_player(game, 0, 2);

                    if (runResult == false)
                    {
                        runResult = move_player(game, 0, -2);
                    }
                }
            }

            break;
        }
        else
        {
            printf("Invalid move!\n");
        }
    } while (PlayerAlive && EntityAlive);
    
    if (PlayerAlive == false)
    {
        if (game->_IS_END)
        {
            is_game_over(game);
        }
    }
    else if (EntityAlive == false)
    {
        printf("You survived!\n");

        aremove(&game->_current_entities, index);
    }
}

void is_game_over(Game* game)
{
    if (player_gethealth(&game->_current_player) <= 0)
    {
        game->_IS_RUNNING = false;
        printf("Game over... you lost!\n");
    }
}

void Game_destroy(Game* game)
{
    destroy_string(&game->_temp);
    destroy_string(&game->_filepath);
    destroy_string(&game->_input);

    aforeach(&game->_map, gclearstr);
    destroy_array(&game->_map);
    aforeach(&game->_current_entities, clearent);
    destroy_array(&game->_current_entities);
    aforeach(&game->_current_items, clearitm);
    destroy_array(&game->_current_items);

    game->_IS_COMBAT = false;
    game->_IS_COLLIDE = false;
    game->_IS_END = false;
    game->_IS_RUNNING = false;
    game->_map_lines = 0;
    game->_current_entities_amount = 0;
    game->_current_items_amount = 0;
    game->_is_combat = 0;
}