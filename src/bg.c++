#include "../include/Spaceship/bg.hpp"

#include <random>

extern std::mt19937 randint;
extern sf::VideoMode window_size;

Spaceship::Bg::Bg(const sf::Texture& big_star_texture) : m_nxt_star_spawn(2.0f), m_big_star_texture(big_star_texture)
{

    m_nxt_star_spawn += static_cast<float>(randint() % 10) / 10;

    unsigned n = 1096u + randint() % 568u;

    m_small_star_positions.reserve(n);

    for (unsigned i = 0u; i < n; i++)
    {
        m_small_star_positions.emplace_back(std::make_pair
        (
            sf::Vector2f(randint() % window_size.width, randint() % window_size.height),
            sf::Vector2f(randint() % 10, randint() % 10)
        ));

        if (randint() % 2) { std::get<1>(m_small_star_positions[i]).x *= -1; }
        if (randint() % 2) { std::get<1>(m_small_star_positions[i]).y *= -1; }
    }


    n = 70 + randint() % 80;

    m_big_star_positions.reserve(n);

    for (unsigned i = 0u; i < n; i++)
    {
        m_big_star_positions.emplace_back(std::make_pair
        (
            sf::Vector2f(randint() % window_size.width, randint() % window_size.height),
            sf::Vector2f(randint() % 5, randint() % 5)
        ));
        
        if (randint() % 2) { std::get<1>(m_big_star_positions[i]).x *= -1; }
        if (randint() % 2) { std::get<1>(m_big_star_positions[i]).y *= -1; }
    }
}

void Spaceship::Bg::update(const float& dt){


    // Clean up stars out of image

    for (unsigned i = m_small_star_positions.size() - 1u; i > m_small_star_positions.size(); i--)
    {
        sf::Vector2f& star_position = std::get<0>(m_small_star_positions[i]);
        if (star_position.x < .0f
            || star_position.x > window_size.width
            || star_position.y < .0f
            || star_position.y > window_size.height) { m_small_star_positions.erase(m_small_star_positions.begin() + i); }
    }

    for (unsigned i = m_big_star_positions.size(); i < m_big_star_positions.size(); i--)
    {
        sf::Vector2f& star_position = std::get<0>(m_big_star_positions[i]);
        if (star_position.x < .0f
            || star_position.x > window_size.width
            || star_position.y < .0f
            || star_position.y > window_size.height) { m_big_star_positions.erase(m_big_star_positions.begin() + i); }
    }


    // Update spawn timer

    m_nxt_star_spawn -= dt;


    // Spawn new stars
    if (m_nxt_star_spawn < .0f)
    {
        m_nxt_star_spawn = 1.0f + static_cast<float>(randint() % 10) / 10.0f;

        // Amount of new spawned stars
        unsigned q = 1u + randint() % 3;

        for (unsigned i = 0u; i < q; i++)
        {
            if (randint() % 4)
            {
                m_small_star_positions.emplace_back(std::make_pair(
                    sf::Vector2f(window_size.width / 2.0f, window_size.height / 2.0f), sf::Vector2f(randint() % 5, randint() % 5)
                ));

                if (randint() % 2) { std::get<1>(m_small_star_positions[i]).x *= -1; }
                if (randint() % 2) { std::get<1>(m_small_star_positions[i]).y *= -1; }
            }
            else
            {
                m_big_star_positions.emplace_back(std::make_pair(
                    sf::Vector2f(window_size.width / 2.0f, window_size.height / 2.0f), sf::Vector2f(randint() % 5, randint() % 5)
                ));

                if (randint() % 2) { std::get<1>(m_big_star_positions[i]).x *= -1; }
                if (randint() % 2) { std::get<1>(m_big_star_positions[i]).y *= -1; }
            }
        }
    }


    // Move stars

    for (std::vector<std::pair<sf::Vector2f, sf::Vector2f>>::iterator it = m_small_star_positions.begin(); it != m_small_star_positions.end(); it++)
    {
        if (std::get<0>(*it).x < window_size.width / 2.0f) { std::get<0>(*it).x -= 10.0f * dt; }
        else if (std::get<0>(*it).x > window_size.width / 2.0f) { std::get<0>(*it).x += 10.0f * dt; }

        std::get<0>(*it).x += std::get<1>(*it).x;

        if (std::get<0>(*it).y < window_size.height / 2.0f) { std::get<0>(*it).y -= 10.0f * dt; }
        else if (std::get<0>(*it).y > window_size.height / 2.0f) { std::get<0>(*it).y += 10.0f * dt; }

        std::get<0>(*it).y += std::get<1>(*it).y;
    }

    for (std::vector<std::pair<sf::Vector2f, sf::Vector2f>>::iterator it = m_big_star_positions.begin(); it != m_big_star_positions.end(); it++)
    {
        if (std::get<0>(*it).x < window_size.width / 2.0f) { std::get<0>(*it).x -= 10.0f * dt; }
        else if (std::get<0>(*it).x > window_size.width / 2.0f) { std::get<0>(*it).x += 10.0f * dt; }

        std::get<0>(*it).x += std::get<1>(*it).x;

        if (std::get<0>(*it).y < window_size.height / 2.0f) { std::get<0>(*it).y -= 10.0f * dt; }
        else if (std::get<0>(*it).y > window_size.height / 2.0f) { std::get<0>(*it).y += 10.0f * dt; }

        std::get<0>(*it).y += std::get<1>(*it).y;
    }
}


// Draw stars

void Spaceship::Bg::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    std::vector<sf::Vertex> star_vertices;
    star_vertices.reserve(m_small_star_positions.size());

    for (std::vector<std::pair<sf::Vector2f, sf::Vector2f>>::const_iterator it = m_small_star_positions.cbegin(); it != m_small_star_positions.cend(); it++)
    {
        star_vertices.emplace_back(sf::Vector2f(std::get<0>(*it).x, std::get<0>(*it).y));
    }

    window.draw(star_vertices.data(), star_vertices.size(), sf::PrimitiveType::Points, states);


    for (std::vector<std::pair<sf::Vector2f, sf::Vector2f>>::const_iterator it = m_big_star_positions.cbegin(); it != m_big_star_positions.cend(); it++)
    {
        sf::Sprite sprite(m_big_star_texture);
        sprite.setPosition(std::get<0>(*it).x, std::get<0>(*it).y);
        window.draw(sprite, states);
    }
}
