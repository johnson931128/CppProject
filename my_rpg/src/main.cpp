#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <cmath>   

#include "Player.hpp"
#include "Enemy.hpp"

int main() {
    // 1. 初始化視窗
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - Open World ARPG");
    window.setFramerateLimit(200); 

    srand(static_cast<unsigned>(time(NULL)));

    Player player;
    std::vector<Enemy> enemies; 
    
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // ======== 1. 大世界地圖背景 ========
    // 放大到 3000 x 3000，並塗成暗綠色代表野外
    sf::RectangleShape background(sf::Vector2f(3000, 3000));
    background.setFillColor(sf::Color(40, 70, 40)); 
    background.setPosition(0, 0);

    // ======== 2. 初始生成原生生態系怪物 ========
    // 遊戲開始前，直接在廣大的地圖上散佈 100 隻怪物
    for (int i = 0; i < 100; ++i) {
        float randomX, randomY;
        float distanceToPlayer;
        
        // 使用 do-while 迴圈：如果隨機骰出來的座標離玩家起始點 (400, 300) 太近，就強制重骰！
        do {
            randomX = static_cast<float>(rand() % 2900 + 50);
            randomY = static_cast<float>(rand() % 2900 + 50);
            
            // 計算這個隨機座標與玩家初始位置 (400, 300) 的直線距離
            float dx = randomX - 400.f;
            float dy = randomY - 300.f;
            distanceToPlayer = std::sqrt(dx * dx + dy * dy);
            
        } while (distanceToPlayer < 600.0f); // 如果距離小於 600 像素，就不斷重骰

        enemies.push_back(Enemy(sf::Vector2f(randomX, randomY)));
    }

    sf::Clock clock;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // 3. 遊戲主迴圈
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        if (elapsedTime.asSeconds() > 0.1f) {
            elapsedTime = sf::seconds(0.1f);
        }
        timeSinceLastUpdate += elapsedTime;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // ======== 固定時間步長 (Fixed Update) ========
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            float fixedDt = TimePerFrame.asSeconds(); 

            // 1. 更新玩家與子彈
            player.update(fixedDt, window);

            // 2. 更新怪物 (怪物內部已經有警戒範圍邏輯了)
            for (auto& enemy : enemies) {
                enemy.update(fixedDt, player.getPosition());
            }

            // 3. 碰撞偵測 (子彈 vs 怪物)
            auto& projectiles = player.getProjectiles();
            for (auto& p : projectiles) {
                for (auto& enemy : enemies) {
                    if (!p.isExpired() && !enemy.isDead() && 
                        p.getBounds().intersects(enemy.getBounds())) {
                        p.destroy();       
                        enemy.takeDamage();
                    }
                }
            }

            // 4. 清理死亡怪物
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                [](const Enemy& e) { return e.isDead(); }), enemies.end());
        }

        // ======== 繪製與相機更新區 ========
        sf::Vector2f playerPos = player.getPosition();
        view.setCenter(std::floor(playerPos.x), std::floor(playerPos.y));

        window.clear();
        window.setView(view);

        window.draw(background);
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        player.draw(window);

        window.display();
    }
    return 0;
}
