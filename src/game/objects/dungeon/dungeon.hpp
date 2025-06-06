#pragma once

#include <random>
#include <unordered_map>

#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/entity.hpp"

class Dungeon : public GameObject {
   public:
	struct RoomData {
		DungeonRoom::Type type = DungeonRoom::Type::NOT_SET;
		DungeonRoom::State state = DungeonRoom::State::UNVISITED;
		int roomContent = 0;
	};

	static constexpr int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	using GameObject::GameObject;
	using GameObject::Render;
	using GameObject::Update;

	void Generate(int roomCount, unsigned long long seed);
	void EnterRoom(int x, int y);
	RoomData GetRoomData(int x, int y) const;
	glm::vec2 GetRoomPosition() const;

	void SetRoomState(int x, int y, DungeonRoom::State state);

	struct SaveData {
		int roomCount;
		unsigned long long seed;
		int curX;
		int curY;
	};

    SaveData GetSaveData() const;

   private:
	void SetRoomType(int x, int y, DungeonRoom::Type type);
	int CountAdjacentRooms(int x, int y);

	DungeonRoom *mCurRoom;
	int mCurX = 0;
	int mCurY = 0;

	int mRoomCount;
	std::vector<std::vector<RoomData>> mRooms;

	std::mt19937_64 mRng;
	std::uniform_int_distribution<int> mDist;
    unsigned long long mSeed;

   public:
	struct EntityData {
		EntityType type;
		glm::vec2 position;
	};

	static const std::unordered_map<DungeonRoom::Type, std::vector<std::vector<EntityData>>> mRoomConfigs;
};
