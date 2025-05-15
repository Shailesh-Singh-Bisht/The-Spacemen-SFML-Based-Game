#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Class to handle the Main Menu screen
class MenuScreen {
public:
    MenuScreen(sf::RenderWindow& window);

    // Initialize menu assets (background, fonts, text)
    bool init();

    // Handle user input for menu navigation
    void handleInput();

    // Update menu state (e.g., hover effects)
    void update(float deltaTime);

    // Draw menu elements to the window
    void render();

    // Check if "Start Game" was selected
    bool isStartSelected() const;

    // Check if "Exit Game" was selected
    bool isExitSelected() const;

private:
    sf::RenderWindow& window_;

    sf::Font font_;
    sf::Text titleText_;
    sf::Text startText_;
    sf::Text exitText_;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    // Track which menu option is currently selected (0 = start, 1 = exit)
    int selectedIndex_;

    // Helper to update the visual state of menu options
    void updateMenuVisuals();
};

#endif // MENUSCREEN_H
