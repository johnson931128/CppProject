#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    // 建立 800x600 的視窗
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hollow Clone - Physics Engine");

    // 遊戲主迴圈
    while (window.isOpen()) {
        // 處理視窗事件 (SFML 3.0 寫法)
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // 清空畫面為黑色
        window.clear(sf::Color::Black);

        // 顯示畫面
        window.display();
    }

    return 0;
}
