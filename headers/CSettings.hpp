#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "dataPath.hpp"
#include "headerEnum.hpp"
#include "CSlider.hpp"

class CSettings : public sf::Drawable
{
    public:
        CSettings(bool = false);
        virtual ~CSettings();
        WindowInstance settingsTick(sf::RenderWindow&);
        int getVolumeMusic() const;
        int getVolumeEat() const;
        int getVolumeClick() const;
        int getVolumeGameOver() const;
        Difficulty getDifficulty() const;
    private: 
        //functions to initialise sprites, buttons and sliders
        sf::FloatRect initButton(sf::Sprite&, sf::Texture&, sf::Vector2f);
        void loadFiles();
        void initSliders();
        void initTextures();

        //read and write settings from/to file
        void setSettings();
        void getSettings();

        //moves active slider
        void moveSlider(const sf::RenderWindow&);
        
        //bool to check if this is an active settings object
        bool m_active_settings_b;

        //variables used to store settings
        int m_volume_music;
        int m_volume_eat;
        int m_volume_click;
        int m_volume_game_over;
        Difficulty m_difficulty;

        //sound variables
        sf::SoundBuffer m_click_buffer;
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

        //textures for buttons and overall settings
        sf::Texture m_difficulty_texture;
        sf::Texture m_volume_texture;
        sf::Texture m_difficulty_easy_texture;
        sf::Texture m_difficulty_medium_texture;
        sf::Texture m_difficulty_hard_texture;
        sf::Texture m_difficulty_extreme_texture;
        sf::Texture m_difficulty_impossible_texture;
        sf::Texture m_menu_texture;

        //rectangles to save button bounds
        sf::FloatRect m_difficulty_easy_bounds;
        sf::FloatRect m_difficulty_medium_bounds;
        sf::FloatRect m_difficulty_hard_bounds;
        sf::FloatRect m_difficulty_extreme_bounds;
        sf::FloatRect m_difficulty_impossible_bounds;
        sf::FloatRect m_menu_bounds;

        //slider pointers
        std::shared_ptr<CSlider> m_active_slider = nullptr;
        std::shared_ptr<CSlider> m_slider_music;
        std::shared_ptr<CSlider> m_slider_eat;
        std::shared_ptr<CSlider> m_slider_click;
        std::shared_ptr<CSlider> m_slider_game_over;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};