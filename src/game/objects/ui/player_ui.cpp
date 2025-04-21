#include "player_ui.hpp"

#include <string>

#include "drawable_game_object.hpp"
#include "spritesheet_game_object.hpp"
#include "text_game_object.hpp"

PlayerUI::PlayerUI(Player *player)
    : GameObject("PlayerUI"), mPlayer(player) {
	SetZIndex(0);

	AddChild(new GameObject("Hearts"));
	UpdateHealth();

	(new SpriteSheetGameObject("Cat", this, "cat", {8, 8}, {5.0f, 10.0f, 0.0f}, {10.0f, 10.0f}))
	    ->SetSpriteSheetFrame({0, 6})
	    ->SetScreenAnchor(ScreenAnchor::TOP_LEFT)
	    ->SetZIndex(1100);
    
	(new TextGameObject("CatsCnt", this, std::to_string(Player::mKillCount), TextGameObject::TextProperties("default", 200.0f), {11.0f, 13.0f, 0.0f}, {20.0f, 20.0f}))
	    ->SetScreenAnchor(ScreenAnchor::TOP_LEFT)
	    ->SetZIndex(0);

	(new TextGameObject("Score", this, std::to_string(Player::mKillCount), TextGameObject::TextProperties("default", 200.0f), {4.0f, 20.0f, 0.0f}, {20.0f, 20.0f}))
	    ->SetScreenAnchor(ScreenAnchor::TOP_LEFT)
	    ->SetZIndex(0);
}

void PlayerUI::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	((TextGameObject *)GetChild("CatsCnt"))->SetText("x" + std::to_string(Player::mCatCount));
	((TextGameObject *)GetChild("Score"))->SetText(std::to_string(Player::mKillCount + Player::mCatCount * 5));

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
