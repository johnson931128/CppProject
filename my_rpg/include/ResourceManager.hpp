#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager() = default;

    // 取得貼圖，如果沒載入過就從檔案讀取
    sf::Texture& getTexture(const std::string& filename);

private:
    std::map<std::string, sf::Texture> m_textures;
};

#endif
