#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "AudioManager.h"   // <-- added audio manager include
#include "MenuScreen.h"
#include "StoryScreen.h"

enum class GameState
{
    MainMenu,
    Story,
    Playing,
    WinText,
    LoseText
};

class Game
{
public:
    Game(sf::RenderWindow &window);

    void run(); // Main game loop

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void resetGame();
    void checkCollisions();
    void spawnEnemies(sf::Time deltaTime);
    void updateGameState();

    // State transitions
    void startStory();
    void startGame();
    void showWinText();
    void showLoseText();
    void restartGameAfterDelay(sf::Time deltaTime);

    sf::RenderWindow &m_window;
    GameState m_state;

    // Game entities
    Player m_player;
    std::vector<Enemy> m_enemies;
    std::vector<Laser> m_playerLasers;
    std::vector<Laser> m_enemyLasers;

    MenuScreen m_menuScreen;
    StoryScreen m_storyScreen;

    sf::Font m_font;
    sf::Text m_stateText;

    sf::Text m_killsText; // Text to display the number of enemies killed
    sf::Text m_healthText;

    // Gameplay tracking
    int m_enemiesKilled;
    sf::Clock m_spawnClock;
    sf::Clock m_stateTextClock;

    sf::Texture m_gameBackgroundTexture;
    sf::Sprite m_gameBackgroundSprite;

    AudioManager m_audioManager;   // <-- Added AudioManager instance here

    static constexpr int WIN_KILL_COUNT = 30;
    static constexpr float STATE_TEXT_DURATION = 5.0f; // seconds
};

#endif // GAME_H
