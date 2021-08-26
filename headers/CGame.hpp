#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CSnake.hpp"
#include "CGrid.hpp"
#include "CSettings.hpp"

class CGame : public sf::Drawable
{
    public:
        CGame();
        ~CGame();
        WindowInstance gameTick(sf::RenderWindow&);
    private:
        CSnake m_snake;
        std::shared_ptr<CFood> m_food;
        CGrid m_grid;
        CSettings m_settings;

        sf::Clock m_clock;
        WindowInstance m_new_instance;
        float convertDifficulty(Difficulty);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};