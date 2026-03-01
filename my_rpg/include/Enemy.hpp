#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
    // 傳入生成位置
    Enemy(sf::Vector2f startPos);
    
    // 更新邏輯需要知道玩家現在在哪裡
    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);
    
    // 取得怪物的碰撞框
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    
    // 狀態管理
    bool isDead() const { return dead; }
    void takeDamage() { dead = true; } // 目前一發子彈就死

private:
    sf::RectangleShape shape;
    float speed;
    bool dead;
};

#endif
