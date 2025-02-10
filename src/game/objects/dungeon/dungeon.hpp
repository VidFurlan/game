#pragma once

#include "game_object.hpp"

class Dungeon : public GameObject {
   public:
	Dungeon(int n, int m);

   private:
	int n, m;
};
