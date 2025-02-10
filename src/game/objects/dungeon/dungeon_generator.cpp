#include "dungeon_generator.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <ratio>
#include <string>
#include <thread>

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "sprite_game_object.hpp"

DungeonGenerator::DungeonGenerator(unsigned long long seed, int roomCount, float roomRadius, glm::vec2 roomSizeRange) {
	this->seed = seed;
	this->roomCount = roomCount;
	this->roomRadius = roomRadius;

	rng = std::mt19937_64(seed);

	for (int i = 0; i < roomCount; i++) {
		float angle = (rng() % (4 * 360)) / 4.0f;
		float distance = (rng() % (int)(roomRadius * 1000)) / 1000.0f;
		std::uniform_real_distribution<float> roomGen(roomSizeRange.x, roomSizeRange.y);
		Room room = {glm::vec2(distance * cos(angle), distance * sin(angle)), glm::vec2(roomGen(rng), roomGen(rng))};
		rooms.push_back(room);
	}
}

Dungeon *DungeonGenerator::Generate() {
	Dungeon *dungeon = new Dungeon(10, 10);
	bool overlap = true;
	for (int i = 0; i < rooms.size(); i++) {
		for (int j = i + 1; j < rooms.size(); j++) {
			glm::vec2 pos1x = {rooms[i].position.x - rooms[i].size.x / 2, rooms[i].position.x + rooms[i].size.x / 2};
			glm::vec2 pos1y = {rooms[i].position.y - rooms[i].size.y / 2, rooms[i].position.y + rooms[i].size.y / 2};
			glm::vec2 pos2x = {rooms[j].position.x - rooms[j].size.x / 2, rooms[j].position.x + rooms[j].size.x / 2};
			glm::vec2 pos2y = {rooms[j].position.y - rooms[j].size.y / 2, rooms[j].position.y + rooms[j].size.y / 2};
			if (pos1x.x < pos2x.y && pos1x.y > pos2x.x && pos1y.x < pos2y.y && pos1y.y > pos2y.x) {
				rooms.erase(rooms.begin() + j);
				j--;
			}
		}
	}

	for (int i = 0; i < rooms.size(); i++) {
		Room room = rooms[i];
		dungeon->AddChild(new SpriteGameObject("Room" + std::to_string(i), "pixel", glm::vec3(room.position.x, room.position.y, 0.0f), room.size, {1.0f, 0.0f, 0.0f, 1.0f}));
	}

	return dungeon;
}
