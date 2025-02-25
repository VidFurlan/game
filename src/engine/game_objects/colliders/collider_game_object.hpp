#pragma once

#include <functional>
#include <utility>
#include "game_objects/game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "shape2d.hpp"

class ColliderGameObject : public GameObject {
   public:
	enum class CollisionType {
		OVERLAP,
		TOUCH,
		NONE
	};

   public:
	ColliderGameObject(std::string name, Shape2D *shape, bool fixed, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	ColliderGameObject(std::string name, GameObject *parent, Shape2D *shape, bool fixed, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	~ColliderGameObject();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(ColliderGameObject *other, CollisionType type = CollisionType::OVERLAP);
    
    void ResolveCollision(float overlap, glm::vec2 minAxis);

	CollisionType CheckCollision(ColliderGameObject *other) const;
    CollisionType CheckCollisionAndResolve(ColliderGameObject *other);
	CollisionType CheckPointCollision(glm::vec2 point) const;
	static std::pair<ColliderGameObject::CollisionType, std::pair<float, glm::vec2>> CheckShapeOverlap(Shape2D *shape1, Shape2D *shape2, glm::vec3 pos1, glm::vec3 pos2);

    bool IsFixed();

    ColliderGameObject *SetOnCollision(std::function<void(ColliderGameObject *, CollisionType)> callback);

   private:
    std::function<void(ColliderGameObject *, CollisionType)> mOnCollision;

    bool mFixed;
	Shape2D *mShape;
	glm::vec3 mGlobalPosition;
};
