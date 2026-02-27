#include "Projectile.hpp"

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir) 
    : direction(dir), speed(600.0f), lifetime(2.0f) {
    
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(5.f, 5.f);
    shape.setPosition(pos);
}

void Projectile::update(float dt) {
    shape.move(direction * speed * dt);
    lifetime -= dt;
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
