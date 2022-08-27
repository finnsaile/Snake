#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "Menu.hpp"
#include "BreakMenu.hpp"
#include "GameOverMenu.hpp"
#include "Settings.hpp"
#include "SettingsValues.hpp"
#include "headerEnum.hpp"
#include "Resources.hpp"


class Window : public sf::Drawable
{
    public:
        Window();
        void windowTick(sf::RenderWindow&);
        void changeInstance();
        void playClick();
    private:
        Resources& m_resource;
        sf::Music m_game_music;
        WindowInstance m_window_instance = EMenu;
        WindowInstance m_new_instance = EMenu;
        Game* m_game_instance = nullptr;
        Menu* m_menu_instance = nullptr;
        BreakMenu* m_break_menu_instance = nullptr;
        GameOverMenu* m_game_over_menu_instance = nullptr;
        Settings* m_settings_instance = nullptr;
        SettingsValues& m_settings_values;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};