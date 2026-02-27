#include <iostream>

int main() {
    bool isRunning = true;
    char userChoice;

    std::cout << "=== Dungeon Crawler System v0.1 ===\n";

    // 遊戲主迴圈 (Game Loop)
    // 這是所有遊戲引擎 (Unreal, Unity) 的核心架構
    while (isRunning) {
        std::cout << "\n[1] Start Game\n";
        std::cout << "[2] Game Options\n";
        std::cout << "[3] Quit\n";
        std::cout << "Enter selection: ";
        
        std::cin >> userChoice;

        std::cout << "---------------------------\n";

        // 使用 switch 取代冗長的 if-else if-else
        switch (userChoice) {
            case '1':
                std::cout << "Initializing World... (TODO)\n";
                // 這裡未來會呼叫 GameInit() 函式
                break;
            
            case '2':
                std::cout << "Settings:\n";
                std::cout << " - Difficulty: Hard\n";
                std::cout << " - Sound: ON\n";
                break;

            case '3':
                std::cout << "Exiting Game. Goodbye!\n";
                isRunning = false; // 打破迴圈條件
                break;

            default:
                std::cout << "Invalid input! Please enter 1, 2, or 3.\n";
                break;
        }
    }

    return 0;
}
