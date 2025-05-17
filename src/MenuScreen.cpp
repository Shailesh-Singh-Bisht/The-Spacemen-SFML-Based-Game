#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen()
    : m_startPressed(false)
{
    loadResources();
    if (!m_backgroundTexture.loadFromFile("assets/UI_Background/main_menu_bg.png"))
    {
        std::cout << "Failed to load menu background!\n";
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    m_titleText.setString("THE SPACEMEN");
    m_titleText.setCharacterSize(48);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setPosition(200, 100); // Adjust as needed

    m_startButton.setSize(sf::Vector2f(300, 60));
    m_startButton.setFillColor(sf::Color(70, 130, 180)); // Steel blue
    m_startButton.setPosition(250, 250);

    m_startText.setFont(m_font);
    m_startText.setString("Start Game");
    m_startText.setCharacterSize(24);
    m_startText.setFillColor(sf::Color::White);
    m_startText.setPosition(270, 260);

    m_exitButton.setSize(sf::Vector2f(300, 60));
    m_exitButton.setFillColor(sf::Color(139, 0, 0)); // Dark red
    m_exitButton.setPosition(250, 350);

    m_exitText.setFont(m_font);
    m_exitText.setString("Exit");
    m_exitText.setCharacterSize(24);
    m_exitText.setFillColor(sf::Color::White);
    m_exitText.setPosition(270, 360);
}

void MenuScreen::handleInput(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (m_startButton.getGlobalBounds().contains(mousePos))
        {
            m_startPressed = true;
        }
        else if (m_exitButton.getGlobalBounds().contains(mousePos))
        {
            std::exit(0); // Exit the game
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            m_startPressed = true;
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            std::exit(0);
        }
    }
}

void MenuScreen::update(sf::Time)
{
    // No dynamic updates for now
}

void MenuScreen::render(sf::RenderWindow &window)
{
    window.draw(m_backgroundSprite); 
    window.draw(m_titleText);
    window.draw(m_startButton);
    window.draw(m_startText);
    window.draw(m_exitButton);
    window.draw(m_exitText);
}

bool MenuScreen::isStartPressed() const
{
    return m_startPressed;
}

void MenuScreen::loadResources()
{
    if (!m_font.loadFromFile("assets/fonts/kenvector_future.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
    }
}
