#pragma once

#include "game_object.hpp"
#include "objects/entities/entity.hpp"

class DungeonRoom : public GameObject {
   public:
	enum class Type {
		NOT_SET,
		START,
		EMPTY,
		MONSTER,
		TREASURE,
		END
	};

	enum class State {
		UNVISITED,
		VISITED,
		CLEARED
	};

	DungeonRoom(GameObject *parent);
	using GameObject::Render;
    virtual void Update(float deltaTime) override;

    void EntitysFromSaveData(std::vector<Entity::SaveData> &entityData);

    void SetRoom(int x, int y);

	void SetType(Type type);
	Type GetType();

    int GetEnemyCount();

   private:
	const int n = 13, m = 13;
	Type mType;
	State mState;
};
