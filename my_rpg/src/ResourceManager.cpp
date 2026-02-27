#include "ResourceManager.hpp"
#include <iostream>

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    // 檢查貼圖是否已經在 map 中
    auto it = m_textures.find(filename);
    if (it != m_textures.end()) {
        return it->second;
    }

    // 如果不在，則載入它
    sf::Texture& texture = m_textures[filename];
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error: Could not load " << filename << std::endl;
    }
    return texture;
}
