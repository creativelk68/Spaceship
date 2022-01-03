#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace Spaceship
{
    class Explosion : public sf::Drawable {
        float m_remaining_lifetime;
        sf::Vector2f m_pos;
        static std::vector<sf::Texture> textures;

    public:

        static inline void init(const sf::Texture* texture_ptr, const uint32_t& size) {
            textures.reserve(size);
            for (register uint32_t i = 0u; i < size; i++) { textures.push_back(*(texture_ptr + i)); }
        }

        Explosion(const sf::Vector2f& position=sf::Vector2f(), const float& lifetime=1.0f);

        bool update(const float&);

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    };

} // namespace Spaceship