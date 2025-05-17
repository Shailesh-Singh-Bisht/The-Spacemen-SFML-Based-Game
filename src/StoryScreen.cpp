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
    };

    m_storyText.setFont(m_font);
    m_storyText.setCharacterSize(24);
    m_storyText.setFillColor(sf::Color::White);
    m_storyText.setStyle(sf::Text::Bold);
    m_storyText.setString(m_storyTexts[m_currentSlide]);
    m_storyText.setPosition(100, 200); // Adjust based on screen size

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
