#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

enum class LaserType {
    Player,
    Enemy
};

class Laser {
public:
    Laser(LaserType type, const sf::Vector2f& position);

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isOffScreen() const;

    int getDamage() const;

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture; // Consider making this static/shared if performance is a concern

    float m_speed;
    LaserType m_type;

    void loadTexture();
};

#endif // LASER_H
