#include "dungeon.hpp"
#include "game_object.hpp"

Dungeon::Dungeon(int n, int m) : GameObject("Dungeon") {
    this->n = n;
    this->m = m;
}
