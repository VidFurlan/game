#pragma once

#include <string>
#include <unordered_map>

#include "objects/entities/entity.hpp"

class EntityFactory {
   public:
	static void Init();
	static Entity *CreateEntity(EntityType type, std::string name, GameObject *parent, glm::vec3 position);

   private:
	static std::unordered_map<EntityType, std::function<Entity *(std::string, GameObject *, glm::vec3)>> mEntityConstructors;
};
