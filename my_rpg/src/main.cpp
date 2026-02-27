#include <SFML/Graphics.hpp>

int main() {
    // 建立視窗
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - My RPG Game");

    // 建議方案：在虛擬機中，手動限幀通常比 VSync 穩定的多
    // 1. 註解掉 VSync
    // window.setVerticalSyncEnabled(true); 
    // 2. 改用限制影格率在 60 FPS
    window.setFramerateLimit(60); 

    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);

    sf::Clock clock;
    const float speed = 200.0f;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // 檢查時間：如果 dt 太大（例如切換視窗導致卡頓），強制校正避免噴裝
        if (dt > 0.1f) dt = 0.1f;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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
