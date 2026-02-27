#include <iostream>

int main() {
    int highVal = 100;
    int lowVal = 10;

    std::cout << "=== 1. Pointer to Constant (保護內容) ===\n";
    // const 在 * 左邊：內容不可改
    const int* pContent = &highVal; 
    
    // *pContent = 50;  // <--- 錯誤！(Read-only variable is not assignable)
    // 試著把上面這行註解拿掉編譯看看
    
    std::cout << "Original Addr: " << pContent << ", Value: " << *pContent << "\n";
    
    pContent = &lowVal; // OK！指標本身(地址)可以改，我現在指別人家
    std::cout << "New Addr     : " << pContent << ", Value: " << *pContent << "\n";


    std::cout << "\n=== 2. Constant Pointer (保護地址) ===\n";
    // const 在 * 右邊：地址不可改
    int* const pAddress = &highVal;
    
    *pAddress = 500;    // OK！內容可以改
    std::cout << "Value changed via pAddress: " << highVal << "\n";
    
    // pAddress = &lowVal; // <--- 錯誤！(Cannot assign to variable 'pAddress' with const-qualified type)
    // 試著把上面這行註解拿掉編譯看看


    std::cout << "\n=== 3. Constant Pointer to Constant (雙重保護) ===\n";
    // 兩邊都有 const
    const int* const pDual = &highVal;
    
    // *pDual = 0;       // <--- 錯誤！內容不可改
    // pDual = &lowVal;  // <--- 錯誤！地址不可改

    std::cout << "Value at pDual: " << *pDual << " (Safe and Locked)\n";

    return 0;
}
