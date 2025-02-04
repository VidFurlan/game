#pragma once

#include "game_objects/game_object.hpp"
#include "shape2d.hpp"

class ColliderGameObject : public GameObject {
   public:
	enum class CollisionType {
		OVERLAP,
		TOUCH,
		NONE
	};

   public:
	ColliderGameObject(std::string name, Shape2D *shape, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	ColliderGameObject(std::string name, GameObject *parent, Shape2D *shape, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	~ColliderGameObject();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(ColliderGameObject *other, CollisionType type = CollisionType::OVERLAP);

	CollisionType CheckCollision(ColliderGameObject *other) const;
    CollisionType CheckPointCollision(glm::vec2 point) const;
	static CollisionType CheckShapeOverlap(Shape2D *shape1, Shape2D *shape2, glm::vec3 pos1, glm::vec3 pos2);

   private:
	Shape2D *mShape;
	glm::vec3 mGlobalPosition;
};
