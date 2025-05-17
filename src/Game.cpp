// Game.cpp
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(sf::RenderWindow &window)
    : m_window(window), m_state(GameState::MainMenu), m_player(), m_menuScreen(), m_storyScreen(), m_enemiesKilled(0)
{
  if (!m_font.loadFromFile("assets/fonts/kenvector_future.ttf"))
  {
    std::cout << "Failed to load font!\n";
  }
  if (!m_gameBackgroundTexture.loadFromFile("assets/images/bgImage.jpg"))
  {
    std::cout << "Failed to load game background!\n";
  }
  m_gameBackgroundSprite.setTexture(m_gameBackgroundTexture);
  if (!m_audioManager.loadAssets())
  {
    std::cout << "Failed to load audio assets!\n";
  }
  // Background music will be played when game starts
  m_stateText.setFont(m_font);
  m_stateText.setCharacterSize(72);
  m_stateText.setFillColor(sf::Color::Red);
  m_stateText.setStyle(sf::Text::Bold);
  m_stateText.setPosition(660, 500); // Centered for 1920x1080

  m_healthText.setFont(m_font);
  m_healthText.setCharacterSize(20);
  m_healthText.setFillColor(sf::Color::Green);
  m_healthText.setPosition(10.f, 10.f);

  m_killsText.setFont(m_font);
  m_killsText.setCharacterSize(20);
  m_killsText.setFillColor(sf::Color::Yellow);
  m_killsText.setPosition(10.f, 40.f);

  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::run()
{
  sf::Clock clock;
  while (m_window.isOpen())
  {
    sf::Time deltaTime = clock.restart();
    processEvents();
    update(deltaTime);
    render();
  }
}

void Game::processEvents()
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      m_window.close();

    if (m_state == GameState::MainMenu)
      m_menuScreen.handleInput(event);
    else if (m_state == GameState::Story)
      m_storyScreen.handleInput(event);
  }
}

void Game::update(sf::Time deltaTime)
{
  switch (m_state)
  {
  case GameState::MainMenu:
    m_menuScreen.update(deltaTime);
    if (m_menuScreen.isStartPressed())
      startStory();
    break;

  case GameState::Story:
    m_storyScreen.update(deltaTime);
    if (m_storyScreen.isFinished())
      startGame();
    break;

  case GameState::Playing:
    m_player.handleInput(m_window, m_playerLasers, m_audioManager);
    m_player.update(deltaTime);

    for (auto &enemy : m_enemies)
      enemy.update(deltaTime);

    // Update and cleanup off-screen lasers
    for (auto it = m_playerLasers.begin(); it != m_playerLasers.end();) {
      it->update(deltaTime);
      if (it->isOffScreen()) {
        it = m_playerLasers.erase(it);
      } else {
        ++it;
      }
    }

    for (auto it = m_enemyLasers.begin(); it != m_enemyLasers.end();) {
      it->update(deltaTime);
      if (it->isOffScreen()) {
        it = m_enemyLasers.erase(it);
      } else {
        ++it;
      }
    }

    checkCollisions();
    spawnEnemies(deltaTime);
    updateGameState();

    m_healthText.setString("Health: " + std::to_string(m_player.getHP()));
    m_killsText.setString("Kills: " + std::to_string(m_enemiesKilled));
    break;

  case GameState::WinText:
  case GameState::LoseText:
    restartGameAfterDelay(deltaTime);
    break;
  }
}

void Game::render()
{
  m_window.clear();

  switch (m_state)
  {
  case GameState::MainMenu:
    m_menuScreen.render(m_window);
    break;

  case GameState::Story:
    m_storyScreen.render(m_window);
    break;

  case GameState::Playing:
    m_window.draw(m_gameBackgroundSprite);
    m_player.render(m_window);
    for (auto &enemy : m_enemies)
      enemy.render(m_window);
    for (auto &laser : m_playerLasers)
      laser.render(m_window);
    for (auto &laser : m_enemyLasers)
      laser.render(m_window);

    m_window.draw(m_healthText);
    m_window.draw(m_killsText);
    break;

  case GameState::WinText:
  case GameState::LoseText:
    m_window.draw(m_gameBackgroundSprite);
    m_window.draw(m_healthText);
    m_window.draw(m_killsText);
    m_window.draw(m_stateText);
    break;
  }

  m_window.display();
}

void Game::startStory()
{
  m_state = GameState::Story;
}

void Game::startGame()
{
  resetGame();
  m_state = GameState::Playing;
  m_audioManager.playMusic(); // Start background music when game starts
}

void Game::resetGame()
{
  m_enemies.clear();
  m_playerLasers.clear();
  m_enemyLasers.clear();
  m_enemiesKilled = 0;
  m_spawnClock.restart();
  m_player.reset();
}

void Game::checkCollisions()
{
  for (auto it = m_playerLasers.begin(); it != m_playerLasers.end();)
  {
    bool hit = false;
    for (auto &enemy : m_enemies)
    {
      if (enemy.getBounds().intersects(it->getBounds()))
      {
        enemy.takeDamage(it->getDamage());
        m_audioManager.playSound("enemy_death");
        it = m_playerLasers.erase(it);
        hit = true;
        break;
      }
    }
    if (!hit)
      ++it;
  }

  for (auto it = m_enemyLasers.begin(); it != m_enemyLasers.end();)
  {
    if (m_player.getBounds().intersects(it->getBounds()))
    {
      m_player.takeDamage(it->getDamage());
      m_audioManager.playSound("health_down");
      it = m_enemyLasers.erase(it);
    }
    else
    {
      ++it;
    }
  }

  for (auto it = m_enemies.begin(); it != m_enemies.end();)
  {
    if (it->isDestroyed())
    {
      ++m_enemiesKilled;
      m_audioManager.playSound("enemy_death");
      it = m_enemies.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void Game::spawnEnemies(sf::Time deltaTime)
{
  static float spawnTimer = 0.0f;
  spawnTimer += deltaTime.asSeconds();
  
  // Spawn 2 ships every 15 seconds
  if (spawnTimer >= 15.0f)
  {
    static std::vector<sf::Texture> enemyTextures;
    static bool texturesLoaded = false;

    // Load textures only once
    if (!texturesLoaded) {
      std::vector<std::string> textureFiles = {
          "assets/images/enemyShip1.png",
          "assets/images/enemyShip2.png",
          "assets/images/enemyShip3.png"
      };
      
      for (const auto& file : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
          std::cout << "Failed to load enemy texture: " << file << "\n";
          return;
        }
        enemyTextures.push_back(texture);
      }
      texturesLoaded = true;
    }

    // Spawn 2 ships from above the screen
    for (int i = 0; i < 2; ++i) {
      int index = std::rand() % enemyTextures.size();
      // Spawn at random x position above the screen (-50 to ensure they're fully off-screen)
      sf::Vector2f position(rand() % 1720 + 100, -50); // Keep 100px margin from edges
      m_enemies.emplace_back(position, enemyTextures[index]);
    }
    spawnTimer = 0.0f; // Reset timer
  }

  for (auto &enemy : m_enemies)
  {
    enemy.shoot(m_enemyLasers);
  }
}

void Game::updateGameState()
{
  if (m_enemiesKilled >= WIN_KILL_COUNT)
  {
    m_state = GameState::WinText;
    m_stateText.setString("You Win! Restarting...");
    m_audioManager.stopMusic(); // Stop background music
    m_audioManager.playSound("win");
    m_stateTextClock.restart();
  }

  if (m_player.getHP() <= 0)
  {
    m_state = GameState::LoseText;
    m_stateText.setString("Game Over! Restarting...");
    m_audioManager.stopMusic(); // Stop background music
    m_audioManager.playSound("game_over");
    m_stateTextClock.restart();
  }
}

void Game::restartGameAfterDelay(sf::Time deltaTime)
{
  if (m_stateTextClock.getElapsedTime().asSeconds() > STATE_TEXT_DURATION)
  {
    startGame();
  }
}
