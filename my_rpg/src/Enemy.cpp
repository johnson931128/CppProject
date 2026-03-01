#include "Enemy.hpp"
#include <cmath>

// 稍微把怪物速度調慢一點，讓玩家有機會逃跑
Enemy::Enemy(sf::Vector2f startPos) : speed(120.0f), dead(false) {
    shape.setSize(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(15.f, 15.f);
    shape.setPosition(startPos);
}

void Enemy::update(float dt, sf::Vector2f playerPos) {
    if (dead) return;

    sf::Vector2f currentPos = shape.getPosition();
    sf::Vector2f direction = playerPos - currentPos;

    // 1. 計算怪物與玩家的直線距離 (畢氏定理)
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // 2. 警戒範圍判定 (例如 400 像素)
    float aggroRadius = 100.0f;

    // 只有當玩家進入警戒範圍時，才進行追擊
    if (distance < aggroRadius) {
        // 正規化向量
        if (distance > 0) {
            direction.x /= distance; // 這裡直接除以 distance 即可，比較快
            direction.y /= distance;
        }

        // 往玩家方向移動
        shape.move(direction * speed * dt);
    }
    
    // ======== 大世界邊界限制 (假設地圖放大到 3000 x 3000) ========
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 15.f) pos.x = 15.f;
    if (pos.x > 2985.f) pos.x = 2985.f; 
    if (pos.y < 15.f) pos.y = 15.f;
    if (pos.y > 2985.f) pos.y = 2985.f;   
    shape.setPosition(pos);
}

void Enemy::draw(sf::RenderWindow& window) {
    if (!dead) {
        window.draw(shape);
    }
}
