#include "imgui_helper.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <map>
#include <string>

#include "game.hpp"
#include "scene_game_object.hpp"

bool ImGuiHelper::mShowSceneDebugMenu = false;
GameObject *ImGuiHelper::mSelectedGameObject = nullptr;

void ImGuiHelper::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplGlfw_InitForOpenGL(Game::GetInstance().GetWindow()->GetWindow(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
}

void ImGuiHelper::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiHelper::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHelper::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiHelper::ImGuiDebugMenu() {
	ImGui::Begin("Game Debug Info");

	ImGuiIO &io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Text("Active scene: %s", Game::GetInstance().GetActiveScene()->GetName().c_str());

	ImGui::Checkbox("Show scene debug", &mShowSceneDebugMenu);

	ImGui::End();

	if (mShowSceneDebugMenu) {
        // General scene debug menu
		SceneGameObject *scene = Game::GetInstance().GetActiveScene();

		ImGui::Begin("Scene Debug Menu");

		ImGui::Text("Scene name: %s", scene->GetName().c_str());
		ImGui::Text("Game objects count: %d", (int)(scene->GetChildrenCount()));

		ImGui::Separator();

        // Hierarchical game object debug menu
		auto dfsHierarchy = [](GameObject *gameObject, int level, bool active, std::string tagName, auto dfsHierarchy) -> void {
            tagName += gameObject->GetName() + "/";

			if (ImGui::Button((std::string("?##Debug") + tagName).c_str())) {
                ImGuiHelper::mSelectedGameObject = gameObject;
            }
			ImGui::SameLine();

			bool isActive = gameObject->GetActive();
			ImGui::Checkbox((std::string("##Active") + tagName).c_str(), &isActive);
            ImGui::SameLine();
			if (isActive != gameObject->GetActive()) gameObject->SetActive(isActive);
            active = active && isActive;

			for (int i = 0; i < level; i++) {
				ImGui::Text("  ");
				ImGui::SameLine();
			}

			ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, (active ? 1.0f : 0.7f)), "%s", gameObject->GetName().c_str());
			for (auto [name, child] : *gameObject->GetChildren()) {
				dfsHierarchy(child, level + 1, active, tagName, dfsHierarchy);
			}
		};
		dfsHierarchy(scene, 0, true, "", dfsHierarchy);

        // Selected game object debug menu
		if (ImGuiHelper::mSelectedGameObject != nullptr) {
			ImGui::Separator();
			GameObject *gameObject = ImGuiHelper::mSelectedGameObject;

			ImGui::Text("Game object: ");
			ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "%s", gameObject->GetName().c_str());

            bool active = gameObject->GetActive();
            ImGui::Checkbox("Active", &active);
            gameObject->SetActive(active);

            bool visible = gameObject->GetVisible();
            ImGui::Checkbox("Visible", &visible);
            gameObject->SetVisible(visible);

            ImGui::Text("Z Index:");
            int layer = gameObject->GetZIndex();
            ImGui::InputInt("##Layer", &layer);
            gameObject->SetZIndex(layer);

			ImGui::Text("Position:");
            glm::vec2 pos = gameObject->GetPosition();
            ImGui::InputFloat("X##Pos", &pos.x);
            ImGui::InputFloat("Y##Pos", &pos.y);
            gameObject->SetPosition(pos);

            ImGui::Text("Rotation:");
            float rot = gameObject->GetRotation();
            ImGui::InputFloat("##Rot", &rot);
            gameObject->SetRotation(rot);

            ImGui::Text("Scale:");
            glm::vec2 scale = gameObject->GetScale();
            ImGui::InputFloat("X##Scale", &scale.x);
            ImGui::InputFloat("Y##Scale", &scale.y);
            gameObject->SetScale(scale);
		}

		ImGui::End();
	}
}
