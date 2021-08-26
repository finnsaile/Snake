#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "headerEnum.hpp"
#include "CSettings.hpp"
#include "CResources.hpp"

class CMenu : public sf::Drawable
{
    public:
        CMenu();
        WindowInstance menuTick(sf::RenderWindow&);
    private:
        sf::FloatRect initButton(sf::Sprite&, sf::Texture&, sf::Vector2f);
        void initTextures();

        CSettings m_settings;

        CResources& m_resource;

        sf::Sprite m_logo_sprite;
        sf::Sprite m_play_sprite;
        sf::Sprite m_quit_sprite;
        sf::Sprite m_settings_sprite;

        sf::FloatRect m_play_bound;
        sf::FloatRect m_quit_bound;
        sf::FloatRect m_settings_bound;

        sf::Sound m_click_sound;
        sf::Color m_my_black; 
        sf::Color m_my_green; 
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};