#pragma once

#include <SFML/Graphics.hpp>

namespace Spaceship
{
    class Obstacle
    {
        static const sf::Texture* texture_ptr;
        static float secs_until_spawn;

        sf::Vector2f m_vel;
        sf::Sprite m_sprite;        

    public:

        static void init(const sf::Texture&);

        static void update(const float&, std::vector<Obstacle>&);

        static void spawn(std::vector<Obstacle>&);

        Obstacle(const sf::Vector2f&, const sf::Vector2f&);

        inline const sf::Vector2f& get_velocity() const { return m_vel; }

        inline bool is_colliding(const sf::RectangleShape& other) const { return m_sprite.getGlobalBounds().intersects(other.getGlobalBounds()); }
        inline bool is_colliding(const sf::Sprite& other)         const { return m_sprite.getGlobalBounds().intersects(other.getGlobalBounds()); }

        inline const sf::Vector2f& get_position() const { return m_sprite.getPosition(); }

        void draw(sf::RenderWindow&) const;
    };
    
} // namespace Spaceship