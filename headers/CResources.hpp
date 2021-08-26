#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class CResources 
{
    public:
        static CResources& getInstance();

        std::string DATA_PATH;
        
        sf::Texture m_head_w;
        sf::Texture m_head_a;
        sf::Texture m_head_s;
        sf::Texture m_head_d;

        sf::Texture m_body_ws;
        sf::Texture m_body_ad;

        sf::Texture m_body_aw;
        sf::Texture m_body_dw;
        sf::Texture m_body_as;
        sf::Texture m_body_ds;

        sf::Texture m_tail_w;
        sf::Texture m_tail_a;
        sf::Texture m_tail_s;
        sf::Texture m_tail_d;

        sf::Texture m_grid_texture_light;
        sf::Texture m_grid_texture_dark;

        sf::Texture m_slider_bar_texture;
        sf::Texture m_slider_dot_texture;

        sf::Texture m_difficulty_texture;
        sf::Texture m_volume_texture;
        sf::Texture m_difficulty_easy_texture;
        sf::Texture m_difficulty_medium_texture;
        sf::Texture m_difficulty_hard_texture;
        sf::Texture m_difficulty_extreme_texture;
        sf::Texture m_difficulty_impossible_texture;
        sf::Texture m_menu_texture;

        sf::Texture m_slider_music_volume;
        sf::Texture m_slider_eat_volume;
        sf::Texture m_slider_lost_volume;
        sf::Texture m_slider_click_volume;

        sf::Texture m_logo_texture;
        sf::Texture m_play_texture;
        sf::Texture m_quit_texture;
        sf::Texture m_settings_texture;

        sf::Texture m_game_menu_break_menu;
        sf::Texture m_game_menu_resume;
        sf::Texture m_game_menu_menu;
        sf::Texture m_game_menu_game_over;
        sf::Texture m_game_menu_play_again;

        sf::Texture m_food_texture;
        
        sf::SoundBuffer m_click_buffer;
        sf::SoundBuffer m_crunch_buffer;
        sf::SoundBuffer m_game_over_buffer;
        sf::Music m_game_music; 

        sf::Font m_game_font;

    private:
        CResources();
        CResources(const CResources&) = delete;
        void operator=(const CResources&) = delete;
        static CResources m_instance;
};
