#pragma once

#include <map>
#include <string>

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class GameObject {
   public:
	GameObject(std::string name, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	GameObject(std::string name, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	GameObject(std::string name, GameObject *parent, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	GameObject(std::string name, GameObject *parent, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	~GameObject();

	virtual void Update(float deltaTime = 0.0f);
	virtual void Render();

	std::string GetName() const;

	void SetActive(bool active);
	bool GetActive() const;

	void SetVisible(bool visible);
	bool GetVisible() const;

	void SetPosition(glm::vec2 pos);
	void SetPosition(glm::vec3 pos);
	void SetRotation(float rot);
	void SetRotation(glm::vec3 rot);

	glm::vec3 GetPosition() const;
	glm::vec3 GetGlobalPosition() const;
	float GetRotation() const;
	float GetGlobalRotation() const;

	void SetScale(glm::vec2 scale);
	void SetScaleX(float scaleX);
	void SetScaleY(float scaleY);

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

	GameObject *pParent = nullptr;
	std::map<std::string, GameObject *> children;
};
