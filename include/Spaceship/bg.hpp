#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <tuple>

namespace Spaceship
{
    class Bg : public sf::Drawable
    {
        float m_nxt_star_spawn;
        std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_small_star_positions, m_big_star_positions;

        const sf::Texture m_big_star_texture;

    public:

        Bg() = delete;

        Bg(const sf::Texture&);

        void update(const float& dt);

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
} // namespace Spaceship
