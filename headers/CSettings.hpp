#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "headerEnum.hpp"
#include "CSlider.hpp"
#include "CResources.hpp"
#include "CSettingsValues.hpp"

class CSettings : public sf::Drawable
{
    public:
        CSettings();
        virtual ~CSettings();
        WindowInstance settingsTick(sf::RenderWindow&);
    private: 
        //functions to initialise sprites, buttons and sliders
        sf::FloatRect initButton(sf::Sprite&, sf::Texture&, sf::Vector2f);
        void initSliders();
        void initTextures();
        void initValues();
    
        //moves active slider
        void moveSlider(const sf::RenderWindow&);
    
        //variables used to store settings
        int* m_volume_music;
        int* m_volume_eat;
        int* m_volume_click;
        int* m_volume_game_over;
        int* m_length;
        int* m_food_count;
        bool* m_wall_crash_b;
        bool* m_self_crash_b;
        Difficulty* m_difficulty;

        CResources& m_resource;
        CSettingsValues& m_settings_values;
        //sound variables
        // sf::SoundBuffer m_click_buffer;
        sf::Sound m_click_sound;

        //sprites for settings and buttons
        sf::Sprite m_difficulty_easy_sprite;
        sf::Sprite m_difficulty_medium_sprite;
        sf::Sprite m_difficulty_hard_sprite;
        sf::Sprite m_difficulty_extreme_sprite;
        sf::Sprite m_difficulty_impossible_sprite;
        sf::Sprite m_menu_sprite;
        sf::Sprite m_difficulty_sprite;
        sf::Sprite m_volume_sprite;

        //rectangles to save button bounds
        sf::FloatRect m_menu_bounds;

        std::string m_difficulty_string_arr[5] = {"Easy", "Medium", "Hard", "Extreme", "Impossible"};
        std::string m_on_off_string_arr[2] = {"Off", "On"};

        //slider shared pointers
        std::shared_ptr<CSlider<int>> m_active_slider_int = nullptr;
        std::shared_ptr<CSlider<bool>> m_active_slider_bool = nullptr;
        std::shared_ptr<CSlider<Difficulty>> m_active_slider_diff = nullptr;
        std::shared_ptr<CSlider<int>> m_slider_music;
        std::shared_ptr<CSlider<int>> m_slider_eat;
        std::shared_ptr<CSlider<int>> m_slider_click;
        std::shared_ptr<CSlider<int>> m_slider_game_over;
        std::shared_ptr<CSlider<int>> m_slider_length;
        std::shared_ptr<CSlider<int>> m_slider_food_count;
        std::shared_ptr<CSlider<bool>> m_slider_wall_crash;
        std::shared_ptr<CSlider<bool>> m_slider_self_crash;
        std::shared_ptr<CSlider<Difficulty>> m_slider_difficulty;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};