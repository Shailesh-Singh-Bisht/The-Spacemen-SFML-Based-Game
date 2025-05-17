// main.cpp
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <filesystem>
#include <iostream>

int main()
{    // Create the main window with 1920x1080 resolution maximized
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Spacemen", sf::Style::Default);
    window.setPosition(sf::Vector2i(0, 0)); // Position at top-left
    
    // Set frame rate limit
    window.setFramerateLimit(60);

    // Create game instance
    Game game(window);

    // Run the main game loop
    game.run();

    return 0;
}
