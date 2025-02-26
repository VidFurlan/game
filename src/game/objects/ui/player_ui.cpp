#include "player_ui.hpp"

#include <string>

#include "spritesheet_game_object.hpp"

PlayerUI::PlayerUI(Player *player)
    : GameObject("PlayerUI"), mPlayer(player) {
	SetZIndex(0);

	AddChild(new GameObject("Hearts"));
	UpdateHealth();
}

void PlayerUI::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	if (mDisplayedHealth != mPlayer->mHealth) {
		UpdateHealth();
	}

	GameObject::Update(deltaTime);
}

void PlayerUI::UpdateHealth() {
	mDisplayedHealth = mPlayer->mHealth;
	for (int i = 0; i < mPlayer->mMaxHealth / 2.0; i++) {
		SpriteSheetGameObject *heart = (SpriteSheetGameObject *)GetChild("Hearts")->GetChild("Heart" + std::to_string(i));
		if (heart == nullptr) {
			heart = (SpriteSheetGameObject *)((new SpriteSheetGameObject("Heart" + std::to_string(i), GetChild("Hearts"), "hearts", {20, 13}, {10.0f, 10.0f + i * 10.0f, 0.0f}, {8, 8}))
			                                      ->SetScreenAnchor(ScreenAnchor::TOP_LEFT)
			                                      ->SetPosition({4.0f + i * 8.0f, 4.0f, 0.0f})
			                                      ->SetZIndex(0));
		}
		if (mDisplayedHealth > i * 2 + 1) {
			heart->SetSpriteSheetFrame({3, 0});
		} else if (mDisplayedHealth > i * 2) {
			heart->SetSpriteSheetFrame({4, 0});
		} else {
			heart->SetSpriteSheetFrame({0, 0});
		}
	}
}
