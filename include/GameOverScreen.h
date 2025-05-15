#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>

// Class to display Game Over screen with message and options
class GameOverScreen {
public:
    GameOverScreen(sf::RenderWindow& window);

    // Initialize fonts, background, and texts
    bool init();

    // Handle user input (restart or exit)
    void handleInput();

    // Update animations or visual effects (if any)
    void update(float deltaTime);

    // Render the Game Over screen
    void render();

    // Check if user wants to restart
    bool isRestartSelected() const;

    // Check if user wants to exit
    bool isExitSelected() const;

private:
    sf::RenderWindow& window_;

    sf::Font font_;
    sf::Text gameOverText_;
    sf::Text restartText_;
    sf::Text exitText_;
    sf::Text capturedText_;  // "You are captured and killed by the guards."

    int selectedIndex_; // 0 = restart, 1 = exit

    void updateMenuVisuals();
};

#endif // GAMEOVERSCREEN_H
