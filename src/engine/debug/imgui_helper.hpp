#pragma once

#include <string>

#include "game_object.hpp"
class ImGuiHelper {
   public:
	static void Init();
	static void NewFrame();
	static void Render();
	static void Shutdown();

	static void ImGuiDebugMenu();

	static void SnapToRight(std::string text);

   private:
	static bool mShowSceneDebugMenu;
	static GameObject *mSelectedGameObject;
};
