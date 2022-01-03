#pragma once

#include <SFML/Graphics.hpp>

#include <random>

#include <iostream>

#include "button.hpp"
#include "bg.hpp"

namespace Spaceship
{

    class MainMenu : public sf::Drawable
    {
        Bg m_bg;
        std::vector<Button> m_buttons;

    public:

        MainMenu(const sf::Font& font, Bg&);

        void poll_events(sf::RenderWindow& window, sf::Music* musics_ptr, uint32_t& game_stage);

        inline void update(const float& dt) { m_bg.update(dt); }

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    };

} // namespace Spaceship
