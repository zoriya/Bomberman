/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Music
*/

#include "Audio/Music.hpp"

RAY::Audio::Music::Music(const std::string &path)
{
    this->load(path);
}

RAY::Audio::Music::Music()
{
}

RAY::Audio::Music::~Music()
{
    this->unload();
}

bool RAY::Audio::Music::load(const std::string &path)
{
    _music = LoadMusicStream(path.c_str());
    return true;
}

bool RAY::Audio::Music::unload(void)
{
    UnloadMusicStream(_music);
}

bool RAY::Audio::Music::isPlayin(void)
{
    return IsMusicPlaying(_music);
}

RAY::Audio::Music &RAY::Audio::Music::play(void)
{
    PlayMusicStream(_music);
    return *this;
}

RAY::Audio::Music &RAY::Audio::Music::stop(void)
{
    StopMusicStream(_music);
    return *this;
}

RAY::Audio::Music &RAY::Audio::Music::pause(void)
{
    PauseMusicStream(_music);
    return *this;
}

RAY::Audio::Music &RAY::Audio::Music::resume(void)
{
    ResumeMusicStream(_music);
    return *this;
}

RAY::Audio::Music &RAY::Audio::Music::setVolume(float volume)
{
    SetMusicVolume(_music, volume);
    return *this;
}

RAY::Audio::Music &RAY::Audio::Music::setPitch(float pitch)
{
    SetMusicPitch(_music, pitch);
    return *this;
}
