#include <iostream>

int main() {
    // 1. 宣告不同型別的變數
    // 這些變數會被配置在 Stack (堆疊) 上
    bool myBool = true;
    char myChar = 'A';
    int myInt = 123456789;
    double myDouble = 3.14159;

    std::cout << "--- Variable Inspector ---" << std::endl;

    // 2. 觀察 bool
    std::cout << "Type: bool\n";
    std::cout << "  Value: " << myBool << "\n";
    std::cout << "  Size : " << sizeof(myBool) << " byte(s)\n";
    std::cout << "  Addr : " << &myBool << "\n\n";

    // 3. 觀察 char (關鍵點！)
    std::cout << "Type: char\n";
    std::cout << "  Value: " << myChar << "\n";
    std::cout << "  Size : " << sizeof(myChar) << " byte(s)\n";
    // 注意：如果是 char*，std::cout 會以為你是要印字串而不是位址。
    // 所以必須強制轉型成 (void*) 讓它顯示記憶體位址。
    std::cout << "  Addr : " << (void*)&myChar << "\n\n";

    // 4. 觀察 int
    std::cout << "Type: int\n";
    std::cout << "  Value: " << myInt << "\n";
    std::cout << "  Size : " << sizeof(myInt) << " byte(s)\n";
    std::cout << "  Addr : " << &myInt << "\n\n";

    // 5. 觀察 double
    std::cout << "Type: double\n";
    std::cout << "  Value: " << myDouble << "\n";
    std::cout << "  Size : " << sizeof(myDouble) << " byte(s)\n";
    std::cout << "  Addr : " << &myDouble << "\n";

    return 0;
}
