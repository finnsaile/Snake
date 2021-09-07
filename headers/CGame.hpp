#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CSnake.hpp"
#include "CGrid.hpp"
#include "CSettingsValues.hpp"
#include "CResources.hpp"

class CGame : public sf::Drawable
{
    public:
        CGame();
        ~CGame();
        WindowInstance gameTick(sf::RenderWindow&);
    private:
        float m_difficulty_f;
   
        WindowInstance m_new_instance;
        CSettingsValues& m_settings_values;
        CResources& m_resource;
        CGrid m_grid;
        
        std::shared_ptr<CSnake> m_snake;  

        CCounter m_counter;
        CCounter m_highscore;

        unsigned int m_highscore_easy;
        unsigned int m_highscore_medium;
        unsigned int m_highscore_hard;
        unsigned int m_highscore_extreme;
        unsigned int m_highscore_impossible;

        sf::Clock m_clock;
        
        unsigned int initHighscore(Difficulty);
        float convertDifficulty(Difficulty);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};