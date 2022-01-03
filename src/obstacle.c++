#include "../include/Spaceship/obstacle.hpp"

float              Spaceship::Obstacle::secs_until_spawn;
const sf::Texture* Spaceship::Obstacle::texture_ptr;

void Spaceship::Obstacle::init(const sf::Texture& texture) { secs_until_spawn = 3.0f; Obstacle::texture_ptr = &texture; }

Spaceship::Obstacle::Obstacle(const sf::Vector2f& position, const sf::Vector2f& velocity)
    : m_sprite(sf::Sprite(*Obstacle::texture_ptr)), m_vel(velocity) { m_sprite.setPosition(position); }

void Spaceship::Obstacle::update(const float& elapsed_time, std::vector<Obstacle>& obstacles) {
    secs_until_spawn -= elapsed_time;

    // Moving all
    for (register unsigned int i = 0; i < obstacles.size(); i++) {
        obstacles[i].m_sprite.move(obstacles[i].m_vel * elapsed_time);
    }

    // Spawning
    if (secs_until_spawn < .0f) {
        Obstacle::spawn(obstacles);
        secs_until_spawn = obstacles.size() * obstacles.size();
    }

    // Despawning
    for (register unsigned int i = obstacles.size() - 1; i < obstacles.size(); i--) {

        const sf::Vector2f& pos = obstacles[i].m_sprite.getPosition();
        if (pos.x < -100 ||
            pos.x > 1300 ||
            pos.y < -100 ||
            pos.y > 800)    {
                obstacles.erase(obstacles.begin() + i);
            }
    }
}

void Spaceship::Obstacle::spawn(std::vector<Obstacle>& obstacles) {
    sf::Vector2f spawn_pos;
    sf::Vector2f orbit_vel;

    if (rand() % 2) {
        spawn_pos.x = rand() % 1300 - 100;
        spawn_pos.y = (rand() % 2) ? 700  : -100;

        orbit_vel.x = 50.0f + ((spawn_pos.x < 0) ? 1.0f : -1.0f) * (rand() % 100);
        orbit_vel.y = 50.0f + ((spawn_pos.y < 0) ? 1.0f : -1.0f) * (rand() % 100);
    } else {
        spawn_pos.y = rand() % 800 - 100;
        spawn_pos.x = (rand() % 2) ? 1200 : -100;

        orbit_vel.x = 50.0f + ((spawn_pos.x < 0) ? 1.0f : -1.0f) * (rand() % 100);
        orbit_vel.y = 50.0f + ((spawn_pos.y < 0) ? 1.0f : -1.0f) * (rand() % 100);
    }

    obstacles.emplace_back(spawn_pos, orbit_vel);
}

void Spaceship::Obstacle::draw(sf::RenderWindow& window) const { window.draw(m_sprite); };