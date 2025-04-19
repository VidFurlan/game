#include "chest.hpp"

#include "game.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/entity.hpp"
#include "polygon2d.hpp"
#include "spritesheet_game_object.hpp"

Chest::Chest(std::string name, GameObject *parent, glm::vec3 position) : Entity(name, parent, EntityType::TREASURE_CHEST, new Polygon2D({{-2.0f, -2.0f}, {-2.0f, 2.0f}, {2.0f, 2.0f}, {2.0f, -2.0f}}), position, {1.0f, 1.0f}) {
    mMaxHealth = 2;
    mHealth = mMaxHealth;
    mImmunityTime = 0.3f;

    SetTag("Enemy");
    SetZIndex(900);
    (new SpriteSheetGameObject("Sprite", this, "enemy", {32, 32}, {0.0f, -2.2f, 0.0f}, {8, 8}))
        ->SetSpriteSheetFrame({26, 19});

    DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
    room->SetEnemyCount(room->GetEnemyCount() + 1);
}

Chest::~Chest() {
    DungeonRoom *room = ((DungeonRoom *)GetParent()->GetParent());
    room->SetEnemyCount(room->GetEnemyCount() - 1);
}
