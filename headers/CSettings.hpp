#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "dataPath.hpp"
#include "headerEnum.hpp"
#include "CSlider.hpp"

class CSettings : public sf::Drawable
{
    public:
        CSettings(bool);
        ~CSettings();
        WindowInstance settingsTick(sf::RenderWindow&);
        void setSettings();
        int getVolumeMusic();
        int getVolumeEat();
        int getVolumeClick();
        int getVolumeGameOver();
        Difficulty getDifficulty();
    private: 
        bool delBool;
        void initDifficultyEasy();
        void initDifficultyMedium();
        void initDifficultyHard();
        void initDifficultyExtreme();
        void initDifficultyImpossible();
        void initSliders();
        void initHeadline();
        void initMenu();
        int volumeMusic;
        int volumeEat;
        int volumeClick;
        int volumeGameOver;
        Difficulty difficulty;
        sf::SoundBuffer clickBuffer;
        sf::Sound clickSound;
        sf::Sprite difficultyEasySprite;
        sf::Sprite difficultyMediumSprite;
        sf::Sprite difficultyHardSprite;
        sf::Sprite difficultyExtremeSprite;
        sf::Sprite difficultyImpossibleSprite;
        sf::Sprite menuSprite;
        sf::Sprite difficultySprite;
        sf::Sprite volumeSprite;
        sf::Texture difficultyTexture;
        sf::Texture volumeTexture;
        sf::Texture difficultyEasyTexture;
        sf::Texture difficultyMediumTexture;
        sf::Texture difficultyHardTexture;
        sf::Texture difficultyExtremeTexture;
        sf::Texture difficultyImpossibleTexture;
        sf::Texture menuTexture;
        sf::FloatRect difficultyEasyBounds;
        sf::FloatRect difficultyMediumBounds;
        sf::FloatRect difficultyHardBounds;
        sf::FloatRect difficultyExtremeBounds;
        sf::FloatRect difficultyImpossibleBounds;
        sf::FloatRect menuBounds;
        CSlider* sliderMusic;
        CSlider* sliderEat;
        CSlider* sliderClick;
        CSlider* sliderGameOver;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};