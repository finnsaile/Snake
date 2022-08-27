#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Snake.hpp"
#include "Grid.hpp"
#include "SettingsValues.hpp"
#include "Resources.hpp"

class Game : public sf::Drawable
{
    public:
        Game();
        ~Game();
        WindowInstance gameTick(sf::RenderWindow&);
    private:
        float m_difficulty_f;
   
        WindowInstance m_new_instance;
        SettingsValues& m_settings_values;
        Resources& m_resource;
        Grid m_grid;
        
        std::shared_ptr<Snake> m_snake;  

        Counter m_counter;
        Counter m_highscore;

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