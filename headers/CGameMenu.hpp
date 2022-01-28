#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "CGame.hpp"
#include "CSettingsValues.hpp"
#include "CResources.hpp"

class CGameMenu : public sf::Drawable
{
    public:
        CGameMenu(CGame*, sf::Texture&, sf::Texture&, sf::Texture&, int = 430, int = 550, int = 500);
        virtual ~CGameMenu();
        WindowInstance gameMenuTick(sf::RenderWindow&);
    protected:
        CResources& m_resource;
        CSettingsValues& m_settings_values;
    private:
        sf::Sprite m_game_menu_sprite;
        sf::Sprite m_button_one_sprite;
        sf::Sprite m_button_two_sprite;;
        sf::FloatRect m_button_one_bound;
        sf::FloatRect m_button_two_bound;

        sf::Sound m_click_sound;
        CGame* m_game_instance;

        sf::FloatRect initButton(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f pos);
        virtual WindowInstance buttonOneAction();
        virtual WindowInstance buttonTwoAction();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};   