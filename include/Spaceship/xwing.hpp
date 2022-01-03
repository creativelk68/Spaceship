#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <vector>

#include "obstacle.hpp"

namespace Spaceship {

    class XWing : public sf::Drawable {
        bool m_is_rotating_left;
        float m_drive_counter;
        sf::Vector2f m_vel;
        sf::Texture m_texture;
        sf::Sprite m_shape;
        bool m_bullet_is_left;

    public:

        XWing(const sf::Vector2f&, const sf::Texture&);
        
        void update(const float&, unsigned int&, std::vector<sf::RectangleShape>&);

        inline void add_velocity(const sf::Vector2f& vel) { m_vel += vel; }

        inline bool is_colliding(const Obstacle& obstacle) { return obstacle.is_colliding(m_shape); }

        inline const sf::Vector2f& get_position() const { return m_shape.getPosition(); }
        
        inline virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const { window.draw(m_shape, states); }

    };

} // namespace TankGame