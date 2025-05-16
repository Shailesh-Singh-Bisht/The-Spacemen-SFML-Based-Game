#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory> // for std::unique_ptr
#include "Player.h"
#include "Enemy.h"
#include "Laser.h"

// Enum for game states
enum class GameState
{
    MENU,
    STORY,
    PLAYING,
    GAME_OVER,
    WIN
};

// Main Game class controlling gameplay, updates, and rendering
class Game
{
public:
    Game(sf::RenderWindow &window);

    // Initialize game resources (textures, sounds, music)
    bool init();

    // Reset game state for a fresh start or restart
    void reset();

    // Main game loop update function (deltaTime for smooth updates)
    void update(float deltaTime);

    // Render all game elements to the window
    void render();

    // Handle player input (keyboard/mouse)
    void handleInput();

    // Get current game state
    GameState getGameState() const;

    // Set game state (used to switch screens, e.g., menu to play)
    void setGameState(GameState state);

private:
    sf::RenderWindow &window_;

    // Game entities
    Player player_; // dynamically constructed with texture, speed, health
    std::vector<Enemy> enemies_;
    std::vector<Laser> playerLasers_;
    std::vector<Laser> enemyLasers_;

    // Textures
    sf::Texture playerTexture_;
    sf::Texture enemyTexture_;
    sf::Texture playerLaserTexture_;
    sf::Texture enemyLaserTexture_;

    // Background and UI
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    // Font and Text
    sf::Font font_;
    sf::Text healthText_;
    sf::Text scoreText_;

    // Audio
    sf::Music backgroundMusic_;
    sf::SoundBuffer laserSoundBuffer_;
    sf::Sound laserSound_;
    sf::SoundBuffer hitSoundBuffer_;
    sf::Sound hitSound_;
    sf::SoundBuffer healSoundBuffer_;
    sf::Sound healSound_;
    sf::SoundBuffer killNotificationBuffer_;
    sf::Sound killNotificationSound_;

    // Game state and timers
    GameState gameState_;

    // Enemy spawning control
    float enemySpawnTimer_;
    float enemySpawnInterval_; // start at 5 seconds, decrease to 3 after 15 kills

    // Game stats
    int enemiesDestroyed_;
    const int winCondition_ = 30;

    // Private helper functions
    void spawnEnemies(float deltaTime);
    void updateEnemies(float deltaTime);
    void updateLasers(float deltaTime);
    void checkCollisions();
    void cleanUpLasers();
    void cleanUpEnemies();
    void playSound(const sf::Sound &sound);

    // Clamp player movement within window bounds
    void clampPlayerPosition();

    // Handle transition to game over or win states
    void checkWinLoseConditions();

    // Update health and score UI texts
    void updateUIText();
};

#endif // GAME_H
