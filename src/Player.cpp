#include "Player.h"
#include "Laser.h" // Include Laser class for firing lasers
#include <SFML/Graphics.hpp>

// Constructor - initialize player properties
Player::Player(const sf::Texture& texture, float speed, int maxHealth)
    : speed_(speed), maxHealth_(maxHealth), health_(maxHealth), 
      isAlive_(true), fireCooldown_(0.3f), timeSinceLastFire_(0.0f)
{
    sprite_.setTexture(texture);
    // Position player near bottom center (x to be set by game)
    sprite_.setPosition(640.f, 650.f); // window width 1280, height 720

    // Set origin to center for smooth movement & rotation if needed
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Reset player to initial state
void Player::reset() {
    health_ = maxHealth_;
    isAlive_ = true;
    sprite_.setPosition(640.f, 650.f);
    timeSinceLastFire_ = 0.0f;
}

// Update player every frame
void Player::update(float deltaTime, const sf::RenderWindow& window) {
    if (!isAlive_)
        return;

    timeSinceLastFire_ += deltaTime;

    // Handle horizontal movement input (keyboard)
    float moveX = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveX -= speed_ * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveX += speed_ * deltaTime;
    }

    // Move player sprite horizontally, clamp to window bounds
    sf::Vector2f pos = sprite_.getPosition();
    pos.x += moveX;

    // Clamp position so player doesn't go off screen (consider sprite width)
    sf::FloatRect bounds = sprite_.getLocalBounds();
    float halfWidth = bounds.width / 2.f;

    if (pos.x - halfWidth < 0.f)
        pos.x = halfWidth;
    else if (pos.x + halfWidth > window.getSize().x)
        pos.x = window.getSize().x - halfWidth;

    sprite_.setPosition(pos);
}

// Check if player can fire based on cooldown
bool Player::canFire() const {
    return timeSinceLastFire_ >= fireCooldown_;
}

// Called when player fires a laser, resets cooldown timer
Laser Player::fire(const sf::Texture& laserTexture) {
    timeSinceLastFire_ = 0.0f;

    // Spawn laser slightly above the player's position
    sf::Vector2f pos = sprite_.getPosition();
    pos.y -= sprite_.getGlobalBounds().height / 2.f;

    return Laser(laserTexture, pos, -600.f,true);  // upward speed, adjust as needed
}

// Get current player position (for laser spawning)
sf::Vector2f Player::getPosition() const {
    return sprite_.getPosition();
}

// Get sprite reference for rendering
const sf::Sprite& Player::getSprite() const {
    return sprite_;
}

// Damage player by amount, return true if player died
bool Player::takeDamage(int damage) {
    if (!isAlive_)
        return false;

    health_ -= damage;
    if (health_ <= 0) {
        health_ = 0;
        isAlive_ = false;
        return true; // player died
    }
    return false;
}

// Heal player by amount, clamp to maxHealth
void Player::heal(int amount) {
    if (!isAlive_)
        return;

    health_ += amount;
    if (health_ > maxHealth_)
        health_ = maxHealth_;
}

// Get current health
int Player::getHealth() const {
    return health_;
}

// Check if player is alive
bool Player::isAlive() const {
    return isAlive_;
}

sf::FloatRect Player::getBounds() const {
    return sprite_.getGlobalBounds();
}
