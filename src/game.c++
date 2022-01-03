#include "../include/Spaceship/main_menu.hpp"
#include "../include/Spaceship/game.hpp"
#include "../include/Spaceship/xwing.hpp"
#include "../include/Spaceship/obstacle.hpp"
#include "../include/Spaceship/explosion.hpp"

#include <array>
#include <cmath>

#include <fstream>
#include <string>


extern sf::VideoMode window_size;

// Functions

void Spaceship::run(const float& dt, unsigned int& game_stage, XWing& xwing, const sf::Font& font, unsigned int& space_pressed, sf::RenderWindow& window,
    sf::Music* music_ptr, MainMenu& menu, Bg& bg, std::vector<sf::RectangleShape>& bullets, std::vector<Obstacle>& obstacles, std::vector<Explosion>& explosions)
{

    switch (game_stage) {
    case 0: menu.poll_events(window, music_ptr, game_stage); menu.update(dt); window.clear(sf::Color(0, 0, 3));
            window.draw(menu); window.display(); return;
    case 1: main_game::poll_events(window, space_pressed);
            main_game::update(dt, xwing, space_pressed, bg, bullets, obstacles, explosions);
            main_game::draw(window, bg, xwing, bullets, obstacles, explosions); return;
    case 2: unfinished_menu::poll_events(window, game_stage); unfinished_menu::draw(window, bg, font, "Multiplayer is not available yet"); return;
    case 3: unfinished_menu::poll_events(window, game_stage); unfinished_menu::draw(window, bg, font, "Settings are not available yet"); return;
    default: throw std::invalid_argument("Invalid game stage:" + std::to_string(game_stage)); exit(1);
    }
}

// Main Game Functions

void Spaceship::main_game::poll_events(sf::RenderWindow& window, unsigned& space_pressed)
{
    for (sf::Event e; window.pollEvent(e);)
    {
        switch (e.type)
        {
            case sf::Event::Closed: window.close(); return;

            case sf::Event::Resized:
                window_size.width = e.size.width;
                window_size.height = e.size.height;
                window.setSize(sf::Vector2u(window_size.width, window_size.height)); break;
            
            case sf::Event::KeyPressed:  if (e.key.code == sf::Keyboard::Space && space_pressed == 0) space_pressed = 1; break;
            case sf::Event::KeyReleased: if (e.key.code == sf::Keyboard::Space)                       space_pressed = 0; break;
        
            default: break;
        }
    }
}

void Spaceship::main_game::update(const float& dt, XWing& xwing, unsigned int& space_pressed, Bg& bg,
    std::vector<sf::RectangleShape>& bullets, std::vector<Obstacle>& obstacles, std::vector<Explosion>& explosions)
{
    bg.update(dt);
    
    xwing.update(dt, space_pressed, bullets);

    for (register uint32_t i = explosions.size() - 1; i < explosions.size(); i--) if (explosions[i].update(dt)) explosions.erase(explosions.begin() + i);

    // Update Bullets
    for (register unsigned int i = bullets.size() - 1; i < bullets.size(); i--) {

        sf::RectangleShape& bullet = bullets[i];

        bullet.move(
            (float) std::sin(bullet.getRotation() / 180.0f * 3.141592654f) *  400 * dt,
            (float) std::cos(bullet.getRotation() / 180.0f * 3.141592654f) * -400 * dt
        );

        const sf::Vector2f& bullet_pos = bullet.getPosition();

        if (bullet_pos.x < -50  ||
            bullet_pos.x > 1250 ||
            bullet_pos.y < -50  ||
            bullet_pos.y > 750)     bullets.erase(bullets.begin() + i);
    }

    Spaceship::Obstacle::update(dt, obstacles);

    for (register uint32_t i = obstacles.size() - 1; i < obstacles.size(); i--) {
        if (xwing.is_colliding(obstacles[i])) {
            if (obstacles[i].get_position().x < xwing.get_position().x) { xwing.add_velocity(sf::Vector2f( 250.0f, .0f)); }
            if (obstacles[i].get_position().x > xwing.get_position().x) { xwing.add_velocity(sf::Vector2f(-250.0f, .0f)); }
            if (obstacles[i].get_position().y < xwing.get_position().y) { xwing.add_velocity(sf::Vector2f(.0f,  250.0f)); }
            if (obstacles[i].get_position().y > xwing.get_position().y) { xwing.add_velocity(sf::Vector2f(.0f, -250.0f)); }


            explosions.push_back(Explosion(obstacles[i].get_position()));
            obstacles.erase(obstacles.begin() + i);
        }
    }

    // Check bullet and Obstacle collision
    for (register unsigned int i = obstacles.size() - 1; i < obstacles.size(); i--) {
        for (register unsigned int j = bullets.size() - 1; j < bullets.size(); j--) {
            if (obstacles[i].is_colliding(bullets[j])) {
                explosions.push_back(Explosion(bullets[j].getPosition()));
                obstacles.erase(obstacles.begin() + i);
                bullets.erase(bullets.begin() + j);
            }
        }
    }
}

void Spaceship::main_game::draw(sf::RenderWindow& window, const Bg& bg, const XWing& xwing, const std::vector<sf::RectangleShape>& bullets,
    std::vector<Obstacle>& obstacles, const std::vector<Explosion>& explosions) {

    window.clear(sf::Color(0, 0, 3));

    window.draw(bg);

    for (register uint32_t i = 0; i < explosions.size(); i++) window.draw(explosions[i]);
    for (register unsigned int i = 0; i < bullets.size();   i++) window.draw(bullets[i]);
    for (register unsigned int i = 0; i < obstacles.size(); i++) obstacles[i].draw(window);

    window.draw(xwing);

    window.display();
}

void Spaceship::unfinished_menu::poll_events(sf::RenderWindow& window, unsigned int& game_stage) {
    sf::Event e;

    while (window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed: window.close(); return;
            case sf::Event::KeyPressed: if (e.key.code == sf::Keyboard::Escape) game_stage = 0; break;
            default: break;
        }
    }
}

void Spaceship::unfinished_menu::draw(sf::RenderWindow& window, const Spaceship::Bg& bg, const sf::Font& font, const char* str) {
    window.clear(sf::Color(0, 0, 3));

    window.draw(bg);

    sf::RectangleShape info(sf::Vector2f(500.0f, 100.0f));
    info.setOrigin(250.0f, 50.0f);

    info.setPosition(
        window.getSize().x / 2,
        window.getSize().y / 2
    );

    info.setOutlineThickness(8.0f);
    info.setOutlineColor(sf::Color::Red);
    info.setFillColor(sf::Color::Transparent);

    sf::Text info_text(str, font, 38u);
    info_text.setFillColor(sf::Color::Red);
    info_text.setPosition(
        info.getPosition().x - info_text.getLocalBounds().width  / 2,
        info.getPosition().y - info_text.getLocalBounds().height / 2
    );

    window.draw(info);
    window.draw(info_text);

    window.display();
}