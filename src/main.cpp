#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  bool isRunning = 1;
  int frameCount = 0;

  std::cout << "[System] SoulKnightLite Engine Starting....\n";

  while(isRunning){
    frameCount++;
    std::cout << "[Render] Frame: " << frameCount << " rendering...\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (frameCount >= 5){
      isRunning = 0;
      std::cout << "[System] Shutting down Engine...\n";
    }
  }

  return 0;
}
