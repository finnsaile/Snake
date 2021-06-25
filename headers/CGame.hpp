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
        CSnake mysnake;
        CFood *food;
        CGrid grid;
        CSettings settings;
        sf::Clock clock;
        WindowInstance newInstance;
        float convertDifficulty(Difficulty);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};