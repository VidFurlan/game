#include "replay_manager.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "game.hpp"
#include "game_object.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/entity.hpp"
#include "objects/entities/entity_factory.hpp"
#include "objects/player.hpp"

ReplayManager::ReplayManager(std::string name, GameObject *parent)
    : GameObject(name, parent) {
    Init();
}

void ReplayManager::Init() {
    SetZIndex(900);
	remove("replay");
	mTime = 0.0f;
	mWaitedTime = 0.0f;
}

void ReplayManager::Update(float deltaTime) {
	mTime += deltaTime;
	mWaitedTime += deltaTime;
	if (Game::GetInstance().GetState() == GameState::GAME_ACTIVE && mWaitedTime >= 1.0f / 60.0f) {
		std::ofstream replayFile("replay", std::ios::binary | std::ios::app);
		if (!replayFile.is_open()) {
			throw std::runtime_error("Failed to open replay file");
		}

		ReplayDataHeader header;
		header.time = mTime;
		header.roomX = ((Dungeon *)Game::GetInstance().GetActiveScene()->GetChild("Dungeon"))->GetRoomPosition().x;
		header.roomY = ((Dungeon *)Game::GetInstance().GetActiveScene()->GetChild("Dungeon"))->GetRoomPosition().y;
		header.playerData = ((Entity *)Game::GetInstance().GetActiveScene()->GetChild("Player"))->GetSaveData();
		replayFile.write(reinterpret_cast<const char *>(&header), sizeof(header));

		auto children = Game::GetInstance().GetActiveScene()->GetChild("Dungeon")->GetChild("DungeonRoom")->GetChild("Entities")->GetChildren();
		int childrenCount = children->size();
		replayFile.write(reinterpret_cast<const char *>(&childrenCount), sizeof(childrenCount));
		for (const auto &[name, entity] : *children) {
			Entity::SaveData data;
			data = ((Entity *)entity)->GetSaveData();
			replayFile.write(reinterpret_cast<const char *>(&data), sizeof(data));
		}
		replayFile.close();
	}
}

void ReplayManager::LateUpdate(float deltaTime) {
	if (Game::GetInstance().GetState() == GameState::GAME_REPLAY) {
		if (!mReplayStarted) {
			mReplayStarted = true;
			mWaitedTime = 0.0f;
			mTime = 0.0f;
			mFilePosition = 0;
            mRoomX = INT_MAX;
            mRoomY = INT_MAX;

            if (!GetChild("PlayerDummy")) new Player("PlayerDummy", this);
            ((Player *)GetChild("PlayerDummy"))->SetTag("XXXPlayer");
            Game::GetInstance().GetActiveScene()->GetChild("Player")->SetVisible(false)->SetActive(false);
		}
		std::ifstream replayFile("replay", std::ios::binary);
		if (!replayFile.is_open()) {
			throw std::runtime_error("Failed to open replay file");
		}

		replayFile.seekg(mFilePosition, std::ios::beg);
		mFilePosition = replayFile.tellg();

		ReplayDataHeader header;
		replayFile.read(reinterpret_cast<char *>(&header), sizeof(header));
		if (replayFile.eof()) {
			replayFile.close();
            Game::GetInstance().SetState(Player::mLevelCleared ? GameState::GAME_PAUSED : GameState::GAME_OVER);
            Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(true)->SetVisible(true);
            Game::GetInstance().GetActiveScene()->GetChild("MenuTransition")->SetVisible(true);
            delete GetChild("PlayerDummy");
            if (GetChild("Entities") != nullptr) GetChild("Entities")->SafeDelete();
            Game::GetInstance().GetActiveScene()->GetChild("Player")->SetVisible(true)->SetActive(true);
			return;
		}

		if (header.time > mTime) {
			return;
		}

        GetChild("PlayerDummy")->SetPosition(glm::make_vec3(header.playerData.position));

		Dungeon *dungeon = (Dungeon *)Game::GetInstance().GetActiveScene()->GetChild("Dungeon");
		if (header.roomX != mRoomX || header.roomY != mRoomY) { 
            mRoomX = header.roomX;
            mRoomY = header.roomY;
            dungeon->SetRoomState(header.roomX, header.roomY, DungeonRoom::State::CLEARED);
            ((DungeonRoom *)dungeon->GetChild("DungeonRoom"))->SetRoom(header.roomX, header.roomY);
            GameObject *entities = new GameObject("Entities", dungeon->GetChild("DungeonRoom"));
        }
        if (GetChild("Entities") != nullptr) {
            GetChild("Entities")->SafeDelete();
        }
		GameObject *entities = new GameObject("Entities", this);

		int entityCount;
		replayFile.read(reinterpret_cast<char *>(&entityCount), sizeof(entityCount));
		for (int i = 0; i < entityCount; i++) {
			Entity::SaveData data;
			replayFile.read(reinterpret_cast<char *>(&data), sizeof(data));
            // std::cout << "Entity: " << i << " " << data.type << " " << data.position.x << ", " << data.position.y << std::endl;
			Entity *entity = EntityFactory::CreateEntity(data.type, std::to_string(i), entities, glm::make_vec3(data.position));
            entity->SetActive(false);
            entity->SetTag("XXX" + std::to_string(i));
		}

		mFilePosition = replayFile.tellg();
		replayFile.close();
	}
}
