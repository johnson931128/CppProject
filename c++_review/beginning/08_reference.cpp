#include <iostream>

// 1. 傳統 C 語言風格：用指標來交換數值
// 呼叫時很麻煩，要傳地址：swapByPtr(&a, &b);
void swapByPtr(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 2. C++ 風格：用參照來交換數值
// 呼叫時超自然：swapByRef(a, b);
// 這裡的 a 和 b 只是外部變數的「綽號」，操作它們就是操作本尊
void swapByRef(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int hp = 100;
    
    // --- 基礎語法：建立參照 ---
    // 語法：型別& 參照名稱 = 目標變數;
    int& hpRef = hp; 

    std::cout << "=== Reference Basics ===\n";
    std::cout << "Original HP : " << hp << "\n";
    std::cout << "Ref HP      : " << hpRef << "\n";

    // 修改參照 = 修改本尊
    hpRef = 50;
    std::cout << "After hpRef=50, Original HP is: " << hp << " (Changed!)\n";

    // --- 關鍵差異：記憶體位址 ---
    // 指標自己有獨立地址，但「參照的地址」就是「本尊的地址」
    std::cout << "Addr of HP  : " << &hp << "\n";
    std::cout << "Addr of Ref : " << &hpRef << " (Exactly the same!)\n\n";

    // --- 實戰：Swap 函式 ---
    int x = 10, y = 20;
    std::cout << "=== Swapping ===\n";
    std::cout << "Before: x=" << x << ", y=" << y << "\n";

    // 使用指標交換 (寫法較囉嗦)
    swapByPtr(&x, &y); 
    std::cout << "Ptr Swap: x=" << x << ", y=" << y << "\n";

    // 使用參照交換 (寫法像傳值，但效果像傳址)
    swapByRef(x, y);
    std::cout << "Ref Swap: x=" << x << ", y=" << y << "\n";

    return 0;
}
