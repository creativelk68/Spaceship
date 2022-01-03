#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Spaceship
{
    class Button : public sf::Drawable {
        sf::Text m_text;
        sf::RectangleShape m_shape;
        sf::Color m_color, m_color_hovered;
        void(*m_on_click)(sf::Music*, unsigned int&);
    public:

        Button() = delete;
        Button(const sf::Text&, const sf::RectangleShape&, void(*on_click)(sf::Music*, unsigned int&));

        void set_position(const sf::Vector2f&);
        void set_bg_color(const sf::Color&);
        void set_hovered_bg_color(const sf::Color&);
        void click(sf::Music*, unsigned int&);
        void update(const sf::RenderWindow& window);

        bool is_clicked(const sf::Vector2i&) const;

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };

} // namespace Spaceship