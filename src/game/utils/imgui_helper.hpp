#pragma once

#include "game_object.hpp"
class ImGuiHelper {
   public:
	static void Init();
	static void NewFrame();
	static void Render();
	static void Shutdown();

	static void ImGuiDebugMenu();

   private:
	static bool mShowSceneDebugMenu;
    static GameObject *mSelectedGameObject;
};
