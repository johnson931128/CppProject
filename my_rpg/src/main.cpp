#include <SFML/Graphics.hpp>

int main() {
    // 1. 建立視窗並開啟垂直同步，解決卡頓核心問題
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - My RPG Game");
    window.setVerticalSyncEnabled(true); 

    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);

    // 2. 準備時鐘來計算時間步長 (Delta Time)
    sf::Clock clock;
    const float speed = 200.0f; // 每秒移動的像素

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 3. 根據時間步長移動，確保動作平滑
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;

        player.move(movement * dt);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
