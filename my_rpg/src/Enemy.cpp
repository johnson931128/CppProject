#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f startPos) : speed(100.0f), dead(false) {
    // 怪物設定為一個紅色的正方形
    shape.setSize(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::Red);
    // 把原點設在中心 (15, 15)
    shape.setOrigin(15.f, 15.f);
    shape.setPosition(startPos);
}

void Enemy::update(float dt, sf::Vector2f playerPos) {
    if (dead) return;

    // 計算方向向量: 玩家位置 - 怪物位置
    sf::Vector2f currentPos = shape.getPosition();
    sf::Vector2f direction = playerPos - currentPos;

    // 正規化向量
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // 往玩家方向移動
    shape.move(direction * speed * dt);
}

void Enemy::draw(sf::RenderWindow& window) {
    if (!dead) {
        window.draw(shape);
    }
}
