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
    m_backgroundSprite.setTexture(m_backgroundTexture);    m_titleText.setString("THE SPACEMEN");
    m_titleText.setCharacterSize(72);  // Increased for 1080p
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setStyle(sf::Text::Bold);
    
    // Center the title
    sf::FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(titleBounds.left + titleBounds.width/2.0f, 
                         titleBounds.top + titleBounds.height/2.0f);
    m_titleText.setPosition(1920/2.0f, 200);  // Top center

    // Center the start button
    m_startButton.setSize(sf::Vector2f(400, 80));  // Larger for 1080p
    m_startButton.setFillColor(sf::Color(70, 130, 180)); // Steel blue
    m_startButton.setOrigin(200, 40);  // Half the button size
    m_startButton.setPosition(1920/2.0f, 500);  // Center of screen

    m_startText.setFont(m_font);
    m_startText.setString("Start Game");
    m_startText.setCharacterSize(36);  // Larger for 1080p
    m_startText.setFillColor(sf::Color::White);
    // Center the text in the button
    sf::FloatRect startTextBounds = m_startText.getLocalBounds();
    m_startText.setOrigin(startTextBounds.left + startTextBounds.width/2.0f,
                         startTextBounds.top + startTextBounds.height/2.0f);
    m_startText.setPosition(1920/2.0f, 500);    m_exitButton.setSize(sf::Vector2f(400, 80));  // Larger for 1080p
    m_exitButton.setFillColor(sf::Color(139, 0, 0)); // Dark red
    m_exitButton.setOrigin(200, 40);  // Half the button size
    m_exitButton.setPosition(1920/2.0f, 650);  // Below start button

    m_exitText.setFont(m_font);
    m_exitText.setString("Exit");
    m_exitText.setCharacterSize(36);  // Larger for 1080p
    m_exitText.setFillColor(sf::Color::White);
    // Center the text in the button
    sf::FloatRect exitTextBounds = m_exitText.getLocalBounds();
    m_exitText.setOrigin(exitTextBounds.left + exitTextBounds.width/2.0f,
                        exitTextBounds.top + exitTextBounds.height/2.0f);
    m_exitText.setPosition(1920/2.0f, 650);
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
