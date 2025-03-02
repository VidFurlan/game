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
	using GameObject::Update;

    void SetRoom(int x, int y);

	void SetType(Type type);
	Type GetType();
    void SetState(State state);
    State GetState();

    void SetEnemyCount(int count);
    int GetEnemyCount();

   private:
	const int n = 13, m = 13;
    int mEnemyCount = 0;
	Type mType;
	State mState;
    std::vector<Entity *> mEntities;
};
