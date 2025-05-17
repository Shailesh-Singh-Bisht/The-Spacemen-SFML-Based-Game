#include "Enemy.h"
#include "Laser.h"

Enemy::Enemy(const sf::Vector2f& position, const sf::Texture& texture)
    : m_speed(100.f), m_hp(100), m_movingRight(true)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
}

Enemy::Enemy(Enemy&& other) noexcept
    : m_sprite(std::move(other.m_sprite))
    , m_movingRight(other.m_movingRight)
    , m_speed(other.m_speed)
    , m_hp(other.m_hp)
    , m_shootCooldown(std::move(other.m_shootCooldown))
    , SHOOT_INTERVAL(other.SHOOT_INTERVAL)
{
}

Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        m_sprite = std::move(other.m_sprite);
        m_movingRight = other.m_movingRight;
        m_speed = other.m_speed;
        m_hp = other.m_hp;
        m_shootCooldown = std::move(other.m_shootCooldown);
    }
    return *this;
}

void Enemy::update(sf::Time deltaTime)
{
    float dx = m_speed * deltaTime.asSeconds();
    float dy = (m_speed * 0.5f) * deltaTime.asSeconds(); // Vertical movement at half speed

    // Move downward until reaching a certain height
    if (m_sprite.getPosition().y < 200.f) {
        m_sprite.move(0.f, dy);
    } else {
        // Once at proper height, move side to side
        if (m_movingRight) {
            m_sprite.move(dx, 0.f);
            if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width >= 1920) {
                m_movingRight = false;
            }
        } else {
            m_sprite.move(-dx, 0.f);
            if (m_sprite.getPosition().x <= 0) {
                m_movingRight = true;
            }
        }
    }
}

void Enemy::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Enemy::shoot(std::vector<Laser>& lasers)
{
    if (m_shootCooldown.getElapsedTime() >= SHOOT_INTERVAL) {
        sf::Vector2f laserPos(
            m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
            m_sprite.getPosition().y + m_sprite.getGlobalBounds().height
        );
        lasers.emplace_back(LaserType::Enemy, laserPos);
        m_shootCooldown.restart();
    }
}

void Enemy::takeDamage(int amount)
{
    m_hp -= amount;
}

int Enemy::getHP() const
{
    return m_hp;
}

sf::FloatRect Enemy::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

bool Enemy::isDestroyed() const
{
    return m_hp <= 0;
}
