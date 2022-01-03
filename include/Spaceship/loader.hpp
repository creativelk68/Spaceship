#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

namespace Spaceship
{
    sf::Font load_font(const char* filepath);

    std::vector<sf::Texture> load_textures(const char* filepath);

    sf::Music* load_musics(const char* filepath);

    void set_window_icon(sf::RenderWindow&, const char*);
    
    const std::array<std::tuple<sf::RectangleShape, sf::Vector2f>, 4>& load_borders();

} // namespace Spaceship