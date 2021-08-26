#pragma once
#include <SFML/Graphics.hpp>
#include "CGameMenu.hpp"

class CBreakMenu : public CGameMenu
{
    public:
        CBreakMenu(CGame*, sf::Texture&, sf::Texture&, sf::Texture&);
};
