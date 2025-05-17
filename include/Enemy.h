#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Laser;  // Forward declaration

class Enemy {
public:
    Enemy(const sf::Vector2f& position, const sf::Texture& texture);
    
    // Add move constructor
    Enemy(Enemy&& other) noexcept;
    
    // Add move assignment operator
    Enemy& operator=(Enemy&& other) noexcept;

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    void shoot(std::vector<Laser>& lasers);
    void takeDamage(int amount);

    int getHP() const;
    sf::FloatRect getBounds() const;

    bool isDestroyed() const;

private:
    sf::Sprite m_sprite;
    bool m_movingRight;  // direction flag
    float m_speed;
    int m_hp;
    sf::Clock m_shootCooldown;
    const sf::Time SHOOT_INTERVAL = sf::seconds(2);
};

#endif // ENEMY_H
