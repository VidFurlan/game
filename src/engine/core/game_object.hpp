#pragma once

#include <map>
#include <set>
#include <string>

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

class GameObject {
   public:
	GameObject(std::string name, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	GameObject(std::string name, GameObject *parent, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	~GameObject();

	virtual void Update(float deltaTime = 0.0f);
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

	GameObject *SetScale(glm::vec2 scale);
	GameObject *SetScaleX(float scaleX);
	GameObject *SetScaleY(float scaleY);

	glm::vec2 GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;

	GameObject *GetParent() const;
	GameObject *GetChild(std::string name) const;
	std::map<std::string, GameObject *> *GetChildren() const;
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
	std::map<std::string, GameObject *> children;

	static bool nameCmp(GameObject *a, GameObject *b) {
		return a->GetName() < b->GetName();
	}
	std::map<int, std::set<GameObject *, bool (*)(GameObject *, GameObject *)>> mChildrenByZIndex{
		{1000, std::set<GameObject *, bool (*)(GameObject *, GameObject *)>(nameCmp)}};
};
