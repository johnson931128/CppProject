#include <SFML/Graphics.hpp>

int main() {
    // 建立一個 800x600 的視窗
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - My RPG Game");

    // 建立代表玩家的物件 (這之後會換成 Sprite)
    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 簡單的移動邏輯 (基礎向量操作)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0, -0.1f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0, 0.1f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-0.1f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(0.1f, 0);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
