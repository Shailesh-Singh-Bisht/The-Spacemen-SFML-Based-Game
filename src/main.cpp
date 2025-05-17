// main.cpp
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <filesystem>
#include <iostream>

int main()
{
    // Create the main window with 1280x720 resolution
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Spacemen");

    // Set frame rate limit
    window.setFramerateLimit(60);

    // Create game instance
    Game game(window);

    // Run the main game loop
    game.run();

    return 0;
}
