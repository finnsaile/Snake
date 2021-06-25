#pragma once
#include <SFML/Graphics.hpp>
#include "CGameMenu.hpp"
#include "dataPath.hpp"
class CGameOverMenu : public CGameMenu
{
    public:
        CGameOverMenu(CGame*, std::string, std::string, std::string);
    private:
        sf::SoundBuffer gameOverSoundBuffer;
        sf::Sound gameOverSound;
};

