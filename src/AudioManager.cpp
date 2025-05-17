#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() : m_isMuted(false)
{
}

AudioManager::~AudioManager()
{
    stopMusic();
}

bool AudioManager::loadAssets()
{
    // Load sound buffers
    struct SoundFile
    {
        const char *name;
        const char *path;    };    SoundFile sounds[] = {
        {"laser_shoot", "assets/audio/laser_shoot.wav"},
        {"enemy_death", "assets/audio/death.wav"},
        {"kill_count", "assets/audio/count_up.ogg"},
        {"health_down", "assets/audio/health_down.wav"},
        {"health_up", "assets/audio/health_up.wav"},
        {"game_over", "assets/audio/gameOver.wav"},
        {"win", "assets/audio/win_game.wav"}};

    for (const auto &s : sounds)
    {
        auto buffer = std::make_shared<sf::SoundBuffer>();
        if (!buffer->loadFromFile(s.path))
        {
            std::cerr << "Failed to load sound: " << s.path << std::endl;
            return false;
        }
        else
        {
            std::cout << "Loaded sound: " << s.path << std::endl;
        }

        m_soundBuffers[s.name] = buffer;        sf::Sound sound;
        sound.setBuffer(*buffer); // use dereferenced shared_ptr
        sound.setVolume(50.f); // Set sound effects to 50% volume
        m_sounds[s.name] = sound;

        std::cout << "Sound loaded and stored: " << s.name << std::endl;
    }

    // Load background music
    if (!m_backgroundMusic.openFromFile("assets/music/bg_music.ogg"))
    {
        std::cerr << "Failed to load background music." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Loaded background music.\n";
    }    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.setVolume(100.f); // Set background music to 100% volume

    std::cout << "Final sound map contains:\n";
    for (auto &s : m_sounds)
        std::cout << "- " << s.first << std::endl;

    return true;
}

void AudioManager::createSound(const std::string &name, const sf::SoundBuffer &buffer)
{
    sf::Sound sound;
    sound.setBuffer(buffer);
    m_sounds[name] = sound;
}

void AudioManager::playSound(const std::string &soundName)
{
    if (m_isMuted)
        return;

    auto it = m_sounds.find(soundName);
    if (it != m_sounds.end())
    {
        it->second.play();
    }
    else
    {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void AudioManager::playMusic()
{
    if (m_isMuted)
        return;
    if (m_backgroundMusic.getStatus() != sf::Music::Playing)
        m_backgroundMusic.play();
}

void AudioManager::stopMusic()
{
    if (m_backgroundMusic.getStatus() == sf::Music::Playing)
        m_backgroundMusic.stop();
}

void AudioManager::mute()
{
    m_isMuted = true;
    m_backgroundMusic.pause();
    // Stop all currently playing sounds (optional)
    for (auto &pair : m_sounds)
    {
        pair.second.stop();
    }
}

void AudioManager::unmute()
{
    m_isMuted = false;
    m_backgroundMusic.play();
}

bool AudioManager::isMuted() const
{
    return m_isMuted;
}
