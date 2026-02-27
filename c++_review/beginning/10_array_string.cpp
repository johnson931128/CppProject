#include <iostream>
#include <cstring> // 為了使用 strlen (雖然我們會手寫一個)

int main() {
    // 1. 定義一個標準的 C-Style String
    // 編譯器看到雙引號 ""，它心裡想的是：「主人要定義一個字串，字串必須要有結尾」 
    // 編譯器會自動在最後補上 '\0'，所以實際大小是 5 + 1 = 6 bytes
    char name[] = "Hello";

    std::cout << "=== Memory Layout of 'Hello' ===\n";
    // 我們用迴圈把每個 byte 印出來看
    // sizeof(name) 會包含最後的 \0
    for (int i = 0; i < (int)sizeof(name); i++) {
        std::cout << "Index " << i 
                  << ": '" << name[i] << "'"
                  << " (ASCII: " << (int)name[i] << ")"
                  << " at " << (void*)&name[i] << "\n";
    }
    std::cout << "Note: ASCII 0 is the Null Terminator '\\0'!\n\n";

    // 2. 危險實驗：沒有 \0 的字串
    // 我們故意宣告一個 char 陣列，但不給它結束符號
    // 編譯器心裡想的是：「主人給我一個字元清單，要我依序放入陣列」
    // 結束了嗎？好，那我就停手。
    char dangerous[] = {'C', '+', '+'}; 
    
    std::cout << "=== The Danger of Missing \\0 ===\n";
    std::cout << "Safe String: " << name << "\n";
    
    // 下面這行非常危險！cout 會一直往後印，直到運氣好撞到 0 為止
    // 你可能會看到 "C++Hello" 或是後面跟著一堆亂碼
    std::cout << "Unsafe String: " << dangerous << " (Watch out!)\n\n";

    // 3. 實戰：利用指標手動計算字串長度 (模擬 strlen)
    std::cout << "=== Manual Strlen Implementation ===\n";
    const char* ptr = name;
    int count = 0;
    
    // 迴圈條件：只要 *ptr 不是 0，就繼續走
    while (*ptr != '\0') {
        count++;
        ptr++; // 指標往後移一格
    }
    
    std::cout << "Calculated Length: " << count << "\n";
    std::cout << "Standard strlen  : " << strlen(name) << "\n";

    return 0;
}
