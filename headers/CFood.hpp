#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <fstream>
#include "CCounter.hpp"
#include "CNode.hpp"
#include "dataPath.hpp"
#include "CSettings.hpp"

//food class to create food
class CFood : public sf::Drawable
{
    public:
        CFood(Difficulty);
        ~CFood();
        //gotEaten to relocate food
        void gotEaten(CNode*);
        //returnRect to get bounds of food
        sf::FloatRect returnRect();
    private:
        int posX;
        int posY;
        CCounter counter;
        CCounter highscore;
        CSettings settings;
        sf::Texture foodTexture;
        sf::Sprite foodSprite;
        sf::SoundBuffer crunchBuffer;
        sf::Sound crunch;
        sf::IntRect foodRect;
        unsigned int highscoreEasy;
        unsigned int highscoreMedium;
        unsigned int highscoreHard;
        unsigned int highscoreExtreme;
        unsigned int highscoreImpossible;
        Difficulty difficulty;
        unsigned int initHighscore(Difficulty);
        void setRandCoordinates();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};