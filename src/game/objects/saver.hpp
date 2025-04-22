#pragma once

#include <string>
#include <vector>

#include "game_object.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/entity.hpp"

class Saver : public GameObject {
   public:
	Saver(const std::string &name, GameObject *parent = nullptr);
	virtual void Update(float deltaTime) override;
	void Save();
	void Load();
    void DeleteSave();
    static void SaveHighscore(int score, std::string user = "Player");
    static std::vector<std::pair<int, std::string>> LoadHighscore();

	static std::string mSaveFilePath;
	static std::string mSaveFileName;

	static bool mShouldLoad;
	static bool mReadyToLoad;
	static std::vector<Entity::SaveData> mEntitySaveData;
	static std::vector<std::vector<Dungeon::RoomData>> mRoomSaveData;
	static Dungeon::SaveData mDungeonSaveData;
    static Entity::SaveData mPlayerSaveData;
};
