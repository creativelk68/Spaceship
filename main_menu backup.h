#pragma once

#include <SFML/Graphics.hpp>

#include <random>

#include <iostream>

#include "button.h"

namespace TankGame {

    class MainMenu : public sf::Drawable {
    public:
        struct BrightStar : public sf::Drawable {
            sf::Sprite sprite;
            float cycle_time;
            bool rev;

            void update(const float& dt) {
                if (cycle_time < .0f) rev = true;
                else if (cycle_time > 3.0f) rev = false;
                cycle_time += (rev) ? dt : -dt;
            }

            virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
                window.draw(this->sprite, states);
            }
        };

    private:
        sf::Sprite m_bg;
        std::vector<BrightStar> m_bright_stars;
        std::vector<Button> m_buttons;

        sf::RenderTexture* __m_ptr_rbg;

    public:

        MainMenu(const sf::Font& font, const sf::Texture& texture_star, const sf::Texture& texture_bright_star);

        inline ~MainMenu() { delete __m_ptr_rbg; }

        inline const sf::Sprite& get_bg() const { return m_bg; }

        inline const std::vector<BrightStar>& get_bright_stars() const { return m_bright_stars; }

        void poll_events(sf::RenderWindow& window, sf::Music* musics_ptr, uint32_t& game_stage);

        inline void update(const float& dt) {
            for (register uint32_t i = 0u; i < m_bright_stars.size(); i++) { m_bright_stars[i].update(dt); }
        }

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    };

} // namespace TankGame
