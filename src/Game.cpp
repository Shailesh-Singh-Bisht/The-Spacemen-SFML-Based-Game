#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(sf::RenderWindow &window)
    : window_(window),
      player_(playerTexture_, 300.f, 100), // initialize player here, but texture not loaded yet
      gameState_(GameState::MENU),
      enemySpawnTimer_(0.f),
      enemySpawnInterval_(5.f),
      enemiesDestroyed_(0) {}

bool Game::init()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Load Textures
    if (!playerTexture_.loadFromFile("assets/images/playerShip.png") ||
        !enemyTexture_.loadFromFile("assets/images/enemyShip1.png") ||
        !playerLaserTexture_.loadFromFile("assets/images/playerLaser.png") ||
        !enemyLaserTexture_.loadFromFile("assets/images/enemyLaser.png") ||
        !backgroundTexture_.loadFromFile("assets/images/bgImage.png"))
    {
        std::cerr << "Failed to load textures." << std::endl;
        return false;
    }
    backgroundSprite_.setTexture(backgroundTexture_);

    // Now that textures are loaded, reinitialize player with valid texture
    player_ = Player(playerTexture_, 300.f, 100);

    // Load Sounds
    if (!laserSoundBuffer_.loadFromFile("assets/sounds/laser_shoot.wav") ||
        !hitSoundBuffer_.loadFromFile("assets/sounds/health_down.wav") ||
        !healSoundBuffer_.loadFromFile("assets/sounds/health_up.wav") ||
        !killNotificationBuffer_.loadFromFile("assets/sounds/count_up.mp3"))
    {
        std::cerr << "Failed to load sound effects." << std::endl;
        return false;
    }
    laserSound_.setBuffer(laserSoundBuffer_);
    hitSound_.setBuffer(hitSoundBuffer_);
    healSound_.setBuffer(healSoundBuffer_);
    killNotificationSound_.setBuffer(killNotificationBuffer_);

    // Load Music
    if (!backgroundMusic_.openFromFile("assets/music/bg_music.mp3"))
    {
        std::cerr << "Failed to load background music." << std::endl;
        return false;
    }
    backgroundMusic_.setLoop(true);
    backgroundMusic_.play();

    return true;
}

void Game::reset()
{
    player_.reset(); // call player's reset method to restore health/position
    enemies_.clear();
    playerLasers_.clear();
    enemyLasers_.clear();
    enemySpawnTimer_ = 0.f;
    enemySpawnInterval_ = 5.f;
    enemiesDestroyed_ = 0;
    gameState_ = GameState::PLAYING;
}

void Game::handleInput()
{
    if (gameState_ != GameState::PLAYING)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player_.canFire())
    {
        playerLasers_.push_back(player_.fire(playerLaserTexture_));
        playSound(laserSound_);
    }
}

void Game::update(float deltaTime) {
    if (gameState_ != GameState::PLAYING) return;

    player_.update(deltaTime, window_);
    spawnEnemies(deltaTime);
    updateEnemies(deltaTime);
    updateLasers(deltaTime);
    checkCollisions();
    cleanUpLasers();
    cleanUpEnemies();
    checkWinLoseConditions();
    updateUIText();
}


void Game::render()
{
    window_.clear();
    window_.draw(backgroundSprite_);

    if (gameState_ == GameState::PLAYING)
    {
        window_.draw(player_.getSprite());
        for (const auto &e : enemies_)
            window_.draw(e.getSprite());
        for (const auto &l : playerLasers_)
            l.draw(window_);
        for (const auto &l : enemyLasers_)
            l.draw(window_);

        window_.draw(healthText_);
        window_.draw(scoreText_);
    }

    window_.display();
}

void Game::spawnEnemies(float deltaTime) {
    enemySpawnTimer_ += 1.f / 60.f;
    if (enemySpawnTimer_ >= enemySpawnInterval_) {
        float xPos = static_cast<float>(rand() % (window_.getSize().x - 50) + 25);
        enemies_.emplace_back(enemyTexture_, xPos, 100.f, enemyLaserTexture_);
        enemySpawnTimer_ = 0.f;
    }
}


void Game::updateEnemies(float deltaTime)
{
    for (auto &enemy : enemies_)
    {
        enemy.update(deltaTime);
        if (enemy.canFire())
        {
            enemyLasers_.push_back(enemy.fire());
            playSound(laserSound_);
        }
    }
}

void Game::updateLasers(float deltaTime)
{
    for (auto &laser : playerLasers_)
        laser.update(deltaTime);
    for (auto &laser : enemyLasers_)
        laser.update(deltaTime);
}

void Game::checkCollisions()
{
    for (auto &laser : playerLasers_)
    {
        for (auto &enemy : enemies_)
        {
            if (laser.getBounds().intersects(enemy.getBounds()))
            {
                enemy.takeDamage(20);
                laser = playerLasers_.back();
                playerLasers_.pop_back();
                playSound(hitSound_);
                break;
            }
        }
    }

    for (auto &laser : enemyLasers_)
    {
        if (laser.getBounds().intersects(player_.getBounds()))
        {
            bool dead = player_.takeDamage(5);
            laser = enemyLasers_.back();
            enemyLasers_.pop_back();
            playSound(hitSound_);
            if (dead)
                break;
        }
    }

    for (auto it = enemies_.begin(); it != enemies_.end();)
    {
        if (!it->isAlive())
        {
            it = enemies_.erase(it);
            enemiesDestroyed_++;
            playSound(killNotificationSound_);
            if (enemiesDestroyed_ == 15)
                enemySpawnInterval_ = 3.f;
        }
        else
        {
            ++it;
        }
    }
}

void Game::cleanUpLasers()
{
    playerLasers_.erase(
        std::remove_if(playerLasers_.begin(), playerLasers_.end(),
                       [&](const Laser &l)
                       { return l.isOffScreen(window_.getSize().y); }),
        playerLasers_.end());

    enemyLasers_.erase(
        std::remove_if(enemyLasers_.begin(), enemyLasers_.end(),
                       [&](const Laser &l)
                       { return l.isOffScreen(window_.getSize().y); }),
        enemyLasers_.end());
}

void Game::cleanUpEnemies()
{
    enemies_.erase(
        std::remove_if(enemies_.begin(), enemies_.end(),
                       [&](const Enemy &e)
                       { return !e.isAlive(); }),
        enemies_.end());
}

void Game::playSound(const sf::Sound &sound)
{
    const_cast<sf::Sound &>(sound).play();
}

void Game::checkWinLoseConditions()
{
    if (!player_.isAlive())
    {
        gameState_ = GameState::GAME_OVER;
    }
    if (enemiesDestroyed_ >= winCondition_)
    {
        gameState_ = GameState::WIN;
    }
}

GameState Game::getGameState() const
{
    return gameState_;
}

void Game::setGameState(GameState state)
{
    gameState_ = state;
}

void Game::updateUIText()
{
    healthText_.setFont(font_);
    healthText_.setCharacterSize(20);
    healthText_.setColor(sf::Color::Green);
    healthText_.setPosition(10.f, 10.f);

    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(20);
    scoreText_.setColor(sf::Color::Yellow);
    scoreText_.setPosition(10.f, 40.f);

    // Set the dynamic text
    healthText_.setString("Health: " + std::to_string(player_.getHealth()));
    scoreText_.setString("Score: " + std::to_string(enemiesDestroyed_));
}
