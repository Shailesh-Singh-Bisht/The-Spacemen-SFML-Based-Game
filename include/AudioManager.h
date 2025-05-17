#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    // Load all sounds and music once at start
    bool loadAssets();

    // Play sound effect by name (e.g., "laser_shoot", "enemy_death")
    void playSound(const std::string& soundName);

    // Play background music, looped
    void playMusic();

    // Stop background music
    void stopMusic();

    // Mute/unmute all sounds
    void mute();
    void unmute();
    bool isMuted() const;

private:
    sf::Music m_backgroundMusic;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_soundBuffers;
    std::unordered_map<std::string, sf::Sound> m_sounds;

    bool m_isMuted;

    void createSound(const std::string& name, const sf::SoundBuffer& buffer);
};

#endif // AUDIOMANAGER_H
