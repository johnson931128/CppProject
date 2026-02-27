#include <iostream>
#include <vector>
#include <algorithm> // 為了 std::sort (雖然我們這次直接依序塞入)

// 回傳 pair: <找到的索引, 花費的步數>
// 如果沒找到，索引回傳 -1
std::pair<int, int> linearSearch(const std::vector<int>& data, int target) {
    int steps = 0;
    for (size_t i = 0; i < data.size(); i++) {
        steps++;
        if (data[i] == target) {
            return { (int)i, steps };
        }
    }
    return { -1, steps };
}

std::pair<int, int> binarySearch(const std::vector<int>& data, int target) {
    int steps = 0;
    int left = 0;
    int right = (int)data.size() - 1;

    while (left <= right) {
        steps++;
        // 算出中間點 (防止 (left+right) 溢位的寫法)
        int mid = left + (right - left) / 2;

        if (data[mid] == target) {
            return { mid, steps }; // 找到了
        }
        
        if (data[mid] < target) {
            // 目標在右邊，左邊界縮進來
            left = mid + 1;
        } else {
            // 目標在左邊，右邊界縮進來
            right = mid - 1;
        }
    }
    return { -1, steps };
}

int main() {
    // 1. 準備數據：一百萬個已排序的數字
    int N = 1000000;
    std::cout << "Generating dataset of size " << N << "...\n";
    std::vector<int> sortedData;
    sortedData.reserve(N); // 預先配置記憶體，避免重新配置
    for (int i = 0; i < N; i++) {
        sortedData.push_back(i * 2); // 0, 2, 4, 6...
    }

    // 2. 設定目標：找最後一個數字 (最壞情況)
    int target = sortedData.back(); // 1999998
    std::cout << "Target: " << target << "\n\n";

    // 3. 測試 Linear Search
    std::cout << "--- Linear Search ---\n";
    auto resultLin = linearSearch(sortedData, target);
    std::cout << "Found at index: " << resultLin.first << "\n";
    std::cout << "Steps taken   : " << resultLin.second << " (O(N))\n\n";

    // 4. 測試 Binary Search
    std::cout << "--- Binary Search ---\n";
    auto resultBin = binarySearch(sortedData, target);
    std::cout << "Found at index: " << resultBin.first << "\n";
    std::cout << "Steps taken   : " << resultBin.second << " (O(log N))\n";

    return 0;
}
