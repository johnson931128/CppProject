#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(sf::Vector2f pos, sf::Vector2f dir);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isExpired() const { return lifetime <= 0.f; }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    void destroy() { lifetime = 0.f; }

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;
    float lifetime;
};

#endif
