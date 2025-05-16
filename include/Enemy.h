#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Laser.h"

class Enemy
{
public:
    // Constructor: initialize with texture, position, speed, and laser texture
     Enemy(const sf::Texture& texture, float x, float y, const sf::Texture& laserTexture);

    // Update enemy position and fire cooldown timer
    void update(float deltaTime);

    // Draw the enemy
    void draw(sf::RenderWindow &window) const;

    // Enemy fires a laser
    Laser fire();

    // Check if enemy can fire
    bool canFire() const;

    // Get bounds for collision
    sf::FloatRect getBounds() const;

    // Damage enemy, return true if enemy is destroyed
    bool takeDamage(int amount);

    // Check if enemy is still alive
    bool isAlive() const;

    // Check if off screen (below window)
    bool isOffScreen(float windowHeight) const;

    // Get enemy sprite (for drawing or collision)
    const sf::Sprite &getSprite() const;
    sf::Vector2f getLaserStartPosition() const;


private:
    sf::Sprite sprite_;
    float speed_;
    const sf::Texture *laserTexture_;

    int health_;
    bool alive_;

    float fireCooldown_;      // seconds between shots
    float timeSinceLastFire_; // time since last laser fired
};

#endif // ENEMY_H
