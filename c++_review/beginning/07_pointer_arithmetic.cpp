#include <iostream>

int main() {
    // 1. 定義一個陣列
    // 在記憶體中，這是連續排列的 5 個整數
    int scores[] = {10, 20, 30, 40, 50};

    // 2. 陣列名稱其實就是指向第一個元素的指標
    // scores 等同於 &scores[0]
    int* ptr = scores;

    std::cout << "=== Array vs Pointer Identity ===\n";
    std::cout << "Addr of scores    : " << scores << "\n";
    std::cout << "Addr of scores[0] : " << &scores[0] << "\n";
    std::cout << "Value of ptr      : " << ptr << " (Should match)\n\n";

    std::cout << "=== Pointer Arithmetic (The Magic) ===\n";
    // 觀察重點：看位址每次增加多少？(應該是 4，因為 int 是 4 bytes)
    std::cout << "ptr     : " << ptr << "  -> Value: " << *ptr << "\n";
    
    ptr = ptr + 1; // 移動到下一個 int
    std::cout << "ptr + 1 : " << ptr << "  -> Value: " << *ptr << "\n";

    ptr = ptr + 1; 
    std::cout << "ptr + 2 : " << ptr << "  -> Value: " << *ptr << "\n\n";

    std::cout << "=== The Secret Formula ===\n";
    // 陣列取值的真相：arr[i] 等同於 *(arr + i)
    std::cout << "Using array index scores[3] : " << scores[3] << "\n";
    std::cout << "Using pointer math *(ptr+1) : " << *(scores + 3) << "\n";
    
    // 甚至可以這樣寫 (C++ 面試題常見陷阱，但在專案中別這樣寫 XD)
    std::cout << "Weird syntax 3[scores]      : " << 3[scores] << "\n";

    return 0;
}
