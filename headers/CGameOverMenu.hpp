#pragma once
#include <SFML/Graphics.hpp>
#include "CGameMenu.hpp"
class CGameOverMenu : public CGameMenu
{
    public:
        CGameOverMenu(CGame*, sf::Texture&, sf::Texture&, sf::Texture&);
    private:
        sf::Sound m_game_over_sound;
};

