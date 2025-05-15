#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Laser.h"

// Enemy class: Tuskabi guard ships pursuing player from the top
class Enemy {
public:
    // Constructor: initialize enemy with texture and starting position
    Enemy(const sf::Texture& texture, sf::Vector2f startPos);

    // Update enemy movement and shooting
    void update(float deltaTime);

    // Draw enemy sprite to window
    void draw(sf::RenderWindow& window) const;

    // Enemy fires lasers at intervals; returns true if a laser was fired
    bool canShoot() const;
    Laser shoot() const;

    // Health management
    int getHealth() const;
    void takeDamage(int amount);
    bool isAlive() const;

    // Get bounding box for collision checks and laser spawn
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    // Move enemy horizontally (left/right) within bounds
    void moveHorizontal(float delta);

private:
    sf::Sprite sprite_;
    int health_;
    const int maxHealth_ = 100;

    // Shooting cooldown
    float shootCooldown_;
    const float shootCooldownTime_ = 1.0f; // 1 second cooldown
    float shootTimer_;

    // Movement direction and speed
    float speed_;
    int direction_; // +1 for right, -1 for left
};

#endif // ENEMY_H
