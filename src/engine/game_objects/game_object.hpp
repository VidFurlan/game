#pragma once

#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

class GameObject {
   public:
	static constexpr float GAME_SCALE_FACTOR = 10.0f;

	GameObject(std::string name, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	GameObject(std::string name, GameObject *parent, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	virtual ~GameObject();

	virtual void Update(float deltaTime = 0.0f);
    virtual void LateUpdate(float deltaTime = 0.0f);
	virtual void Render();

	std::string GetName() const;

	GameObject *SetActive(bool active);
	bool GetActive() const;

	GameObject *SetVisible(bool visible);
	bool GetVisible() const;

	GameObject *SetPosition(glm::vec2 pos);
	GameObject *SetPosition(glm::vec3 pos);
	GameObject *SetRotation(float rot);
	GameObject *SetRotation(glm::vec3 rot);

	glm::vec3 GetPosition() const;
	glm::vec3 GetGlobalPosition() const;
	float GetRotation() const;
	float GetGlobalRotation() const;

	GameObject *SetZIndex(int zIndex);
	int GetZIndex() const;

	GameObject *GetParent() const;
	GameObject *GetChild(std::string name) const;
	std::unordered_map<std::string, GameObject *> *GetChildren() const;
	unsigned int GetChildrenCount() const;

	GameObject *AddChild(GameObject *child);
	GameObject *AddChildToLocalPos(GameObject *child);
	GameObject *RemoveChild(std::string name);
	void DeleteChild(std::string name);

	GameObject *operator+=(glm::vec2 pos);
	GameObject *operator-=(glm::vec2 pos);
	GameObject *operator*=(glm::vec2 pos);
	GameObject *operator/=(glm::vec2 pos);

	GameObject *operator+=(glm::vec3 pos);
	GameObject *operator-=(glm::vec3 pos);
	GameObject *operator*=(glm::vec3 pos);
	GameObject *operator/=(glm::vec3 pos);

   protected:
	const std::string mName;

	bool mActive;
	bool mVisible;

	glm::vec3 mPos;
	glm::vec2 mScale;
	int mZIndex = 1000;

	GameObject *pParent = nullptr;
	std::unordered_map<std::string, GameObject *> children;
	std::map<int, std::set<GameObject *>, std::greater<int>> mChildrenByZIndex;
};
