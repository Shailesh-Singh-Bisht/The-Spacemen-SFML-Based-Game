#ifndef STORYSCREEN_H
#define STORYSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class StoryScreen {
public:
    StoryScreen();

    void handleInput(const sf::Event& event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    bool isFinished() const;  // Returns true if story is done

private:
    std::vector<std::string> m_storyTexts;
    int m_currentSlide;

    sf::Font m_font;
    sf::Text m_storyText;

    sf::Clock m_slideTimer;
    const sf::Time SLIDE_DURATION = sf::seconds(5);

    void loadResources();
    void nextSlide();
};

#endif // STORYSCREEN_H
