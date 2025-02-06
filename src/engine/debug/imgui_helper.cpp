#include "imgui_helper.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <type_traits>

#include "abstract_image_game_object.hpp"
#include "camera_game_object.hpp"
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
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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

	// ImGuiIO &io = ImGui::GetIO();
	//
	// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
	//	ImGui::UpdatePlatformWindows();
	//	ImGui::RenderPlatformWindowsDefault();
	// }
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

	bool disablePostProcessing = Game::GetInstance().IsPostProcessingDisabled();
	ImGui::Checkbox("Disable post processing", &disablePostProcessing);
	Game::GetInstance().SetPostProcessingDisabled(disablePostProcessing);

	bool debugMode = Game::GetInstance().IsDebugMode();
	ImGui::Checkbox("Debug mode", &debugMode);
	Game::GetInstance().SetDebugMode(debugMode);

	ImGui::Checkbox("Show scene debug", &mShowSceneDebugMenu);

	ImGui::End();

	if (mShowSceneDebugMenu) {
		// General scene debug menu
		SceneGameObject *scene = Game::GetInstance().GetActiveScene();

		ImGui::Begin("Scene Debug Menu");

		ImGui::Text("Scene name: %s", scene->GetName().c_str());
		ImGui::Text("Active Game Objects: %d", (int)(scene->GetChildrenCount()));
        if (scene->GetActiveCamera() == nullptr) {
            ImGui::Text("No active camera set");
        } else {
            ImGui::Text("Active camera: %s", scene->GetActiveCamera()->GetName().c_str());
            ImGui::Text("Camera position: (%.2f, %.2f)", scene->GetActiveCamera()->GetPosition().x, scene->GetActiveCamera()->GetPosition().y);
        }

		ImGui::Separator();

		ImGui::Text("\t\tA | V \tName [AV]");

		// Hierarchical game object debug menu
		auto dfsHierarchy = [](GameObject *gameObject, int level, bool active, bool visible, std::string tagName, auto dfsHierarchy) -> void {
			tagName += gameObject->GetName() + "/";

			if (ImGui::Button((std::string("Debug##Debug") + tagName).c_str())) {
				if (ImGuiHelper::mSelectedGameObject == gameObject) {
					ImGuiHelper::mSelectedGameObject = nullptr;
				} else {
					ImGuiHelper::mSelectedGameObject = gameObject;
				}
			}
			ImGui::SameLine();

			bool isActive = gameObject->GetActive();
			ImGui::Checkbox((std::string("##Active") + tagName).c_str(), &isActive);
			ImGui::SameLine();
			if (isActive != gameObject->GetActive()) gameObject->SetActive(isActive);
			active = active && isActive;

			bool isVisible = gameObject->GetVisible();
			ImGui::Checkbox((std::string("##Visible") + tagName).c_str(), &isVisible);
			ImGui::SameLine();
			if (isVisible != gameObject->GetVisible()) gameObject->SetVisible(isVisible);
			visible = visible && isVisible;

			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			if (gameObject->GetChildren()->empty()) {
				flags |= ImGuiTreeNodeFlags_Leaf;
			}
			if (ImGuiHelper::mSelectedGameObject == gameObject) {
				flags |= ImGuiTreeNodeFlags_Selected;
			}

			bool showChildren = ImGui::TreeNodeEx((std::string("##") + tagName).c_str(), flags, "%s [%s%s]", gameObject->GetName().c_str(), active ? "A" : "-", visible ? "V" : "-");

			if (showChildren) {
				for (auto [name, child] : *gameObject->GetChildren()) {
					dfsHierarchy(child, level + 1, active, visible, tagName, dfsHierarchy);
				}
				ImGui::TreePop();
			}
		};

		for (auto [name, gameObject] : *scene->GetChildren()) {
			dfsHierarchy(gameObject, 0, true, true, "", dfsHierarchy);
		}

		// Selected game object debug menu
		if (ImGuiHelper::mSelectedGameObject != nullptr) {
			ImGui::Separator();

			GameObject *gameObject = ImGuiHelper::mSelectedGameObject;

			ImGui::Text("Game object: ");
			ImGui::SameLine();
			SnapToRight(gameObject->GetName());
			ImGui::Text("Parent: ");
			ImGui::SameLine();
			if (gameObject->GetParent() != nullptr) {
				SnapToRight(gameObject->GetParent()->GetName());
			} else {
				SnapToRight("None");
			}
			ImGui::Text("Type: ");
			ImGui::SameLine();
			SnapToRight(typeid(*gameObject).name());

			ImGui::Separator();

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
			ImGui::InputFloat("X##Pos", &pos.x, 1.0f, 1.0f, "%.4f", ImGuiInputTextFlags_CharsDecimal);
			ImGui::InputFloat("Y##Pos", &pos.y, 1.0f, 1.0f, "%.4f", ImGuiInputTextFlags_CharsDecimal);
			gameObject->SetPosition(pos);

			ImGui::Text("Rotation:");
			float rot = gameObject->GetRotation();
			ImGui::InputFloat("##Rot", &rot, 1.0f, 1.0f, "%.2f", ImGuiInputTextFlags_CharsDecimal);
			gameObject->SetRotation(rot);

			if (dynamic_cast<AbstractImageGameObject *>(gameObject)) {
				AbstractImageGameObject *imageGameObject = dynamic_cast<AbstractImageGameObject *>(gameObject);

				glm::vec2 size = imageGameObject->GetScale();
				ImGui::Text("Size:");
				ImGui::InputFloat("Width##Size", &size.x, 1.0f, 1.0f, "%.4f", ImGuiInputTextFlags_CharsDecimal);
				ImGui::InputFloat("Height##Size", &size.y, 1.0f, 1.0f, "%.4f", ImGuiInputTextFlags_CharsDecimal);
				imageGameObject->SetScale(size);

				glm::vec3 color = imageGameObject->GetColor();
				ImGui::ColorEdit3("Color", &color.x);
				imageGameObject->SetColor(color);
			}

			if (dynamic_cast<CameraGameObject *>(gameObject)) {
				CameraGameObject *cameraGameObject = dynamic_cast<CameraGameObject *>(gameObject);

				float zoom = cameraGameObject->GetZoom();
				ImGui::Text("Zoom:");
				ImGui::InputFloat("##Zoom", &zoom, 0.1f, 1.0f, "%.4f", ImGuiInputTextFlags_CharsDecimal);
				cameraGameObject->SetZoom(zoom);

				if (ImGui::Button("Use Camera")) {
					cameraGameObject->Use();
				}
			}
		}

		ImGui::End();
	}
}

void ImGuiHelper::SnapToRight(std::string text) {
	auto posX = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(text.c_str()).x - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
	if (posX > ImGui::GetCursorPosX())
		ImGui::SetCursorPosX(posX);
	ImGui::Text("%s", text.c_str());
}
