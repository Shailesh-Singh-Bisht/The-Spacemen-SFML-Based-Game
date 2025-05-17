#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>

class MenuScreen
{
public:
    MenuScreen();

    void handleInput(const sf::Event &event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow &window);

    bool isStartPressed() const; // Returns true if Space pressed to start

private:
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_instructionsText;

    sf::RectangleShape m_startButton;
    sf::Text m_startText;

    sf::RectangleShape m_exitButton;
    sf::Text m_exitText;

    bool m_startPressed;

    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    void loadResources();
};

#endif // MENUSCREEN_H
