/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Sound
*/

#include "Audio/Sound.hpp"

RAY::Audio::Sound::Sound(const std::string &path):
	_sound(LoadSound(path.c_str()))
{

}

RAY::Audio::Sound::Sound()
{
}

RAY::Audio::Sound::~Sound()
{
	this->unload();
}

bool RAY::Audio::Sound::load(const std::string &path)
{
	_sound = LoadSound(path.c_str());
	return true;
}

bool RAY::Audio::Sound::unload(void)
{
	UnloadSound(_sound);
	return true;
}

bool RAY::Audio::Sound::isPlaying(void)
{
	return IsSoundPlaying(_sound);
}

RAY::Audio::Sound &RAY::Audio::Sound::play(void)
{
	PlaySound(_sound);
	return *this;
}

RAY::Audio::Sound &RAY::Audio::Sound::stop(void)
{
	StopSound(_sound);
	return *this;
}

RAY::Audio::Sound &RAY::Audio::Sound::pause(void)
{
	PauseSound(_sound);
	return *this;
}

RAY::Audio::Sound &RAY::Audio::Sound::resume(void)
{
	ResumeSound(_sound);
	return *this;
}

RAY::Audio::Sound &RAY::Audio::Sound::setVolume(float volume)
{
	SetSoundVolume(_sound, volume);
	return *this;
}

RAY::Audio::Sound &RAY::Audio::Sound::setPitch(float pitch)
{
	SetSoundPitch(_sound, pitch);
	return *this;
}
