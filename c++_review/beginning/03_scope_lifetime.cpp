#include <iostream>

// 全域變數 (Global Variable) - 程式結束前都在
int globalVar = 100;

void testFunction() {
    int localVar = 200;
    std::cout << "Inside Function:\n";
    std::cout << "  Global Addr: " << &globalVar << "\n";
    std::cout << "  Local  Addr: " << &localVar << "\n";
}

int main() {
    std::cout << "Inside Main (Before Call):\n";
    std::cout << "  Global Addr: " << &globalVar << "\n";
    
    // 呼叫函式
    testFunction();

    // 這裡我們做一個大括號區塊 (Block Scope)
    {
        int blockVar = 300;
        std::cout << "Inside Block:\n";
        std::cout << "  Block Var Addr: " << &blockVar << "\n";
    } // blockVar 在這裡死亡

    // 思考：如果你這時候試圖去存取 blockVar 的位址，會發生什麼事？
    // 答：編譯器會報錯，因為名稱已經看不到了。
    
    return 0;
}
