#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "CResources.hpp"

class CCounter: public sf::Drawable
{
    public:
        CCounter(unsigned int, int, int, bool);
        void increaseScore(unsigned int);
        unsigned int getScore();
    private:
        unsigned int m_score;
        int m_pos_x;
        int m_pos_y;
        CResources& m_resource;

        sf::Text m_score_text;

        sf::Color m_green;
        sf::Color m_black;
        sf::Color m_red;

        bool m_highscore_counter;

        void setCounterAttributes();
        void setCounterPosition();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};