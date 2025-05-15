#include "Laser.h"
#include <SFML/Graphics.hpp>

// Constructor: initialize laser with texture, position, speed, and ownership type
Laser::Laser(const sf::Texture& texture, sf::Vector2f position, float speed, bool isPlayerLaser)
    : speed_(speed), playerLaser_(isPlayerLaser)
{
    sprite_.setTexture(texture);
    sprite_.setPosition(position);

    // Center the laser origin for consistent movement and collisions
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Update the laser's position based on its speed
void Laser::update(float deltaTime) {
    sprite_.move(0.f, speed_ * deltaTime);
}

// Draw the laser to the render window
void Laser::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

// Check if laser is off the screen vertically
bool Laser::isOffScreen(float windowHeight) const {
    float y = sprite_.getPosition().y;
    return (y < 0.f || y > windowHeight);
}

// Get the bounding box of the laser (used for collision detection)
sf::FloatRect Laser::getBounds() const {
    return sprite_.getGlobalBounds();
}

// Return whether this laser belongs to the player
bool Laser::isPlayerLaser() const {
    return playerLaser_;
}
