#include <iostream>
#include <chrono>
#include <thread>

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

  // 建立連續記憶體配置：宣告並初始化一個大小為 3 的 Enemy 陣列
  Enemy enemies[3] = {
    {1, 0.0f, 10.0f, 1.5f}, // id: 1, 初始位置 (0, 10), 速度 1.5
    {2, 0.0f, 20.0f, 2.0f}, // id: 2, 初始位置 (0, 20), 速度 2.0
    {3, 0.0f, 30.0f, 1.0f}  // id: 3, 初始位置 (0, 30), 速度 1.0
  };

  while (isRunning) {
    // 1. Process Input (處理輸入 - 暫時留空)

    // 2. Update (更新狀態)
    frameCount++;
    // 使用 for 迴圈走訪陣列，更新每隻怪物的 X 座標
    for (int i = 0; i < 3; i++) {
      // 撞到右牆 (x >= 12) 且正在往右走，或是撞到左牆 (x <= 0) 且正在往左走
      if ((enemies[i].x >= 12.0f && enemies[i].speed > 0) || 
          (enemies[i].x <= 0.0f && enemies[i].speed < 0)) {
        enemies[i].speed *= -1; // 速度反轉
      }
      enemies[i].x += enemies[i].speed; // 加上當前速度（可能是正或負）
    }

    // 3. Render (渲染畫面)
    std::cout << "\n--- [Render] Frame: " << frameCount << " ---\n";
    for (int i = 0; i < 3; i++) {
      std::cout << "Enemy " << enemies[i].id 
                << " pos: (" << enemies[i].x << ", " << enemies[i].y << ")\n";
    }

    // 模擬幀率控制 (強制休眠 500 毫秒)
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 延長測試時間到 10 幀，觀察跑最快的 Enemy 2 反彈效果
    if (frameCount >= 10) {
      isRunning = false;
      std::cout << "\n[System] Shutting down Engine...\n";
    }
  }

  return 0;
}
