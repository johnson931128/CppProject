#include "Player.hpp"
#include <algorithm>
#include <cmath> // 給 std::sqrt 使用

// 初始化時設定 cooldown 為 0
Player::Player() : speed(300.0f), shootCooldown(0.f) { 
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(25.f, 25.f);
    shape.setPosition(400.f, 300.f);
}

// 修改函數標記，接收 window
void Player::update(float dt, const sf::RenderWindow& window) {
    // 1. 移動邏輯 (與原本相同)
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
    shape.move(movement * dt);

    // 2. 更新冷卻時間
    if (shootCooldown > 0.f) {
        shootCooldown -= dt;
    }

    // 3. 處理射擊 (加上冷卻時間判斷)
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootCooldown <= 0.f) {
        // a. 取得滑鼠在視窗上的像素座標
        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
        
        // b. 將像素座標轉換為遊戲世界座標 (超級重要！)
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow);

        // c. 計算方向向量: 目標位置 - 玩家位置
        sf::Vector2f playerPos = shape.getPosition();
        sf::Vector2f direction = mousePosWorld - playerPos;

        // d. 正規化向量 (讓長度變成 1)
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }

        // e. 發射子彈！
        projectiles.push_back(Projectile(playerPos, direction));
        
        // f. 重置冷卻時間 (例如 0.15 秒發射一次)
        shootCooldown = 0.15f; 
    }

    // 4. 更新子彈與清理 (與原本相同)
    for (auto& p : projectiles) p.update(dt);
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return p.isExpired(); }), projectiles.end());
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
    for (auto& p : projectiles) p.draw(window);
}
