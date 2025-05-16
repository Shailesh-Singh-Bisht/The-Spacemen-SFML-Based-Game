#include "Enemy.h"
#include <SFML/Graphics.hpp>

// Constructor: sets position, texture, and firing setup
Enemy::Enemy(const sf::Texture& texture, float x, float y, const sf::Texture& laserTexture)
    : laserTexture_(&laserTexture), sprite_(texture), speed_(300.f), health_(100), alive_(true),
      fireCooldown_(1.5f), timeSinceLastFire_(0.0f)
{
    sprite_.setPosition(x, y);

    // Center origin for better movement/collision
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Update position and fire timer
void Enemy::update(float deltaTime) {
    if (!alive_) return;

    sprite_.move(0.f, speed_ * deltaTime);
    timeSinceLastFire_ += deltaTime;
}

// Draw enemy to window
void Enemy::draw(sf::RenderWindow& window) const {
    if (alive_) {
        window.draw(sprite_);
    }
}

// Fire a laser if cooldown is over
Laser Enemy::fire() {
    sf::Vector2f laserPos = getLaserStartPosition();
    float laserSpeed = +300.f;

    return Laser(*laserTexture_, laserPos, laserSpeed, false);
}

sf::Vector2f Enemy::getLaserStartPosition() const {
    // Example: laser should start at the middle bottom of enemy sprite
    sf::FloatRect bounds = sprite_.getGlobalBounds();
    return sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height);
}


// Check if enough time passed to fire
bool Enemy::canFire() const {
    return timeSinceLastFire_ >= fireCooldown_;
}

// Get bounding box
sf::FloatRect Enemy::getBounds() const {
    return sprite_.getGlobalBounds();
}

// Damage enemy, return true if dead
bool Enemy::takeDamage(int amount) {
    if (!alive_) return false;

    health_ -= amount;
    if (health_ <= 0) {
        health_ = 0;
        alive_ = false;
        return true;
    }
    return false;
}

// Status check
bool Enemy::isAlive() const {
    return alive_;
}

// Off-screen check
bool Enemy::isOffScreen(float windowHeight) const {
    return sprite_.getPosition().y - sprite_.getGlobalBounds().height / 2.f > windowHeight;
}

// Accessor for sprite (if needed externally)
const sf::Sprite& Enemy::getSprite() const {
    return sprite_;
}
