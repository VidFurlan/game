#include "saver.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "game.hpp"
#include "game_object.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/entities/entity.hpp"
#include "objects/player.hpp"

bool Saver::mShouldLoad = false;
bool Saver::mReadyToLoad = false;
std::vector<Entity::SaveData> Saver::mEntitySaveData;
std::vector<std::vector<Dungeon::RoomData>> Saver::mRoomSaveData;
Dungeon::SaveData Saver::mDungeonSaveData;
Entity::SaveData Saver::mPlayerSaveData;

Saver::Saver(const std::string &name, GameObject *parent)
    : GameObject(name, parent) {
}

void Saver::Update(float deltaTime) {
	Save();
}

void Saver::Save() {
	if (Game::GetInstance().GetState() != GameState::GAME_ACTIVE) return;

	std::filesystem::create_directory(mSaveFilePath);
	std::ofstream saveFile(mSaveFilePath + mSaveFileName, std::ios::binary);
	if (!saveFile.is_open()) {
		throw std::runtime_error("Failed to open save file for writing");
	}

	GameObject *scene = Game::GetInstance().GetActiveScene();

	// Dungeon save data
	Dungeon *dungeon = (Dungeon *)(scene->GetChild("Dungeon"));
	if (dungeon == nullptr) {
		throw std::runtime_error("Dungeon not found");
	}
	Dungeon::SaveData dungeonSaveData = dungeon->GetSaveData();
	saveFile.write(reinterpret_cast<const char *>(&dungeonSaveData), sizeof(Dungeon::SaveData));
	for (int i = -dungeonSaveData.roomCount; i < dungeonSaveData.roomCount; i++) {
		for (int j = -dungeonSaveData.roomCount; j < dungeonSaveData.roomCount; j++) {
			Dungeon::RoomData roomData = dungeon->GetRoomData(i, j);
			saveFile.write(reinterpret_cast<const char *>(&roomData), sizeof(Dungeon::RoomData));
		}
	}

    // Player save data
    Entity::SaveData playerSaveData;
    playerSaveData.type = EntityType::PLAYER;
    playerSaveData.position = scene->GetChild("Player")->GetPosition();
    playerSaveData.health = ((Entity *)scene->GetChild("Player"))->GetHealth();
    saveFile.write(reinterpret_cast<char *>(&playerSaveData), sizeof(Entity::SaveData));
    saveFile.write(reinterpret_cast<char *>(&Player::mCatCount), sizeof(int));
    saveFile.write(reinterpret_cast<char *>(&Player::mKillCount), sizeof(int));

	// Entity save data
	GameObject *entities = dungeon->GetChild("DungeonRoom")->GetChild("Entities");
	for (auto [name, child] : *entities->GetChildren()) {
		Entity *entity = dynamic_cast<Entity *>(child);
		Entity::SaveData entitySaveData = entity->GetSaveData();
		saveFile.write(reinterpret_cast<const char *>(&entitySaveData), sizeof(Entity::SaveData));
	}

	saveFile.close();
}

void Saver::Load() {
	std::ifstream saveFile(mSaveFilePath + mSaveFileName, std::ios::binary);
	if (!saveFile.is_open()) {
		return;
	}

	GameObject *scene = Game::GetInstance().GetActiveScene();

	// Dungeon load data
	saveFile.read(reinterpret_cast<char *>(&mDungeonSaveData), sizeof(Dungeon::SaveData));
    mRoomSaveData.clear();
    mRoomSaveData.resize(mDungeonSaveData.roomCount * 2, std::vector<Dungeon::RoomData>(mDungeonSaveData.roomCount * 2));
	for (int i = -mDungeonSaveData.roomCount; i < mDungeonSaveData.roomCount; i++) {
		for (int j = -mDungeonSaveData.roomCount; j < mDungeonSaveData.roomCount; j++) {
			Dungeon::RoomData roomData;
			saveFile.read(reinterpret_cast<char *>(&roomData), sizeof(Dungeon::RoomData));
			mRoomSaveData[i + mDungeonSaveData.roomCount][j + mDungeonSaveData.roomCount] = roomData;
		}
	}

    // Player load data
    saveFile.read(reinterpret_cast<char *>(&mPlayerSaveData), sizeof(Entity::SaveData));
    saveFile.read(reinterpret_cast<char *>(&Player::mCatCount), sizeof(int));
    saveFile.read(reinterpret_cast<char *>(&Player::mKillCount), sizeof(int));

	// Entity load data
    mEntitySaveData.clear();
    Entity::SaveData entitySaveData;
	while (saveFile.read(reinterpret_cast<char *>(&entitySaveData), sizeof(Entity::SaveData))) {
		mEntitySaveData.push_back(entitySaveData);
	}

	saveFile.close();

	mReadyToLoad = true;
	mShouldLoad = false;
}

void Saver::DeleteSave() {
    std::filesystem::remove(mSaveFilePath + mSaveFileName);
    mShouldLoad = false;
    mReadyToLoad = false;
    mEntitySaveData.clear();
    mRoomSaveData.clear();
}
