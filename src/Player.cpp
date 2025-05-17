#include "Player.h"
#include <iostream>

Player::Player()
    : m_speed(200.f), m_hp(100)
{
    loadTextures();
    m_sprite.setTexture(m_texture);  // Only one texture used
    m_sprite.setPosition(960.f, 980.f);  // Position at bottom center of 1920x1080 screen
}

void Player::loadTextures() {
    if (!m_texture.loadFromFile("assets/images/playerShip.png")) {
        std::cerr << "Failed to load player texture\n";
    }
}

void Player::handleInput(const sf::RenderWindow& window, std::vector<Laser>& lasers, AudioManager& audioManager){
    float moveDistance = m_speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (m_sprite.getPosition().x > 0)
            m_sprite.move(-moveDistance * (1.f / 60.f), 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width < window.getSize().x)
            m_sprite.move(moveDistance * (1.f / 60.f), 0.f);
    }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(lasers, audioManager);
    }
}

void Player::update(sf::Time deltaTime) {
    // No animation switching needed
}

void Player::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Player::shoot(std::vector<Laser>& lasers, AudioManager& audioManager) {
    if (m_shootCooldown.getElapsedTime() >= SHOOT_INTERVAL) {
        sf::Vector2f pos = m_sprite.getPosition();
        float xCenter = pos.x + m_sprite.getGlobalBounds().width / 2.f;

        lasers.emplace_back(LaserType::Player, sf::Vector2f(xCenter, pos.y));
        m_shootCooldown.restart();

        // Play shoot sound
        audioManager.playSound("laser_shoot");
    }
}

void Player::takeDamage(int amount) {
    m_hp -= amount;
    if (m_hp < 0)
        m_hp = 0;
}

void Player::heal(int amount) {
    m_hp += amount;
    if (m_hp > 100)
        m_hp = 100;
}

int Player::getHP() const {
    return m_hp;
}

sf::FloatRect Player::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void Player::reset() {
    m_hp = 100;
    m_sprite.setPosition(960.f, 980.f); // Position at bottom center of 1920x1080 screen
    m_shootCooldown.restart();
}

// Remove switchTexture method because no upgrades/animations
