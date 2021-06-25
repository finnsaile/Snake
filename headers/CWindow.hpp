#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CGame.hpp"
#include "CMenu.hpp"
#include "CBreakMenu.hpp"
#include "CGameOverMenu.hpp"
#include "CSettings.hpp"
#include "headerEnum.hpp"
#include "dataPath.hpp"


class CWindow : public sf::Drawable
{
    public:
        CWindow();
        void windowTick(sf::RenderWindow&);
        void changeInstance();
        void playClick();
    private:
        sf::Music gameMusic;
        WindowInstance windowInstance;
        WindowInstance newInstance;
        CGame* gameInstance;
        CMenu* menuInstance;
        CBreakMenu* breakMenuInstance;
        CGameOverMenu* gameOverMenuInstance;
        CSettings* settingsInstance;
        CSettings* settings;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};