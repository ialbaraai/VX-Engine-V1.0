# VX Engine

A lightweight, CLI-based game engine written in pure C, built on top of [core](https://github.com/ZynarX/core).

## Features
- Entity, item, and player systems
- Turn-based combat and collision detection
- Scene loading from `.vxe` files
- Inventory system with item pickup
- Built entirely on custom generic data structures (corelib)

## Dependencies
- core (included in `src/core.c`)

## Building
```bash
make #build
make clean #clean
make re #rebuild
```

## Usage
```c
Player player = player_init();
array entities = array_init(0, sizeof(Entity));
array items    = array_init(0, sizeof(Item));

Entity e1 = entity_init(3, 1, 1, 1);
ainsert(&entities, &e1);

Item itm = item_init("Hot Chocolate", 1, 3, 10);
ainsert(&items, &itm);

Game game = Game_init("./assets/map.vxe", &player, &entities, &items, true, true, false);
run(&game);

Game_destroy(&game);
player_destroy(&player);

aforeach(&entities, clearent);
aforeach(&items, clearitm);
destroy_array(&entities);
destroy_array(&items);
```

## Roadmap
- V1.1 — CLI designer and `.vxe` parser
- V2.0 — SDL3 rendering

## License
MIT
