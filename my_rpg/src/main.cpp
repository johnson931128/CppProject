#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Top-down RPG");
    window.setFramerateLimit(60);

    Player player;
    
    // 初始化相機
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // 建立一個簡單的大地圖背景 (2000x2000)
    sf::RectangleShape background(sf::Vector2f(2000, 2000));
    background.setFillColor(sf::Color(50, 50, 50)); 
    background.setPosition(0, 0);

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // 更新玩家邏輯 (內部會一併更新子彈)
        player.update(dt);

        // 讓相機中心點對齊玩家座標
        view.setCenter(player.getPosition());

        window.clear();

        // 告訴 window 接下來的繪製都要套用這個相機視角
        window.setView(view);

        // 繪製順序：先畫背景，再畫玩家(與子彈)
        window.draw(background);
        player.draw(window);

        window.display();
    }
    return 0;
}
