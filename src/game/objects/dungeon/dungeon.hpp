#pragma once

#include <random>

#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon_room.hpp"

class Dungeon : public GameObject {
   public:
	struct RoomData {
		DungeonRoom::Type type = DungeonRoom::Type::NOT_SET;
		DungeonRoom::State state = DungeonRoom::State::UNVISITED;
	};

	static constexpr int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	using GameObject::GameObject;
	using GameObject::Render;
	using GameObject::Update;

	void Generate(int roomCount, unsigned long long seed);
	void EnterRoom(int x, int y);
	RoomData &GetRoomData(int x, int y);
	glm::vec2 GetRoomPosition() const;

   private:
	int mCurX, mCurY;
	DungeonRoom *mCurRoom;

	void SetRoomType(int x, int y, DungeonRoom::Type type);
	int CountAdjacentRooms(int x, int y);

	int mRoomCount;
	std::vector<std::vector<RoomData>> mRooms;

	std::mt19937_64 mRng;
	std::uniform_int_distribution<int> mDist;
};
