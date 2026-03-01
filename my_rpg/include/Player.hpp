#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.hpp"

class Player {
public:
    Player();
    // 修改這裡：把 window 傳進來
    void update(float dt, const sf::RenderWindow& window); 
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    std::vector<Projectile>& getProjectiles() { return projectiles; }
private:
    sf::CircleShape shape;
    float speed;
    std::vector<Projectile> projectiles;
    
    // 新增：射擊冷卻時間
    float shootCooldown; 
};

#endif
