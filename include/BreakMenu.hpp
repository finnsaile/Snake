#pragma once
#include <SFML/Graphics.hpp>
#include "GameMenu.hpp"

class BreakMenu : public GameMenu
{
    public:
        BreakMenu(Game*, sf::Texture&, sf::Texture&, sf::Texture&);
};
