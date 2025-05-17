// Laser.cpp
#include <iostream>
#include "Laser.h"


#include <SFML/Graphics.hpp>

Laser::Laser(LaserType type, const sf::Vector2f& position)
    : m_type(type), m_speed(400.0f)  // speed in pixels per second
{
    loadTexture();
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);

    // Adjust origin to center horizontally, bottom or top vertically depending on type
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Laser::loadTexture() {
    // Load texture based on type; assuming files exist in assets/images/
    // For simplicity, one texture per laser type

    std::string path;
    if (m_type == LaserType::Player) {
        path = "assets/images/playerLaser.png";
    } else {
        path = "assets/images/enemyLaser.png";
    }

    if (!m_texture.loadFromFile(path)) {
        std::cout << "Error loading laser texture: " << path << std::endl;
    }
}

void Laser::update(sf::Time deltaTime) {
    float movement = m_speed * deltaTime.asSeconds();

    if (m_type == LaserType::Player) {
        // Move upward
        m_sprite.move(0, -movement);
    } else {
        // Move downward
        m_sprite.move(0, movement);
    }
}

void Laser::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::FloatRect Laser::getBounds() const {
    return m_sprite.getGlobalBounds();
}

bool Laser::isOffScreen() const {
    sf::Vector2f pos = m_sprite.getPosition();
    return (pos.y < 0 || pos.y > 1080); // Updated to match window height
}

int Laser::getDamage() const {
    // Player lasers deal 20 damage, enemy lasers deal 5 damage (example)
    return (m_type == LaserType::Player) ? 20 : 5;
}
