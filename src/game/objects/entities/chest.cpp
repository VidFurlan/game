#include "chest.hpp"

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float4.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/entity.hpp"
#include "objects/menu_transition.hpp"
#include "objects/player.hpp"
#include "polygon2d.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

Chest::Chest(std::string name, GameObject *parent, glm::vec3 position) : Entity(name, parent, EntityType::TREASURE_CHEST, new Polygon2D({{-3.0f, -3.0f}, {-3.0f, 3.0f}, {3.0f, 3.0f}, {3.0f, -3.0f}}), position, {1.0f, 1.0f}) {
	mMaxHealth = 2;
	mHealth = mMaxHealth;
	mImmunityTime = 0.3f;

	SetTag("Enemy");
	SetZIndex(900);
	(new SpriteGameObject("Sprite", this, "ice", {0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}))->SetColor({1.0f, 1.0f, 1.0f, 0.5f});
	(new SpriteSheetGameObject("Cat", this, "cat", {8, 8}, {0.0f, -2.0f, 0.0f}, {10.0f, 10.0f}))
	    ->SetSpriteSheetFrame({0, 6})
	    ->SetZIndex(1100);

	//(new SpriteSheetGameObject("Sprite", this, "enemy", {32, 32}, {0.0f, -2.2f, 0.0f}, {8, 8}))
	//    ->SetSpriteSheetFrame({26, 19});

	DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
}

Chest::~Chest() {
	DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
}

void Chest::Death() {
	Player::mCatCount++;
	Game::GetInstance().SetState(GameState::GAME_PAUSED);
	((MenuTransition *)Game::GetInstance().GetActiveScene()->GetChild("MenuTransition"))->Transition([]() {
		Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(true)->SetVisible(true);
		Player::mLevelCleared = true;
	});
}

void Chest::Update(float deltaTime) {
	Entity::Update(deltaTime);
	glm::vec4 color = ((AbstractImageGameObject *)GetChild("Sprite"))->GetColor();
	color.a = 0.5;
	((AbstractImageGameObject *)GetChild("Sprite"))->SetColor(color);
}
