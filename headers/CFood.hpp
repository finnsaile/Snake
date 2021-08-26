#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <fstream>
#include "CCounter.hpp"
#include "CNode.hpp"
#include "CSettings.hpp"
#include "CResources.hpp"

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
        int m_pos_x;
        int m_pos_y;

        CResources& m_resource;
        
        CSettings m_settings;

        CCounter m_counter;
        CCounter m_highscore;

        sf::Sprite m_food_sprite;
        sf::Sound m_crunch_sound;

        unsigned int m_highscore_easy;
        unsigned int m_highscore_medium;
        unsigned int m_highscore_hard;
        unsigned int m_highscore_extreme;
        unsigned int m_highscore_impossible;

        Difficulty m_difficulty;
        
        unsigned int initHighscore(Difficulty);
        void setRandCoordinates();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};