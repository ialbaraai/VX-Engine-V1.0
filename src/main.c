#include <stdio.h>
#include "../include/Game.h"

int main(void)
{
    Player player = player_init();
    array entarr = array_init(0, sizeof(Entity));
    array itemarr = array_init(0, sizeof(Item));

    Entity ent = entity_init(3, 1, 1, 1);
    Entity ent2 = entity_init(3, 3, 1, 1);

    ainsert(&entarr, &ent);
    ainsert(&entarr, &ent2);

    Item itm = item_init("Hot Chocolate", 1, 3, 10);

    ainsert(&itemarr, &itm);

    Game game = Game_init("./assets/test.vxe", &player, &entarr, &itemarr, true, true, false);

    run(&game);

    Game_destroy(&game);

    player_destroy(&player);

    aforeach(&entarr, clearent);
    aforeach(&itemarr, clearitm);

    destroy_array(&itemarr);
    destroy_array(&entarr);

    return 0;
}