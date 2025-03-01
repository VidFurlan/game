#include "dungeon.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>

void Dungeon::Generate(int targetRoomCount, unsigned long long seed) {
	mRoomCount = targetRoomCount;
	mRng.seed(seed);
	mRooms = std::vector<std::vector<RoomData>>(2 * mRoomCount + 1, std::vector<RoomData>(2 * mRoomCount + 1));
	mDist = std::uniform_int_distribution<int>(0, 100);

	mCurX = 0;
	mCurY = 0;

	std::queue<std::pair<int, int>> q;
	q.push({0, 0});
	int roomCount = 0;

	std::vector<int> dirs = {0, 1, 2, 3};
	while (roomCount < mRoomCount) {
		if (roomCount != mRoomCount && q.empty()) {
			for (int i = -mRoomCount; i < mRoomCount; i++) {
				for (int j = -mRoomCount; j < mRoomCount; j++) {
					if (GetRoomData(i, j).type != DungeonRoom::Type::NOT_SET) q.push({i, j});
				}
			}
		}

		auto [x, y] = q.front();
		q.pop();

		if (CountAdjacentRooms(x, y) >= 2) continue;

		if (GetRoomData(x, y).type == DungeonRoom::Type::NOT_SET) {
			int roomType = mDist(mRng);
			if (roomType < 5) {
				SetRoomType(x, y, DungeonRoom::Type::TREASURE);
			} else if (roomType < 15) {
				SetRoomType(x, y, DungeonRoom::Type::EMPTY);
			} else {
				SetRoomType(x, y, DungeonRoom::Type::MONSTER);
			}
			roomCount++;
		}

		std::shuffle(dirs.begin(), dirs.end(), mRng);
		for (int i = 0; i < 4; i++) {
			int nx = x + directions[dirs[i]][0];
			int ny = y + directions[dirs[i]][1];
			if (GetRoomData(nx, ny).type == DungeonRoom::Type::NOT_SET) {
				if (mDist(mRng) & 1) continue;
				q.push({nx, ny});
			}
		}
	}

	SetRoomType(0, 0, DungeonRoom::Type::START);

	for (int i = -mRoomCount; i < mRoomCount; i++) {
		for (int j = -mRoomCount; j < mRoomCount; j++) {
			if (GetRoomData(i, j).type == DungeonRoom::Type::START)
				std::cout << "S";
			else if (GetRoomData(i, j).type == DungeonRoom::Type::MONSTER)
				std::cout << "M";
			else if (GetRoomData(i, j).type == DungeonRoom::Type::TREASURE)
				std::cout << "T";
			else if (GetRoomData(i, j).type != DungeonRoom::Type::NOT_SET)
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}

	((DungeonRoom *)AddChild(new DungeonRoom(this)))->SetRoom(0, 0);
}

void Dungeon::EnterRoom(int x, int y) {
	if (GetRoomData(x, y).type == DungeonRoom::Type::NOT_SET) return;
	mCurX = x;
	mCurY = y;
	mCurRoom = (DungeonRoom *)GetChild("DungeonRoom");
	if (GetRoomData(x, y).state == DungeonRoom::State::UNVISITED) {
		GetRoomData(x, y).state = DungeonRoom::State::VISITED;
	}
	((DungeonRoom *)GetChild("DungeonRoom"))->SetRoom(x, y);
}

void Dungeon::SetRoomType(int x, int y, DungeonRoom::Type type) {
	if (x < -mRoomCount || x >= mRoomCount || y < -mRoomCount || y >= mRoomCount) throw std::runtime_error("Invalid room coordinates");
	mRooms[x + mRoomCount][y + mRoomCount].type = type;
	if (mRoomConfigs.find(type) != mRoomConfigs.end())
		mRooms[x + mRoomCount][y + mRoomCount].roomContent = mDist(mRng) % mRoomConfigs.at(type).size();
	else
		mRooms[x + mRoomCount][y + mRoomCount].roomContent = -1;
}

Dungeon::RoomData &Dungeon::GetRoomData(int x, int y) {
	if (x < -mRoomCount || x >= mRoomCount || y < -mRoomCount || y >= mRoomCount) throw std::runtime_error("Invalid room coordinates");
	return mRooms[x + mRoomCount][y + mRoomCount];
}

glm::vec2 Dungeon::GetRoomPosition() const {
	return glm::vec2(mCurX, mCurY);
}

int Dungeon::CountAdjacentRooms(int x, int y) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + directions[i][0];
		int ny = y + directions[i][1];
		if (nx < -mRoomCount || nx >= mRoomCount || ny < -mRoomCount || ny >= mRoomCount) continue;
		if (GetRoomData(nx, ny).type != DungeonRoom::Type::NOT_SET) count++;
	}
	return count;
}
