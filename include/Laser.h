#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

// Laser class: projectiles fired by player and enemies
class Laser {
public:
    // Constructor: initialize laser with position, direction, speed, and texture
    Laser(const sf::Texture& texture, sf::Vector2f position, float speed, bool isPlayerLaser);

    // Update laser position based on speed and direction
    void update(float deltaTime);

    // Draw laser sprite to window
    void draw(sf::RenderWindow& window) const;

    // Check if laser is out of screen bounds (to be removed)
    bool isOffScreen(float windowHeight) const;

    // Get bounding box for collision detection
    sf::FloatRect getBounds() const;

    // Check laser owner type (player or enemy)
    bool isPlayerLaser() const;

private:
    sf::Sprite sprite_;
    float speed_;           // Positive speed means moving up for player lasers, down for enemy lasers
    bool playerLaser_;      // true if player fired this laser, false if enemy
};

#endif // LASER_H
