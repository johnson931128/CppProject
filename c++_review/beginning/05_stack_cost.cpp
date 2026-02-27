#include <iostream>

// 定義一個模擬遊戲怪物的結構
struct Monster {
    long long id; // 8 bytes
    int hp;       // 4 bytes
    int mp;       // 4 bytes
    // 故意塞一個陣列讓它變「胖」，增加複製的成本
    // 100 * 4 bytes = 400 bytes
    int rawData[100]; 
};

// 測試函式：使用預設的 Pass-by-Value (傳值)
// 參數 m 在這裡會是 main 裡面的 boss 的「複製品」
void verifyCopy(Monster m) {
    std::cout << "\n--- Inside Function (verifyCopy) ---\n";
    std::cout << "  Address of m: " << &m << " (注意看這裡!)\n";
    std::cout << "  Size of m   : " << sizeof(m) << " bytes\n";
    
    // 試圖修改血量
    std::cout << "  Action: Attacking clone! Setting HP to 0...\n";
    m.hp = 0;
}

int main() {
    Monster boss;
    boss.id = 999;
    boss.hp = 10000;

    std::cout << "=== Pass-by-Value Cost Test ===\n";
    std::cout << "Original Boss HP: " << boss.hp << "\n";
    std::cout << "Address of Boss : " << &boss << "\n";
    std::cout << "Size of Boss    : " << sizeof(boss) << " bytes\n";

    // 呼叫函式，這瞬間發生了 Memory Copy
    verifyCopy(boss);

    std::cout << "\n--- Back in Main ---\n";
    // 驗證：如果真的是複製，原本的 boss 血量應該還是 10000
    std::cout << "Original Boss HP: " << boss.hp << "\n";
    
    if (boss.hp == 10000) {
        std::cout << "Conclusion: The original was NOT modified. (Safe but slow)\n";
    } else {
        std::cout << "Conclusion: The original WAS modified.\n";
    }

    return 0;
}
