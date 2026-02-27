#include <iostream>

int main() {
    // __cplusplus 是一個預定義的巨集，會根據編譯標準顯示不同的數值
    // C++17 應該顯示 201703L
    std::cout << "Environment Check OK." << std::endl;
    std::cout << "Standard Version: " << __cplusplus << std::endl;
    return 0;
}
