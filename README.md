# VX Engine

A lightweight, CLI-based game engine written in pure C, built on [core](https://github.com/ialbaraai/core).

## Features
- Entity, item, and player systems
- Turn-based combat and collision detection
- Scene loading from `.vxe` files
- Inventory system with item pickup
- Built entirely on custom generic data structures (core)

## Dependencies
- core (included in `src/core.c`)

## Building
```bash
cmake . -B build
cd build
./app
```

## Usage
```c
Player player = player_init(); // Initialize your player
array entities = array_init(0, sizeof(Entity)); // Initialize the entities array using core arrays
array items    = array_init(0, sizeof(Item)); // Initialize the items array using core arrays

Entity e1 = entity_init(3, 1, 1, 1); // Initialize the entities
ainsert(&entities, &e1); // Insert entities into your entities array

Item itm = item_init("Hot Chocolate", 1, 3, 10); // Initialize the items
ainsert(&items, &itm); // Insert the items into your items array

Game game = Game_init("./assets/map.vxe", &player, &entities, &items, true, true, false); // Initialize your game struct
run(&game); // Run your game

Game_destroy(&game); // Destroy your game struct to free allocated memory
player_destroy(&player); // Destroy your player to free allocated memory

aforeach(&entities, clearent); // Destroy your entities to free allocated memory (clearent is a function that calls entity_destroy() for each entity)
aforeach(&items, clearitm); // Destroy your items to free allocated memory (clearitm is a function that calls item_destroy() for each item)
destroy_array(&entities); // Destroy your entities array to free allocated memory
destroy_array(&items); // Destroy your items array to free allocated memory
```

## Roadmap
- V1.1 — CLI designer and `.vxe` parser
- V2.0 — SDL3 rendering

---

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.

---

## Author

**albaraa** — [@ialbaraai](https://github.com/ialbaraai)
