#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.hpp"

class Player {
public:
    Player();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const { return shape.getPosition(); }

private:
    sf::CircleShape shape;
    float speed;
    std::vector<Projectile> projectiles; // 管理玩家發射的所有子彈
};

#endif
