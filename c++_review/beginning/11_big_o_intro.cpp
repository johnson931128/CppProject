#include <iostream>
#include <vector>

// 1. O(N) 線性搜尋模擬
// 情境：在背包裡一個一個找某個 ID 的物品
void simulateLinear(int n) {
    long long steps = 0;
    std::cout << "--- O(N) Linear Search (N = " << n << ") ---\n";
    
    // 模擬：最壞情況，目標在最後一個
    for (int i = 0; i < n; i++) {
        steps++; // 紀錄運算次數
        if (i == n - 1) { // 找到了
            break;
        }
    }
    std::cout << "Steps taken: " << steps << "\n";
}

// 2. O(N^2) 雙重迴圈模擬
// 情境：檢查 N 隻怪物是否兩兩互相碰撞
void simulateQuadratic(int n) {
    long long steps = 0;
    std::cout << "--- O(N^2) Nested Loop (N = " << n << ") ---\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            steps++; // 這裡會跑 N * N 次
        }
    }
    std::cout << "Steps taken: " << steps << "\n";
}

// 3. O(1) 直接存取模擬
// 情境：知道 ID 直接拿資料 (Array Index / Hash Map)
void simulateConstant(int n) {
    long long steps = 0;
    std::cout << "--- O(1) Constant Access (N = " << n << ") ---\n";
    
    // 不管 N 是多少，我只做一次動作
    if (n > 0) {
        steps++;
    }
    std::cout << "Steps taken: " << steps << " (Instant!)\n";
}

int main() {
    // 測試案例 1：小規模數據 (10)
    int smallN = 10;
    std::cout << "=== Small Scale (N=10) ===\n";
    simulateLinear(smallN);
    simulateQuadratic(smallN);
    simulateConstant(smallN);
    
    std::cout << "\n";

    // 測試案例 2：大規模數據 (1000)
    // 注意看 O(N^2) 會暴增到多可怕
    int largeN = 1000;
    std::cout << "=== Large Scale (N=1000) ===\n";
    simulateLinear(largeN);
    simulateQuadratic(largeN); // 預測：這應該會是一百萬
    simulateConstant(largeN);

    std::cout << "\n=== The Lesson ===\n";
    std::cout << "If N becomes 10,000:\n";
    std::cout << " - O(N)   Wait time: ~0.01 ms\n";
    std::cout << " - O(N^2) Wait time: ~100 ms (Lag starts here!)\n";
    std::cout << "Avoid Nested Loops in Update() functions!\n";

    return 0;
}
