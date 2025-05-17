#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Laser.h"
#include "AudioManager.h"

class Player {
public:
    Player();

    void handleInput(const sf::RenderWindow& window, std::vector<Laser>& lasers, AudioManager& audioManager);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    void shoot(std::vector<Laser>& lasers, AudioManager& audioManager);
    void reset();


    void takeDamage(int amount);
    void heal(int amount);

    int getHP() const;
    sf::FloatRect getBounds() const;

private:
    sf::Texture m_texture;    // Single player texture
    sf::Sprite m_sprite;

    float m_speed;
    int m_hp;
    sf::Clock m_shootCooldown;
    const sf::Time SHOOT_INTERVAL = sf::milliseconds(300);

    void loadTextures();
};

#endif // PLAYER_H
