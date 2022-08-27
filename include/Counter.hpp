#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Resources.hpp"

class Counter: public sf::Drawable
{
    public:
        Counter(unsigned int, int, int, bool);
        void increaseScore(unsigned int);
        unsigned int getScore();
    private:
        sf::Color m_black;
        sf::Color m_green;
        sf::Color m_red;

        unsigned int m_score;
        int m_pos_x;
        int m_pos_y;
        bool m_highscore_counter;

        Resources& m_resource;

        sf::Text m_score_text;

        void setCounterAttributes();
        void setCounterPosition();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};