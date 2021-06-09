
#include <catch2/catch.hpp>

#define private public
#include <Drawables/Image.hpp>
#include <Audio/Sound.hpp>
#include <Audio/Music.hpp>
#include <TraceLog.hpp>
#include <iostream>


TEST_CASE("Cache test - New Load - Not lonely", "[Cache]")
{
    RAY::TraceLog::setLevel(RAY::TraceLog::Level::LOG_NONE);
    RAY::Image myImage("assets/icon.png", false);

    REQUIRE(RAY::Image::_imagesCache._cache.size() == 1);
    REQUIRE(RAY::Image::_imagesCache._cache.contains("assets/icon.png"));
    REQUIRE(RAY::Image::_imagesCache._cache["assets/icon.png"].size() == 1);
    REQUIRE(myImage._image.use_count() == 2);
    RAY::Image::_imagesCache._cache.clear();
}

TEST_CASE("Cache test - New Load - Lonely", "[Cache][segf]")
{
    RAY::TraceLog::setLevel(RAY::TraceLog::Level::LOG_NONE);
    RAY::Image myImage("assets/icon.png", false);

    REQUIRE(RAY::Image::_imagesCache._cache.size() == 1);
    REQUIRE(RAY::Image::_imagesCache._cache.contains("assets/icon.png"));
    REQUIRE(RAY::Image::_imagesCache._cache["assets/icon.png"].size() == 1);
    REQUIRE(myImage._image.use_count() == 2);
}

TEST_CASE("Cache test - Already loaded - Lonely", "[Cache]")
{
    RAY::Audio::Sound mySound("assets/sounds/crate_break.ogg", false);
    RAY::Audio::Sound mySound2("assets/sounds/crate_break.ogg", true);

    REQUIRE(RAY::Audio::Sound::_soundsCache._cache.size() == 1);
    REQUIRE(RAY::Audio::Sound::_soundsCache._cache.contains("assets/sounds/crate_break.ogg"));
    REQUIRE(RAY::Audio::Sound::_soundsCache._cache["assets/sounds/crate_break.ogg"].size() == 2);
    REQUIRE(mySound._sound.use_count() == 2);
    REQUIRE(mySound2._sound.use_count() == 2);
}

TEST_CASE("Cache test - Already loaded - Not lonely", "[Cache]")
{
    RAY::Audio::Music myMusic("assets/musics/music_result.ogg", false);
    RAY::Audio::Music myMusic2("assets/musics/music_result.ogg", false);

    REQUIRE(RAY::Audio::Music::_musicsCache._cache.size() == 1);
    REQUIRE(RAY::Audio::Music::_musicsCache._cache.contains("assets/musics/music_result.ogg"));
    REQUIRE(RAY::Audio::Music::_musicsCache._cache["assets/musics/music_result.ogg"].size() == 1);
    REQUIRE(myMusic._music.use_count() == 3);
    REQUIRE(myMusic2._music.use_count() == 3);
}