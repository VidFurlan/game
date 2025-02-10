#pragma once

#include <random>
#include <vector>

#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"

class DungeonGenerator {
   public:
	DungeonGenerator(unsigned long long seed, int roomCount, float roomRadius, glm::vec2 roomSizeRange);
	Dungeon *Generate();

   private:
	struct Room {
		glm::vec2 position;
		glm::vec2 size;
	};

	unsigned long long seed;
	int roomCount;
	float roomRadius;

	std::vector<Room> rooms;
	std::mt19937_64 rng;
};
