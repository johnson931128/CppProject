#include <iostream>
#include <chrono>
#include <thread>
#include <stack>  // 引入 C++ STL 的 Stack

// 定義遊戲狀態 (列舉型別)
enum class GameState { MENU, PLAYING, PAUSE };

// 定義遊戲實體資料結構：敵人 (Enemy)
struct Enemy {
  int id;
  float x;
  float y;
  float speed;
};

int main() {
  bool isRunning = true;
  int frameCount = 0;

  std::cout << "[System] SoulKnightLite Engine Starting...\n";

  // 建立遊戲狀態機 (Stack)
  std::stack<GameState> stateStack;
  // 遊戲啟動時，先將「主選單」推入堆疊
  stateStack.push(GameState::MENU);

  Enemy enemies[3] = {
    {1, 0.0f, 10.0f, 1.5f}, 
    {2, 0.0f, 20.0f, 2.0f}, 
    {3, 0.0f, 30.0f, 1.0f}  
  };

  while (isRunning) {
    frameCount++;
    
    // 取得當前位於堆疊最上層的狀態
    GameState currentState = stateStack.top();

    // 1. Process Input (模擬玩家按鍵操作)
    if (frameCount == 3 && currentState == GameState::MENU) {
      std::cout << "\n>>> [輸入事件] 玩家點擊了「開始遊戲」！ <<<\n";
      stateStack.push(GameState::PLAYING); // 推入遊玩狀態
    } 
    else if (frameCount == 7 && currentState == GameState::PLAYING) {
      std::cout << "\n>>> [輸入事件] 玩家按下了「暫停鍵 (ESC)」！ <<<\n";
      stateStack.push(GameState::PAUSE);   // 推入暫停狀態
    } 
    else if (frameCount == 10 && currentState == GameState::PAUSE) {
      std::cout << "\n>>> [輸入事件] 玩家再次按下「暫停鍵 (ESC)」，解除暫停！ <<<\n";
      stateStack.pop(); // 彈出暫停狀態，自動回到下層的 PLAYING 狀態
    }

    // 更新 currentState，因為剛才的 Input 可能改變了堆疊最上層
    currentState = stateStack.top();

    // 2. Update (更新狀態)
    // 【核心邏輯】：只有在 PLAYING 狀態時，物理引擎與怪物才會更新！
    if (currentState == GameState::PLAYING) {
      for (int i = 0; i < 3; i++) {
        if ((enemies[i].x >= 12.0f && enemies[i].speed > 0) || 
            (enemies[i].x <= 0.0f && enemies[i].speed < 0)) {
          enemies[i].speed *= -1; 
        }
        enemies[i].x += enemies[i].speed; 
      }
    }

    // 3. Render (渲染畫面)
    std::cout << "\n--- [Render] Frame: " << frameCount << " ---\n";
    
    if (currentState == GameState::MENU) {
      std::cout << "[UI] === 遊戲主選單 (Main Menu) ===\n";
      std::cout << "[UI] 等待玩家開始遊戲...\n";
    } 
    else if (currentState == GameState::PLAYING) {
      for (int i = 0; i < 3; i++) {
        std::cout << "Enemy " << enemies[i].id 
                  << " pos: (" << enemies[i].x << ", " << enemies[i].y << ")\n";
      }
    } 
    else if (currentState == GameState::PAUSE) {
      std::cout << "[UI] === 遊戲已暫停 (Game Paused) ===\n";
      std::cout << "[UI] 怪物位置已被凍結，等待解除暫停...\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 測試時間延長到 12 幀
    if (frameCount >= 12) {
      isRunning = false;
      std::cout << "\n[System] Shutting down Engine...\n";
    }
  }

  return 0;
}
