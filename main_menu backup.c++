#include "../include/TankGame/main_menu.h"

#include <SFML/Audio.hpp>

extern std::mt19937 randint;
extern sf::VideoMode window_size;

TankGame::MainMenu::MainMenu(const sf::Font& font, const sf::Texture& texture_star, const sf::Texture& texture_bright_star)
{
    const uint32_t n = 1096 + randint() % 568, m = 68 + randint() % 69;

    sf::Vertex* stars = new sf::Vertex[n];

    for (register uint32_t i = 0u; i < n; i++) {
        stars[i].position = sf::Vector2f(randint() % window_size.width, randint() % window_size.height);
        stars[i].color = sf::Color::White;
    }

    sf::RenderTexture* rbg = new sf::RenderTexture;
    rbg->create(window_size.width, window_size.height);
    rbg->clear(sf::Color(0, 0, 3));
    rbg->draw(stars, n, sf::PrimitiveType::Points);

    delete[] stars;

    if (texture_star.getSize().x == 0u || texture_star.getSize().y == 0u) {
        for (register uint32_t i = 0u; i < m; i++) {
            sf::CircleShape star(2);
            star.setPosition(randint() % window_size.width, randint() % window_size.height);
            rbg->draw(star);
        }
    } else {
        for (register uint32_t i = 0u; i < m; i++) {
            sf::Sprite star(texture_star);
            star.setPosition(randint() % window_size.width, randint() % window_size.height);
            rbg->draw(star);
        }
    }

    rbg->display();

    m_bg = sf::Sprite(rbg->getTexture());
    __m_ptr_rbg = rbg;

    const uint32_t o = 69 + randint() % 10;

    m_bright_stars.reserve(o);

    for (register uint32_t i = 0u; i < o; i++) {
        BrightStar star;
        star.cycle_time = static_cast<float>(randint() % 300) / 100.0f;
        star.rev = false;
        star.sprite = sf::Sprite(texture_bright_star);
        star.sprite.setPosition(randint() % window_size.width, randint() % window_size.height);
        m_bright_stars.push_back(star);
    }

    m_buttons.reserve(3u);

    // Singleplayer Button
    Button btn_singleplayer(sf::Text("Singleplayer", font, 45), sf::RectangleShape(sf::Vector2f(500.0f, 100.0f)), 
        [](sf::Music* musics, unsigned int& stage) {
            musics[stage].stop();
            stage = 1;
            musics[stage].play();
        }
    );

    btn_singleplayer.set_position(sf::Vector2f(window_size.width / 2 - 250.0f, window_size.height / 3 - 75.0f));
    btn_singleplayer.set_bg_color(sf::Color(0xDF, 0, 0));
    btn_singleplayer.set_hovered_bg_color(sf::Color::Red);
    m_buttons.push_back(btn_singleplayer);

    Button btn_multiplayer(sf::Text("Multiplayer", font, 45), sf::RectangleShape(sf::Vector2f(500.0f, 100.0f)),
        [](sf::Music* musics, unsigned int& stage) { stage = 2; }
    );

    btn_multiplayer.set_position(sf::Vector2f(window_size.width / 2 - 250.0f, window_size.height / 3 + 75.0f));
    btn_multiplayer.set_bg_color(sf::Color(0xDF, 0, 0));
    btn_multiplayer.set_hovered_bg_color(sf::Color::Red);
    m_buttons.push_back(btn_multiplayer);

    Button btn_settings(sf::Text("Settings", font, 45), sf::RectangleShape(sf::Vector2f(500.0f, 100.0f)),
        [](sf::Music* musics, unsigned int& stage) { stage = 3; }
    );

    btn_settings.set_position(sf::Vector2f(window_size.width / 2 - 250.0f, window_size.height / 3 + 225.0f));
    btn_settings.set_bg_color(sf::Color(0xDF, 0, 0));
    btn_settings.set_hovered_bg_color(sf::Color::Red);
    m_buttons.push_back(btn_settings);
}


void TankGame::MainMenu::poll_events(sf::RenderWindow& window, sf::Music* musics_ptr, uint32_t& game_stage) {
    for (sf::Event e; window.pollEvent(e);) {
        switch (e.type)
        {
            case sf::Event::Closed: window.close(); return;
            case sf::Event::Resized: window.setView(sf::View(sf::FloatRect(.0f, .0f, e.size.width, e.size.height))); break;

            case sf::Event::MouseButtonPressed:
               if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                   for (register unsigned int i = 0; i < m_buttons.size(); i++) {
                       if (m_buttons[i].is_clicked(sf::Mouse::getPosition(window))) m_buttons[i].click(musics_ptr, game_stage);
                   }
               } break;
        
            default: break;
        }
    }

    for (register uint32_t i = 0u; i < m_buttons.size(); i++) { m_buttons[i].update(window); }
}


void TankGame::MainMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const {

    window.draw(m_bg);

    for (register uint32_t i = 0u; i < m_bright_stars.size(); i++) {
        sf::Sprite cpy = m_bright_stars[i].sprite;
        cpy.setColor(sf::Color(255, 255, 255, std::abs(m_bright_stars[i].cycle_time) * 85.0f));
        window.draw(cpy);
    }

    for (register uint32_t i = 0u; i < m_buttons.size(); i++) { window.draw(m_buttons[i]); }
}
