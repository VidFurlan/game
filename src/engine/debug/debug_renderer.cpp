#include "debug_renderer.hpp"
#include <iostream>
#include "game.hpp"
#include "game_object.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"

void DebugRenderer::drawLineGlobalPos(glm::vec2 p1, glm::vec2 p2, const glm::vec3& color) {
    p1 -= glm::make_vec2(Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetPosition() * GameObject::GAME_SCALE_FACTOR);
    p2 -= glm::make_vec2(Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetPosition() * GameObject::GAME_SCALE_FACTOR);

    p1 *= Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetZoom();
    p2 *= Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetZoom();

    p1 += glm::vec2(Game::GetInstance().GetWindow()->GetWidth() / 2.0f, Game::GetInstance().GetWindow()->GetHeight() / 2.0f);
    p2 += glm::vec2(Game::GetInstance().GetWindow()->GetWidth() / 2.0f, Game::GetInstance().GetWindow()->GetHeight() / 2.0f);

    drawLineAbsolutPos(p1, p2, color);
}

void DebugRenderer::drawLineAbsolutPos(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color) {
    glm::vec2 pos = (p1 + p2) / 2.0f;
    glm::vec2 scale = glm::vec2(glm::distance(p1, p2), 2.0f);
    float angle = glm::degrees(glm::atan(p2.y - p1.y, p2.x - p1.x));
    pos -= scale / 2.0f;
    Game::GetInstance().GetSpriteRenderer()->DrawSprite(__debugPixelTexture, pos,
                                                        scale, angle, color);
}
