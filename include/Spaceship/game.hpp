#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <tuple>
#include <array>
#include <vector>

#include "obstacle.hpp"
#include "xwing.hpp"
#include "explosion.hpp"
#include "main_menu.hpp"

namespace Spaceship
{
    void run(const float& dt, unsigned& game_stage, XWing& communist_tank, const sf::Font& font, unsigned int& space_pressed, sf::RenderWindow& window,
    sf::Music* music_ptr, MainMenu& menu, Bg&, std::vector<sf::RectangleShape>& bullets, std::vector<Obstacle>& obstacles,
    std::vector<Explosion>& explosions);

    namespace main_game {

        void poll_events(sf::RenderWindow&, unsigned&);
        void update(const float&, XWing&, unsigned&, Bg&, std::vector<sf::RectangleShape>&, std::vector<Obstacle>&, std::vector<Explosion>&);
        void draw(sf::RenderWindow&, const Bg&, const XWing&, const std::vector<sf::RectangleShape>&, std::vector<Obstacle>&, const std::vector<Explosion>&);

    } // namespace main_game

    namespace unfinished_menu {

        void poll_events(sf::RenderWindow&, unsigned int&);
        void draw(sf::RenderWindow&, const Bg&, const sf::Font&, const char*);

    } // namespace multiplayer_menu

} // namespace TankGame