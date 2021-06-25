#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "CGame.hpp"
#include "dataPath.hpp"
#include "CSettings.hpp"

class CGameMenu : public sf::Drawable
{
    public:
        CGameMenu(CGame*, std::string, std::string, std::string, int = 430, int = 550, int = 500);
        virtual ~CGameMenu();
        WindowInstance gameMenuTick(sf::RenderWindow&);
        void initGameMenu(std::string, int);
        void initButton1(std::string, int);
        void initButton2(std::string, int);
        CSettings settings;
    private:
        sf::Sprite gameMenuSprite;
        sf::Sprite button1Sprite;
        sf::Sprite button2Sprite;
        sf::Texture button1Texture;
        sf::Texture gameMenuTexture;
        sf::Texture button2Texture;
        sf::FloatRect button1Bound;
        sf::FloatRect button2Bound;
        sf::SoundBuffer clickBuffer;
        sf::Sound clickSound;
        CGame* gameInstance;
        virtual WindowInstance button1Action();
        virtual WindowInstance button2Action();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};   