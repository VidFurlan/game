#pragma once

#include "game_object.hpp"
#include "objects/player.hpp"

class PlayerUI : public GameObject {
   public:
	PlayerUI(Player *player);
    void Update(float deltaTime) override;
    void UpdateHealth();

   private:
	Player *mPlayer;
    float mDisplayedHealth;
};
