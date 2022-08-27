#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "Game.hpp"
#include "SettingsValues.hpp"
#include "Resources.hpp"

class GameMenu : public sf::Drawable
{
    public:
        GameMenu(Game*, sf::Texture&, sf::Texture&, sf::Texture&, int = 430, int = 550, int = 500);
        virtual ~GameMenu();
        WindowInstance gameMenuTick(sf::RenderWindow&);
    protected:
        Resources& m_resource;
        SettingsValues& m_settings_values;
    private:
        sf::Sprite m_game_menu_sprite;
        sf::Sprite m_button_one_sprite;
        sf::Sprite m_button_two_sprite;;
        sf::FloatRect m_button_one_bound;
        sf::FloatRect m_button_two_bound;

        sf::Sound m_click_sound;
        Game* m_game_instance;

        sf::FloatRect initButton(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f pos);
        virtual WindowInstance buttonOneAction();
        virtual WindowInstance buttonTwoAction();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};   