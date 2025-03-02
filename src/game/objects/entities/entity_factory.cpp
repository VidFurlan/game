#include "entity_factory.hpp"
#include <functional>
#include <iostream>
#include <string>
#include "objects/entities/chest.hpp"
#include "objects/entities/enemy.hpp"

std::unordered_map<EntityType, std::function<Entity *(std::string, GameObject *, glm::vec3)>> EntityFactory::mEntityConstructors;

void EntityFactory::Init() {
    mEntityConstructors[TREASURE_CHEST] = [](std::string name, GameObject *parent, glm::vec3 position) {
        return new Chest(name, parent, position);
    };

    mEntityConstructors[GRAY_BLOB] = [](std::string name, GameObject *parent, glm::vec3 position) {
        return new Enemy(name, parent, position);
    };
}

Entity *EntityFactory::CreateEntity(EntityType type, std::string name, GameObject *parent, glm::vec3 position) {
    std::function<Entity *(std::string, GameObject *, glm::vec3)> constructor = mEntityConstructors[type];
    return constructor("Entity" + name, parent, position);
}
