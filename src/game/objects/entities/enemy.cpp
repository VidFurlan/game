#include "enemy.hpp"

#include "game.hpp"
#include "game_object.hpp"
#include "glm/geometric.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "polygon2d.hpp"
#include "spritesheet_game_object.hpp"

Enemy::Enemy(std::string name, GameObject *parent, glm::vec3 position)
    : Entity(name, parent, new Polygon2D({{-2.0f, -2.0f}, {-2.0f, 2.0f}, {2.0f, 2.0f}, {2.0f, -2.0f}}), true, position, {1.0f, 1.0f}) {
    mMaxHealth = 3;
    mHealth = mMaxHealth;
	SetTag("Enemy");
	SetZIndex(900);
	(new SpriteSheetGameObject("EnemySprite", this, "enemy", {32, 32}, {0.0f, -2.2f, 0.0f}, {8, 8}))
	    ->SetSpriteSheetFrame({1, 23});
	moveSpeed *= (rand() % 100) / 200.0f - 0.5f + 1.0f;

    DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
    room->SetEnemyCount(room->GetEnemyCount() + 1);
}

Enemy::~Enemy() {
    DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
    room->SetEnemyCount(room->GetEnemyCount() - 1);
}

void Enemy::Update(float deltaTime) {
	Entity::Update(deltaTime);

	if (mActive == false) {
		return;
	}

	mAnimationTimeElapsed += deltaTime;
	if (mAnimationTimeElapsed > 0.1f) {
		mAnimationTimeElapsed = 0.0f;
		mAnimationFrame = (mAnimationFrame + 1) % 4;
		((SpriteSheetGameObject *)GetChild("EnemySprite"))->SetSpriteSheetFrame({1, 23 + mAnimationFrame});
	}

	GameObject *player = Game::GetInstance().GetActiveScene()->GetChild("Player");
	glm::vec3 move = player->GetGlobalPosition() - GetGlobalPosition() + glm::vec3((rand() % 100) / 20.0f - 2.5f, (rand() % 100) / 20.0f - 2.5f, 0.0f);
	if (std::abs(move.x) > 3.0f) ((SpriteSheetGameObject *)GetChild("EnemySprite"))->SetScaleX(move.x > 0 ? 8.0f : -8.0f);
	if ((move.x != 0 || move.y != 0) && glm::length(move) > 10.0f) {
		move = glm::normalize(move);
		mPos += move * moveSpeed * deltaTime;
	}
}
