#include <iostream>

int main() {
    // 1. 定義一個普通的整數變數 (本尊)
    int powerLevel = 9000;

    // 2. 定義一個指標 (分身/遙控器)
    // 語法：型別* 變數名稱 = &目標變數;
    // '&' 是 "取址運算子" (Address-of Operator)，用來拿門牌號碼
    int* ptr = &powerLevel;

    std::cout << "=== Pointer Initialization ===\n";
    std::cout << "Value of powerLevel : " << powerLevel << "\n";
    std::cout << "Addr of powerLevel  : " << &powerLevel << "\n";
    std::cout << "Value of ptr        : " << ptr << " (應該跟上面一樣)\n";
    std::cout << "Addr of ptr         : " << &ptr << " (指標自己也有住址!)\n";

    // 3. 關鍵測試：指標的大小
    // 不管指向 int, double, 還是超大 struct，指標本身只存地址
    // 在 64-bit 系統上，地址就是 64-bit (8 bytes)
    std::cout << "Size of ptr         : " << sizeof(ptr) << " bytes\n";

    // 4. 解參照 (Dereferencing) - 使用遙控器
    // 這裡的 '*' 代表 "存取指向的目標"
    std::cout << "\n=== Dereferencing ===\n";
    std::cout << "Value at *ptr       : " << *ptr << "\n"; // 讀取

    *ptr = 9999; // 修改 (寫入)
    std::cout << "You changed *ptr to 9999...\n";
    
    // 5. 見證奇蹟
    std::cout << "Value of powerLevel : " << powerLevel << " (本尊被改了!)\n";

    return 0;
}
