#include "dungeon_room.hpp"

#include <functional>
#include <iostream>
#include <string>

#include "game.hpp"
#include "game_object.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/entities/entity.hpp"
#include "objects/entities/entity_factory.hpp"
#include "objects/player.hpp"
#include "objects/room_transition.hpp"
#include "objects/saver.hpp"
#include "rect_collider_game_object.hpp"
#include "scene_game_object.hpp"
#include "spritesheet_game_object.hpp"

DungeonRoom::DungeonRoom(GameObject *parent) : GameObject("DungeonRoom", parent) {
	GameObject *colliders = AddChild(new GameObject("Colliders", {0.0f, 0.0f, 0.0f}));
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("DoorUp", false, {0.0f, 44.0f, 0.0f}, {10.0f, 2.0f})))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (GetEnemyCount() > 0) return;
		    if (type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "Player") {
			    ((RoomTransition *)Game::GetInstance().GetActiveScene()->GetChild("Transition"))->Transition([this]() {
				    Dungeon *dungeon = (Dungeon *)this->GetParent();
				    dungeon->EnterRoom(dungeon->GetRoomPosition().x + 1, dungeon->GetRoomPosition().y);
				    GameObject *player = Game::GetInstance().GetActiveScene()->GetChild("Player");
				    player->SetPosition({0, -(m - 3) * 4.0f, 0.0f});
			    });
		    }
	    })
	    ->SetActive(false);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("DoorDown", false, {0.0f, -44.0f, 0.0f}, {10.0f, 2.0f})))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (GetEnemyCount() > 0) return;
		    if (type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "Player") {
			    ((RoomTransition *)Game::GetInstance().GetActiveScene()->GetChild("Transition"))->Transition([this]() {
				    Dungeon *dungeon = (Dungeon *)this->GetParent();
				    dungeon->EnterRoom(dungeon->GetRoomPosition().x - 1, dungeon->GetRoomPosition().y);
				    GameObject *player = Game::GetInstance().GetActiveScene()->GetChild("Player");
				    player->SetPosition({0, (m - 3) * 4.0f, 0.0f});
			    });
		    }
	    })
	    ->SetActive(false);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("DoorLeft", false, {-44.0f, 0.0f, 0.0f}, {2.0f, 10.0f})))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (GetEnemyCount() > 0) return;
		    if (type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "Player") {
			    ((RoomTransition *)Game::GetInstance().GetActiveScene()->GetChild("Transition"))->Transition([this]() {
				    Dungeon *dungeon = (Dungeon *)this->GetParent();
				    dungeon->EnterRoom(dungeon->GetRoomPosition().x, dungeon->GetRoomPosition().y - 1);
				    GameObject *player = Game::GetInstance().GetActiveScene()->GetChild("Player");
				    player->SetPosition({(n - 3) * 4.0f, 0, 0.0f});
			    });
		    }
	    })
	    ->SetActive(false);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("DoorRight", false, {44.0f, 0.0f, 0.0f}, {2.0f, 10.0f})))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (GetEnemyCount() > 0) return;
		    if (type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "Player") {
			    ((RoomTransition *)Game::GetInstance().GetActiveScene()->GetChild("Transition"))->Transition([this]() {
				    Dungeon *dungeon = (Dungeon *)this->GetParent();
				    dungeon->EnterRoom(dungeon->GetRoomPosition().x, dungeon->GetRoomPosition().y + 1);
				    GameObject *player = Game::GetInstance().GetActiveScene()->GetChild("Player");
				    player->SetPosition({-(n - 3) * 4.0f, 0, 0.0f});
			    });
		    }
	    })
	    ->SetActive(false);

	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("WallUp", true, {0.0f, -100.0f, 0.0f}, {300.0f, 112.0f})))->SetFixed(true);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("WallDown", true, {0.0f, 100.0f, 0.0f}, {300.0f, 112.0f})))->SetFixed(true);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("WallLeft", true, {-100.0f, 0.0f, 0.0f}, {112.0f, 300.0f})))->SetFixed(true);
	((ColliderGameObject *)colliders->AddChild(new RectColliderGameObject("WallRight", true, {100.0f, 0.0f, 0.0f}, {112.0f, 300.0f})))->SetFixed(true);

	GameObject *tiles = AddChild(new GameObject("Tiles"));
	tiles->SetPosition({-n * 4 + 4, -m * 4 + 4, 0.0f});

	AddChild(new GameObject("Entities"))->SetZIndex(900);
	EntityFactory::Init();
}

void DungeonRoom::SetRoom(int x, int y) {
	Dungeon *dungeon = (Dungeon *)this->GetParent();
	mType = dungeon->GetRoomData(x, y).type;

	GameObject *tiles = GetChild("Tiles");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			SpriteSheetGameObject *tile = (SpriteSheetGameObject *)tiles->GetChild("Tile" + std::to_string(i) + "_" + std::to_string(j));
			if (tile == nullptr) {
				tile = (new SpriteSheetGameObject("Tile" + std::to_string(i) + "_" + std::to_string(j), tiles, "tileset", {10, 10}, {i * 8, j * 8, 0}, {8, 8}))
				           ->SetSpriteSheetFrame(6 + i % 4 + (10 * (j % 3)));
			} else {
				tile->SetScale({8.0f, 8.0f});
			}

			if (i == n - 1 && j == m - 1)
				tile->SetSpriteSheetFrame(4, 5);
			else if (i == 0 && j == m - 1)
				tile->SetSpriteSheetFrame(4, 0);
			else if (i == n - 1 && j == 0)
				tile->SetSpriteSheetFrame(0, 5);
			else if (i == 0 && j == 0)
				tile->SetSpriteSheetFrame(0, 0);
			else if (j == 0)
				tile->SetSpriteSheetFrame(0, 1 + rand() % 4);
			else if (j == m - 1)
				tile->SetSpriteSheetFrame(4, 1 + rand() % 4);
			else if (i == 0)
				tile->SetSpriteSheetFrame(rand() % 4, 0);
			else if (i == n - 1)
				tile->SetSpriteSheetFrame(rand() % 4, 5);
		}
	}

	GetChild("Colliders")->GetChild("DoorUp")->SetActive(false);
	GetChild("Colliders")->GetChild("DoorDown")->SetActive(false);
	GetChild("Colliders")->GetChild("DoorRight")->SetActive(false);
	GetChild("Colliders")->GetChild("DoorLeft")->SetActive(false);

	float roomX = x;
	float roomY = y;
	for (int i = 0; i < 4; i++) {
		if (dungeon->GetRoomData(roomX + Dungeon::directions[i][0], roomY + Dungeon::directions[i][1]).type != Type::NOT_SET) {
			if (i == 0) {
				GetChild("Colliders")->GetChild("DoorUp")->SetActive(true);
				((SpriteSheetGameObject *)tiles->GetChild("Tile" + std::to_string(n / 2) + "_" + std::to_string(m - 1)))->SetSpriteSheetFrame(3, 6)->SetScaleX(-8);
			}
			if (i == 1) {
				GetChild("Colliders")->GetChild("DoorDown")->SetActive(true);
				((SpriteSheetGameObject *)tiles->GetChild("Tile" + std::to_string(n / 2) + "_" + "0"))->SetSpriteSheetFrame(3, 7)->SetScaleX(-8);
			}
			if (i == 2) {
				GetChild("Colliders")->GetChild("DoorRight")->SetActive(true);
				((SpriteSheetGameObject *)tiles->GetChild("Tile" + std::to_string(n - 1) + "_" + std::to_string(m / 2)))->SetSpriteSheetFrame(4, 7);
			}
			if (i == 3) {
				GetChild("Colliders")->GetChild("DoorLeft")->SetActive(true);
				((SpriteSheetGameObject *)tiles->GetChild("Tile" + std::to_string(0) + "_" + std::to_string(m / 2)))->SetSpriteSheetFrame(5, 8);
			}
		}
	}

	delete GetChild("Entities");
	GameObject *entities = AddChild(new GameObject("Entities"))->SetZIndex(900);

	if (Dungeon::mRoomConfigs.find(mType) != Dungeon::mRoomConfigs.end() && dungeon->GetRoomData(roomX, roomY).state != DungeonRoom::State::CLEARED) {
		int idx = 0;
		for (auto &entityData : Dungeon::mRoomConfigs.at(mType)[dungeon->GetRoomData(roomX, roomY).roomContent]) {
			EntityFactory::CreateEntity(entityData.type, std::to_string(idx), entities, glm::make_vec3(entityData.position));
			idx++;
		}
	}
}

void DungeonRoom::EntitysFromSaveData(std::vector<Entity::SaveData> &entityData) {
	delete GetChild("Entities");
	GameObject *entities = AddChild(new GameObject("Entities"))->SetZIndex(900);
	int idx = 0;
	for (auto &data : entityData) {
		EntityFactory::CreateEntity(data.type, std::to_string(idx), entities, glm::make_vec3(data.position))->SetPosition(data.position);
		idx++;
	}

    Player *player = (Player *)Game::GetInstance().GetActiveScene()->GetChild("Player");
    player->SetPosition(Saver::mPlayerSaveData.position);
    player->SetHealth(Saver::mPlayerSaveData.health);
}

void DungeonRoom::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	if (GetEnemyCount() == 0) {
		Dungeon *dungeon = (Dungeon *)GetParent();
		dungeon->SetRoomState(dungeon->GetRoomPosition().x, dungeon->GetRoomPosition().y, DungeonRoom::State::CLEARED);
	}
}

void DungeonRoom::SetType(Type type) {
	mType = type;
}

DungeonRoom::Type DungeonRoom::GetType() {
	return mType;
}

int DungeonRoom::GetEnemyCount() {
	return GetChild("Entities")->GetChildren()->size();
}
