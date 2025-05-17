#include "StoryScreen.h"
#include <iostream>

StoryScreen::StoryScreen()
    : m_currentSlide(0)
{
    loadResources();

    // Sample story slides – you can replace with actual text or load from file later
    m_storyTexts = {
        "In a distant galaxy, tuskabi group took over the government of the galaxy. They were brutal and ruthless.",
        "The rebels emerged, an elite force, determined to fight back against the tyranny.",
        "One day, a plan of enemies weapons, were stolen by two rebels.",
        "The tuskabi group was furious and sent their best soldiers to hunt them down.",
        "The rebels escaped but not before the enemies ships arrive. They took a hyperjump but the enemies catch up to them.",
        "The two decided to fight, one took the wheels and the other one took the arms.",
        "Your task to defend the ship and destroy the enemies. Good Luck."
    };    m_storyText.setFont(m_font);
    m_storyText.setCharacterSize(22);  // Smaller size for better fit
    m_storyText.setFillColor(sf::Color::White);
    m_storyText.setStyle(sf::Text::Bold);
    m_storyText.setLineSpacing(1.5f);  // Add some space between lines

    // Word wrap the text to fit within 800 pixels width
    std::string currentText = m_storyTexts[m_currentSlide];
    std::string wrappedText;
    size_t lineStart = 0;
    size_t lastSpace = 0;
    size_t currentWidth = 0;
    const size_t MAX_WIDTH = 800;

    for (size_t i = 0; i < currentText.length(); ++i) {
        if (currentText[i] == ' ') {
            lastSpace = i;
        }
        currentWidth += 14; // Approximate width per character

        if (currentWidth >= MAX_WIDTH) {
            if (lastSpace > lineStart) {
                wrappedText += currentText.substr(lineStart, lastSpace - lineStart) + "\n";
                lineStart = lastSpace + 1;
                i = lastSpace;
            } else {
                wrappedText += currentText.substr(lineStart, i - lineStart) + "\n";
                lineStart = i;
            }
            currentWidth = 0;
        }
    }
    wrappedText += currentText.substr(lineStart);
    
    m_storyText.setString(wrappedText);
    
    // Center the text both horizontally and vertically
    sf::FloatRect textBounds = m_storyText.getLocalBounds();
    m_storyText.setOrigin(textBounds.left + textBounds.width/2.0f, 
                         textBounds.top + textBounds.height/2.0f);
    m_storyText.setPosition(1920/2.0f, 1080/2.0f);// Slightly above center

    m_slideTimer.restart();
}

void StoryScreen::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            nextSlide();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        nextSlide();
    }
}

void StoryScreen::update(sf::Time) {
    if (m_slideTimer.getElapsedTime() >= SLIDE_DURATION) {
        nextSlide();
    }
}

void StoryScreen::render(sf::RenderWindow& window) {
    // Clear any previous transformations
    m_storyText.setString(m_storyTexts[m_currentSlide]);
    
    // Get window size
    sf::Vector2u windowSize = window.getSize();
    
    // Calculate maximum width (60% of window width)
    float maxWidth = windowSize.x * 0.6f;
    
    // Split text into words
    std::string text = m_storyTexts[m_currentSlide];
    std::string word;
    std::string wrappedText;
    std::string currentLine;
    
    for(size_t i = 0; i < text.length(); ++i) {
        if(text[i] == ' ' || i == text.length() - 1) {
            if(i == text.length() - 1 && text[i] != ' ') {
                word += text[i];
            }
            
            // Test current line + new word
            std::string testLine = currentLine + (currentLine.empty() ? "" : " ") + word;
            m_storyText.setString(testLine);
            
            if(m_storyText.getGlobalBounds().width > maxWidth) {
                // Add current line to wrapped text and start new line
                wrappedText += currentLine + "\n";
                currentLine = word;
            } else {
                // Add word to current line
                currentLine = testLine;
            }
            word.clear();
        } else {
            word += text[i];
        }
    }
    
    // Add the last line
    wrappedText += currentLine;
    
    // Set the wrapped text
    m_storyText.setString(wrappedText);
    
    // Center the text
    sf::FloatRect bounds = m_storyText.getLocalBounds();
    m_storyText.setOrigin(bounds.width / 2, bounds.height / 2);
    m_storyText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    
    // Draw the text
    window.draw(m_storyText);
}

bool StoryScreen::isFinished() const {
    return m_currentSlide >= static_cast<int>(m_storyTexts.size());
}

void StoryScreen::loadResources() {
    if (!m_font.loadFromFile("assets/fonts/kenvector_future.ttf")) {
        std::cout << "Error loading story font!" << std::endl;
    }
}

void StoryScreen::nextSlide() {
    m_currentSlide++;
    if (m_currentSlide < static_cast<int>(m_storyTexts.size())) {
        m_storyText.setString(m_storyTexts[m_currentSlide]);
        m_slideTimer.restart();
    }
}
