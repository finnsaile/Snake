#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "headerEnum.hpp"
#include "dataPath.hpp"
#include "CSettings.hpp"

class CMenu : public sf::Drawable
{
    public:
        CMenu();
        WindowInstance menuTick(sf::RenderWindow&);
    private:
        void initLogo();
        void initPlay();
        void initQuit();
        void initSettings();
        CSettings settings;
        sf::Sprite logo;
        sf::Sprite play;
        sf::Sprite quit;
        sf::Sprite settingsSprite;
        sf::Texture logoTexture;
        sf::Texture playTexture;
        sf::Texture quitTexture;
        sf::Texture settingsTexture;
        sf::FloatRect playBound;
        sf::FloatRect quitBound;
        sf::FloatRect settingsBound;
        sf::SoundBuffer clickBuffer;
        sf::Sound clickSound;
        sf::Font menuFont;
        sf::Color myBlack; 
        sf::Color myGreen; 
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};