#include "../include/Spaceship/xwing.hpp"

#include <array>
#include <cmath>
#include <random>

extern std::mt19937 randint;

Spaceship::XWing::XWing(const sf::Vector2f& position, const sf::Texture& texture) 
: m_is_rotating_left(true), m_drive_counter(1.0f), m_vel(sf::Vector2f()), m_shape(sf::Sprite(m_texture)), m_texture(texture),
m_bullet_is_left(randint() % 2) {

    m_shape.setOrigin(sf::Vector2f(50.0f, 50.0f));
    m_shape.setPosition(position);
    m_shape.setRotation(45.0f);

    if (texture.getSize() == sf::Vector2u()) {
        sf::RenderTexture alt_texture;
        alt_texture.create(100u, 100u);

        const std::array<sf::Vertex, 3> vertices = {
            sf::Vertex(sf::Vector2f(50.0f, .0f), sf::Color::Green),
            sf::Vertex(sf::Vector2f(40.0f, 15.0f), sf::Color::Green),
            sf::Vertex(sf::Vector2f(60.0f, 15.0f), sf::Color::Green)
        };

        alt_texture.clear(sf::Color::Red);
        alt_texture.draw(&vertices[0], vertices.size(), sf::PrimitiveType::Triangles);
        alt_texture.display();

        m_texture = alt_texture.getTexture();

        return;
    } 
    
    m_shape.setTexture(m_texture);
}

void Spaceship::XWing::update(const float& dt, unsigned int& space_pressed, std::vector<sf::RectangleShape>& bullets) {

    if (space_pressed == 1) {
        m_drive_counter = 1.0f;
        m_is_rotating_left = (m_is_rotating_left) ? false : true;
        space_pressed = 2;

        sf::RectangleShape bullet(sf::Vector2f(6.0f, 24.0f));
        bullet.setFillColor(sf::Color::Red);

        const float sin = std::sin(m_shape.getRotation() / 180.0f * 3.141592f), cos = std::cos(m_shape.getRotation() / 180.0f * 3.141592f);

        bullet.setPosition(m_shape.getPosition() + sf::Vector2f(
            (sin == .0f) ? ((m_bullet_is_left) ? -47.0f : 44.99f) : (((m_bullet_is_left) ? -47.0f * sin : 44.99f * sin)),
            -50.0f * cos - 24.0f
        ));

        bullet.setRotation(m_shape.getRotation());
        bullets.push_back(bullet);

        if (m_bullet_is_left) { m_bullet_is_left = false; }
        else                  { m_bullet_is_left = true;  }

        m_vel += sf::Vector2f(
            (float) std::sin(m_shape.getRotation() / 180.0f * 3.1415926f) * -100,
            (float) std::cos(m_shape.getRotation() / 180.0f * 3.1415926f) *  100
        );
    } else if (space_pressed == 2) {
        if (m_drive_counter > .0f) m_drive_counter -= dt;
        else {
            m_vel += sf::Vector2f(
                (float) std::sin(m_shape.getRotation() / 180.0f * 3.141592f) *  10,
                (float) std::cos(m_shape.getRotation() / 180.0f * 3.141592f) * -10
            );
        }
    } else m_drive_counter = 1.0f;

    if (m_drive_counter == 1.0f) m_shape.rotate((m_is_rotating_left) ? -120 * dt : 120 * dt);

    // Speed limit
    m_vel.x = (m_vel.x > 400.0f) ? 400.0f : ((m_vel.x < -400.0f) ? -400.0f : m_vel.x);
    m_vel.y = (m_vel.y > 400.0f) ? 400.0f : ((m_vel.y < -400.0f) ? -400.0f : m_vel.y);
 
    // Rubbing (even though game is in space)
    const sf::Vector2<bool> vel_is_positive(m_vel.x > .0f, m_vel.y > .0f);
    m_vel += sf::Vector2f((vel_is_positive.x) ? -3.0f : 3.0f, (vel_is_positive.y) ? -3.0f : 3.0f);
    if ((vel_is_positive.x && m_vel.x < .0f) || vel_is_positive.x == false && m_vel.x > .0f) m_vel.x = .0f;
    if ((vel_is_positive.y && m_vel.y < .0f) || vel_is_positive.y == false && m_vel.y > .0f) m_vel.y = .0f;

    // Border collision
    const sf::Vector2f& position = m_shape.getPosition();
    constexpr uint32_t tank_size = 50u;

    if (position.x - tank_size < .0f) { m_vel.x -= position.x - tank_size; }
    else if (position.x + tank_size > 1200.0f) { m_vel.x -= position.x - tank_size; }

    if (position.y - tank_size < .0f) { m_vel.y -= position.y - tank_size; }
    else if (position.y + tank_size > 700.0f) { m_vel.y -= position.y - tank_size; }

    m_shape.move(m_vel * dt);
}
