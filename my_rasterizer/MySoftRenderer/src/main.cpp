#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// 1. 設定解析度 (先設低一點，方便觀察軟體渲染的效能)
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// 輔助函式：用來設定某個座標的像素顏色
// 這就是我們對顯卡驅動做的最底層操作：寫入記憶體
void setPixel(std::vector<sf::Uint8>& pixels, int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

    // 核心公式：二維座標轉一維索引
    int index = (y * SCREEN_WIDTH + x) * 4;
    
    pixels[index] = r;     // Red
    pixels[index + 1] = g; // Green
    pixels[index + 2] = b; // Blue
    pixels[index + 3] = a; // Alpha (透明度)
}

int main() {
    // 建立視窗
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Day 1: Framebuffer");
    window.setFramerateLimit(60);

    // 2. 建立像素緩衝區 (Pixel Buffer)
    // 大小是 寬 * 高 * 4 (RGBA)
    std::vector<sf::Uint8> pixels(SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    // 3. 建立 SFML 的 Texture 與 Sprite 用來顯示我們的 Buffer
    sf::Texture texture;
    texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        // --- [渲染階段 Software Rendering] ---
        
        // 練習：畫一個漸層背景
        // 我們遍歷每一個像素，自己決定它的顏色
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                // 根據 x 和 y 的位置產生顏色 (這就是 Shader 的原理!)
                sf::Uint8 r = (x * 255) / SCREEN_WIDTH;  // x 越右邊越紅
                sf::Uint8 g = (y * 255) / SCREEN_HEIGHT; // y 越下面越綠
                sf::Uint8 b = 128;                       // 藍色固定
                
                setPixel(pixels, x, y, r, g, b, 255);
            }
        }

        // 練習：在中間畫一個白色方塊 (證明我們可以控制任意區域)
        for (int y = 200; y < 280; y++) {
            for (int x = 280; x < 360; x++) {
                setPixel(pixels, x, y, 255, 255, 255, 255);
            }
        }

        // 4. 將 CPU 的像素資料上傳給 GPU (這是最慢的一步)
        texture.update(pixels.data());

        // 5. 繪製
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
