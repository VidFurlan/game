#pragma once

#include "glm/fwd.hpp"
#include "resource_manager.hpp"
#include "singleton.hpp"
#include "texture.hpp"

class DebugRenderer : public Singleton {
   public:
	static DebugRenderer& GetInstance() {
		static DebugRenderer instance;
		return instance;
	}
	void drawLineGlobalPos(glm::vec2 start, glm::vec2 end, const glm::vec3& color);
	void drawLineAbsolutPos(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color);

   private:
	DebugRenderer()
		: __debugPixelTexture(ResourceManager::GetInstance().LoadTexture("assets/engine/textures/pixel.png", false, "pixel")) {}

	Texture __debugPixelTexture;
};
