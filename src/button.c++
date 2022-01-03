#include "../include/Spaceship/button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


Spaceship::Button::Button(const sf::Text& text, const sf::RectangleShape& shape, void(*on_click)(sf::Music*, unsigned&)) :
    m_text(text), m_shape(shape) { m_on_click = on_click; }


void Spaceship::Button::set_position(const sf::Vector2f& new_position) {
    m_shape.setPosition(new_position);
    
    const float new_x_txt = new_position.x + m_shape.getSize().x / 2 - m_text.getLocalBounds().width  / 2;
    const float new_y_txt = new_position.y + m_shape.getSize().y / 2 - m_text.getLocalBounds().height / 2;
    m_text.setPosition(sf::Vector2f(new_x_txt, new_y_txt));
}

void Spaceship::Button::set_bg_color(const sf::Color& color) {
    m_color = color;
}

void Spaceship::Button::set_hovered_bg_color(const sf::Color& color) {
    this->m_color_hovered = color;
}

void Spaceship::Button::click(sf::Music* music_ptrs, unsigned int& stage) {
    m_on_click(music_ptrs, stage);
}

bool Spaceship::Button::is_clicked(const sf::Vector2i& mouse_position) const {
    return 
        mouse_position.x >= this->m_shape.getPosition().x &&
        mouse_position.x <= this->m_shape.getPosition().x + this->m_shape.getLocalBounds().width &&
        mouse_position.y >= this->m_shape.getPosition().y &&
        mouse_position.y <= this->m_shape.getPosition().y + this->m_shape.getLocalBounds().height;
}

void Spaceship::Button::update(const sf::RenderWindow& window) {
    if (this->is_clicked(sf::Mouse::getPosition(window))) m_shape.setFillColor(m_color_hovered);
    else                                                  m_shape.setFillColor(m_color);    
}

void Spaceship::Button::draw(sf::RenderTarget& window, sf::RenderStates states) const {    
    window.draw(m_shape);
    window.draw(m_text);
}