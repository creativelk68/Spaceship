#include "../include/Spaceship/main_menu.hpp"

#include <SFML/Audio.hpp>

extern std::mt19937 randint;
extern sf::VideoMode window_size;

Spaceship::MainMenu::MainMenu(const sf::Font& font, Bg& bg) : m_bg(bg)
{
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


void Spaceship::MainMenu::poll_events(sf::RenderWindow& window, sf::Music* musics_ptr, uint32_t& game_stage) {
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


void Spaceship::MainMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_bg);

    for (register uint32_t i = 0u; i < m_buttons.size(); i++) { window.draw(m_buttons[i]); }
}
