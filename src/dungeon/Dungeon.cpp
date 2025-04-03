//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <utils/priority_queue.h>
#include <iostream>
#include <unistd.h>
#include <ui/ui.hpp>

Dungeon::Dungeon() {}
Dungeon::~Dungeon() {}

void Dungeon::generateRandomDungeon()
{
    do {
        initializeCells(); // Initialize the cells with rock
        if (!generateRooms()) continue; // Generate rooms, reset if failed
        generateCorridors();
        generateStairs();
        placeCharacterRandomly(pc); // Place the player character randomly
        // placeNPCsRandomly(numNPCS); // Place NPCs randomly
        // numMonsterAlive = numNPCS; // Set the number of monsters alive
        break;
    } while (true);
}

bool Dungeon::placeNPCsRandomly(int numNPCS)
{
    for (int i = 0; i < numNPCS; i++) {
        NPC npc = NPC(Point(), Cell(), true, i);
        if (placeCharacterRandomly(npc)) {
            npcs.push_back(npc);
        }
    }
    return true;
}

int Dungeon::startGameplay(int numNPCS){
    // initialize_monsters(d);
    placeNPCsRandomly(numNPCS); // Place NPCs randomly
    numMonsterAlive = numNPCS; // Set the number of monsters alive
    int num_entities = getNPCs().size() + 1;

    // Create a priority queue for the entities
    // Only keys are needed, no data
    PriorityQueue *pq = pq_create(num_entities, num_entities, NULL, NULL);

    // Initialize the priority queue with the player and monsters
    // entity = (0) is the player, PLAYER_ID
    // entity = (i + 1), are the monsters, where i = index or monster_ID
    pq_insert(pq, 0, NULL, PLAYER_ID);
    for (int i = 0; i < getNPCs().size(); i++){
        pq_insert(pq, i + 1, NULL, 0); // all entities start at time 0
    }

    // render_grid(d); // Render the dungeon

    while (getPC().isAlive() && numMonsterAlive > 0) {

        int entity_id = pq_get_min_key(pq);
        int current_time = pq_get_priority(pq, entity_id);
        int next_time;


        if (entity_id == PLAYER_ID) { // Player's turn
            ui::render_grid(*this); // Render the dungeon
            ui::get_input(*this); // Get player input
            // printDungeon();
            // usleep(250000); // Sleep for 0.1 seconds

            // if (get_input(d) == -2){
            //     pq_destroy(pq);
            //     return -2;
            // }

        
            next_time = current_time + calculateTiming(pc.getSpeed());
        } else {
            // Check if the entity is alive, if not, skip
            if (!npcs[entity_id - 1].isAlive()) {
                pq_extract_min(pq);
                continue;
            }
            moveNPC(npcs[entity_id - 1]);
            next_time = current_time + calculateTiming(npcs[entity_id - 1].getSpeed());
        }
        
        // Reschedule entity's next turn
        pq_extract_min(pq);
        pq_insert(pq, entity_id, NULL, next_time);
    }

    ui::render_game_over(*this);
    pq_destroy(pq);

    return 1;
}

