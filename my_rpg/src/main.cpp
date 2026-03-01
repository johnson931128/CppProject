#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // 給 rand(), srand() 使用
#include <ctime>   // 給 time() 使用，用來設定隨機亂數種子
#include <cmath>   // 給 std::floor() 使用，用來平滑相機

#include "Player.hpp"
#include "Enemy.hpp"

int main() {
    // 1. 初始化視窗
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - My Top-down RPG");
    window.setFramerateLimit(60);

    // 設定隨機亂數種子，確保每次開遊戲怪物生的位置不一樣
    srand(static_cast<unsigned>(time(NULL)));

    // 2. 初始化遊戲物件
    Player player;
    std::vector<Enemy> enemies; // 管理畫面上所有怪物的陣列
    
    // 初始化相機
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // 建立一個簡單的大地圖背景 (2000x2000)
    sf::RectangleShape background(sf::Vector2f(2000, 2000));
    background.setFillColor(sf::Color(50, 50, 50)); 
    background.setPosition(0, 0);

    sf::Clock clock;
    float spawnTimer = 0.f; // 用來計時何時該生下一隻怪物

    // 3. 遊戲主迴圈
    while (window.isOpen()) {
        // 計算時間差 (dt)
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f; // 避免切換視窗時 dt 過大導致破圖

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // ======== 更新邏輯區 ========

        // 更新玩家邏輯 (內部會一併處理移動、射擊與更新子彈)
        player.update(dt, window);

        // 怪物生成邏輯：每 2 秒生成一隻怪物
        spawnTimer += dt;
        if (spawnTimer > 2.0f) {
            float randomX = static_cast<float>(rand() % 2000);
            float randomY = static_cast<float>(rand() % 2000);
            enemies.push_back(Enemy(sf::Vector2f(randomX, randomY)));
            spawnTimer = 0.f; // 重置計時器
        }

        // 更新所有怪物的位置 (讓牠們朝玩家走)
        for (auto& enemy : enemies) {
            enemy.update(dt, player.getPosition());
        }

        // 碰撞偵測：子彈 vs 怪物
        auto& projectiles = player.getProjectiles(); // 取得玩家發射的真實子彈清單
        for (auto& p : projectiles) {
            for (auto& enemy : enemies) {
                // 如果子彈跟怪物都活著，而且兩者的碰撞框重疊了
                if (!p.isExpired() && !enemy.isDead() && 
                    p.getBounds().intersects(enemy.getBounds())) {
                    
                    p.destroy();       // 子彈標記為銷毀
                    enemy.takeDamage();// 怪物標記為死亡
                }
            }
        }

        // 清理死亡的怪物 (Erase-Remove Idiom)
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return e.isDead(); }), enemies.end());

        // 相機跟隨玩家，並將座標轉為整數以消除畫面微抖動 (Camera Jitter)
        sf::Vector2f playerPos = player.getPosition();
        view.setCenter(std::floor(playerPos.x), std::floor(playerPos.y));


        // ======== 繪製邏輯區 ========
        window.clear();

        // 告訴 window 接下來的繪製都要套用這個相機視角
        window.setView(view);

        // 1. 先畫最底層的背景
        window.draw(background);

        // 2. 畫怪物
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        // 3. 畫玩家 (內部會一併把子彈畫出來，所以子彈會蓋在怪物上面)
        player.draw(window);

        window.display();
    }
    return 0;
}
