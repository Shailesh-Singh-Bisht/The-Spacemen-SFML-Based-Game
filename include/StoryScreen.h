#ifndef STORYSCREEN_H
#define STORYSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Class to display the Intro Story screens (black screen + centered text)
class StoryScreen {
public:
    StoryScreen(sf::RenderWindow& window);

    // Initialize fonts and story texts
    bool init();

    // Advance to next story screen on input
    void handleInput();

    // Update any animations or timers if needed
    void update(float deltaTime);

    // Draw current story screen text
    void render();

    // Check if story has finished (all screens shown)
    bool isFinished() const;

private:
    sf::RenderWindow& window_;

    sf::Font font_;
    std::vector<std::string> storyTexts_;  // Holds the 5 story lines
    int currentIndex_;

    sf::Text displayText_;
};

#endif // STORYSCREEN_H
