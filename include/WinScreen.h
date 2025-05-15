#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <SFML/Graphics.hpp>

// Class to display Win screen with message and options
class WinScreen {
public:
    WinScreen(sf::RenderWindow& window);

    // Initialize fonts, background, and texts
    bool init();

    // Handle user input (restart or exit)
    void handleInput();

    // Update animations or visual effects (if any)
    void update(float deltaTime);

    // Render the Win screen
    void render();

    // Check if user wants to restart
    bool isRestartSelected() const;

    // Check if user wants to exit
    bool isExitSelected() const;

private:
    sf::RenderWindow& window_;

    sf::Font font_;
    sf::Text winText_;
    sf::Text restartText_;
    sf::Text exitText_;
    sf::Text escapedText_;  // "You escaped the guards, rebel forces are very happy."

    int selectedIndex_; // 0 = restart, 1 = exit

    void updateMenuVisuals();
};

#endif // WINSCREEN_H
