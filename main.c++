#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <tuple>
#include <array>
#include <vector>
#include <random>

#include "include/Spaceship/main_menu.hpp"
#include "include/Spaceship/loader.hpp"
#include "include/Spaceship/game.hpp"
#include "include/Spaceship/xwing.hpp"
#include "include/Spaceship/obstacle.hpp"
#include "include/Spaceship/explosion.hpp"
#include "include/Spaceship/bg.hpp"

std::mt19937 randint(time(nullptr));
sf::VideoMode window_size(1200u, 700u);

int main()
{

    sf::RenderWindow window(window_size, "Tank", sf::Style::Close);
    Spaceship::set_window_icon(window, "../assets/ente.png");

    sf::Clock clock;
    unsigned game_stage = 0u; // 0 = main menu, 1 = main game, 2 = Multiplayer, 3 = Settings
    unsigned space_key_status = 0u;

    const sf::Font font                     = Spaceship::load_font("../assets/fonts/FreeSans.ttf");
    const std::vector<sf::Texture> textures = Spaceship::load_textures("../assets/textures/textures.txt");
    sf::Music* musics_ptr                   = Spaceship::load_musics("../assets/music/musics.txt");

    Spaceship::Bg bg(textures[6]);
    Spaceship::MainMenu menu = Spaceship::MainMenu(font, bg);

    Spaceship::Obstacle::init(textures[1]);
    Spaceship::Explosion::init(&textures[2], 3u);

    std::vector<Spaceship::Obstacle> obstacles;
    obstacles.reserve(3u);

    std::vector<sf::RectangleShape> bullets;
    bullets.reserve(8u);

    std::vector<Spaceship::Explosion> explosions;
    explosions.reserve(8u); 

    Spaceship::XWing xwing(sf::Vector2f(window_size.width / 2 - 50.0f, window_size.height / 2 - 50.0f), textures[0]);

    musics_ptr[0].play(); // play menu music

    while (window.isOpen()) {
        const float elapsed_time = clock.restart().asSeconds();

        Spaceship::run(elapsed_time, game_stage, xwing, font, space_key_status, window, musics_ptr, menu, bg, bullets, obstacles, explosions);
    }

    // Clean up
    delete[] musics_ptr;
}