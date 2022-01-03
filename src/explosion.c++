#include "../include/Spaceship/explosion.hpp"

#include <cmath>

std::vector<sf::Texture> Spaceship::Explosion::textures;

Spaceship::Explosion::Explosion(const sf::Vector2f& position, const float& lifetime) : m_remaining_lifetime(lifetime), m_pos(position) {}

bool Spaceship::Explosion::update(const float& delta) {
    m_remaining_lifetime -= delta;

    return m_remaining_lifetime <= .0f;
}

void Spaceship::Explosion::draw(sf::RenderTarget& window, sf::RenderStates render_states) const {

    const uint32_t texture_idx = (m_remaining_lifetime < .3f) ? 2u : ((m_remaining_lifetime < .6f) ? 1u : 0u);

    if (texture_idx > textures.size() - 1) return;

    sf::Sprite sprite(textures[texture_idx]);
    sprite.setOrigin(textures[texture_idx].getSize().x / 2u, textures[texture_idx].getSize().y / 2u);
    sprite.setPosition(m_pos);
    window.draw(sprite);
}