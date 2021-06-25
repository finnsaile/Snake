#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "dataPath.hpp"

class CCounter: public sf::Drawable
{
    public:
        CCounter(unsigned int, int, int, bool);
        void increaseScore(unsigned int);
        unsigned int getScore();
    private:
        unsigned int score;
        sf::Font scoreFont;
        sf::Text scoreText;
        sf::Color myGreen;
        sf::Color myBlack;
        sf::Color myRed;
        bool highscoreCounter;
        int posX;
        int posY;
        void setCounterAttributes();
        void setCounterPosition();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};