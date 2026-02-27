#include "Player.hpp"
#include <algorithm> // 給 std::remove_if 使用

Player::Player() : speed(300.0f) {
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(25.f, 25.f);
    shape.setPosition(400.f, 300.f);
}

void Player::update(float dt) {
    // 1. 處理移動
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;

    shape.move(movement * dt);

    // 2. 處理射擊 (按住滑鼠左鍵)
    // 目前先簡單設定方向為 (1.f, 0.f) 代表固定往右射擊
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        projectiles.push_back(Projectile(shape.getPosition(), sf::Vector2f(1.f, 0.f)));
    }

    // 3. 更新所有子彈位置
    for (auto& p : projectiles) {
        p.update(dt);
    }

    // 4. 清理過期子彈
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return p.isExpired(); }), projectiles.end());
}

void Player::draw(sf::RenderWindow& window) {
    // 先畫玩家
    window.draw(shape);
    // 再把每一顆子彈畫出來
    for (auto& p : projectiles) {
        p.draw(window);
    }
}
