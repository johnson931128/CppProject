#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // 給 rand(), srand() 使用
#include <ctime>   // 給 time() 使用，用來設定隨機亂數種子
#include <cmath>   // 給 std::floor() 使用，用來平滑相機

#include "Player.hpp"
#include "Enemy.hpp"

int main() {
    // 1. 初始化視窗 (配合你的 200Hz 螢幕，拉高渲染上限)
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSIE5004 - My Top-down RPG");
    window.setFramerateLimit(200); 

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
    float spawnTimer = 0.f; 

    // ======== Fixed Time Step 的核心變數 ========
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 固定每秒更新 60 次物理邏輯
    sf::Time timeSinceLastUpdate = sf::Time::Zero;         // 時間累加器

    // 3. 遊戲主迴圈
    while (window.isOpen()) {
        // 每次迴圈收集經過的時間，加入累加器
        sf::Time elapsedTime = clock.restart();
        
        // 【防呆機制】：避免切換視窗或卡頓時累積過多時間，導致一次更新太多次
        if (elapsedTime.asSeconds() > 0.1f) {
            elapsedTime = sf::seconds(0.1f);
        }
        timeSinceLastUpdate += elapsedTime;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // ======== 核心修改：固定時間步長 (Fixed Update) ========
        // 只要累積的時間超過 1/60 秒，就執行一次邏輯更新
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            
            // 這裡的 fixedDt 永遠是固定的 0.01666... 秒！
            float fixedDt = TimePerFrame.asSeconds(); 

            // --- 所有的「更新邏輯」都要放在這個迴圈裡面 ---
            
            // 1. 更新玩家與子彈
            player.update(fixedDt, window);

            // 2. 怪物生成邏輯
            spawnTimer += fixedDt;
            if (spawnTimer > 2.0f) {
                float randomX = static_cast<float>(rand() % 2000);
                float randomY = static_cast<float>(rand() % 2000);
                enemies.push_back(Enemy(sf::Vector2f(randomX, randomY)));
                spawnTimer = 0.f;
            }

            // 3. 更新怪物位置
            for (auto& enemy : enemies) {
                enemy.update(fixedDt, player.getPosition());
            }

            // 4. 碰撞偵測
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

            // 5. 清理死亡怪物
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                [](const Enemy& e) { return e.isDead(); }), enemies.end());
                
            // --- 更新邏輯結束 ---
        }

        // ======== 繪製與相機更新區 ========
        
        // 相機跟隨玩家 (放在邏輯更新完之後，繪製之前)
        sf::Vector2f playerPos = player.getPosition();
        view.setCenter(std::floor(playerPos.x), std::floor(playerPos.y));

        window.clear();
        
        // 告訴 window 接下來的繪製都要套用這個相機視角
        window.setView(view);

        // 依序繪製背景、怪物、玩家(包含子彈)
        window.draw(background);
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        player.draw(window);

        window.display();
    }
    return 0;
}
