#pragma once

#include "game.hpp"
#include "game_object.hpp"
#include "game_scene.hpp"
#include "objects/entities/entity.hpp"

class ReplayManager : public GameObject {
   public:
	ReplayManager(std::string name, GameObject *parent);

	virtual void Update(float deltaTime) override;
    virtual void LateUpdate(float deltaTime) override;
    void Init();

	struct ReplayDataHeader {
        float time;
		int roomX, roomY;
		Entity::SaveData playerData;
		int entityCount;
	};

    static GameState mOldState;
    bool mReplayStarted = false;

   private:
    float mTime;
    float mWaitedTime;
    int mFilePosition;
    int mRoomX, mRoomY;
};
