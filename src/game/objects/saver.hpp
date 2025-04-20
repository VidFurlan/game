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

	static bool mShouldLoad;
	static bool mReadyToLoad;
	static std::vector<Entity::SaveData> mEntitySaveData;
	static std::vector<std::vector<Dungeon::RoomData>> mRoomSaveData;
	static Dungeon::SaveData mDungeonSaveData;

   private:
	const std::string mSaveFilePath = "saves/";
	const std::string mSaveFileName = "save";
};
