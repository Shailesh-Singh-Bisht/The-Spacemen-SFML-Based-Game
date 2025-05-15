#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Laser.h"

// Player class: controls the stolen ship at the bottom of the screen
class Player
{
public:
    // Constructor: initialize player with texture, speed, and max health
    Player(const sf::Texture& texture, float speed, int maxHealth);

    // Reset player to initial position, full health, and ready to fire
    void reset();

    // Update player state every frame (handle cooldowns, keep player in window bounds)
    void update(float deltaTime, const sf::RenderWindow& window);

    // Movement controls: move player horizontally within screen bounds
    // void moveLeft(float deltaTime);
    // void moveRight(float deltaTime);

    // Check if player can fire (cooldown elapsed)
    bool canFire() const;

    // Fire a laser: returns a Laser object spawned at player's position
    Laser fire(const sf::Texture& laserTexture);

    // Get player position and bounding box for collisions and laser spawn
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    // Access player's sprite for drawing
    const sf::Sprite& getSprite() const;

    // Health management
    bool takeDamage(int damage); // returns true if player died
    void heal(int amount);
    int getHealth() const;
    bool isAlive() const;

private:
    sf::Sprite sprite_;
    float speed_;

    int maxHealth_;
    int health_;
    bool isAlive_;

    // Shooting cooldown management
    float fireCooldown_;       // cooldown duration in seconds
    float timeSinceLastFire_;  // time elapsed since last shot fired
};

#endif // PLAYER_H
