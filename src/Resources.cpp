#include "Resources.hpp"
#include <iostream>


Resources Resources::m_instance;

Resources::Resources() :
/*
!!!CHANGE DATA_PATH to absolute file path of resource folder or run programm from main Snake folder!!!
*/
DATA_PATH("resources/")
{
    //snake head tectures
    m_head_w.loadFromFile(DATA_PATH + "Snake/SnakeHeadW.png");
    m_head_a.loadFromFile(DATA_PATH + "Snake/SnakeHeadA.png");
    m_head_s.loadFromFile(DATA_PATH + "Snake/SnakeHeadS.png");
    m_head_d.loadFromFile(DATA_PATH + "Snake/SnakeHeadD.png");

    //snake body textures
    m_body_ws.loadFromFile(DATA_PATH + "Snake/SnakeBodyWS.png");
    m_body_ad.loadFromFile(DATA_PATH + "Snake/SnakeBodyAD.png");
    m_body_aw.loadFromFile(DATA_PATH + "Snake/SnakeBodyAW.png");
    m_body_dw.loadFromFile(DATA_PATH + "Snake/SnakeBodyDW.png");
    m_body_as.loadFromFile(DATA_PATH + "Snake/SnakeBodyAS.png");
    m_body_ds.loadFromFile(DATA_PATH + "Snake/SnakeBodyDS.png");

    //snake tail textures
    m_tail_w.loadFromFile(DATA_PATH + "Snake/SnakeTailW.png");
    m_tail_a.loadFromFile(DATA_PATH + "Snake/SnakeTailA.png");
    m_tail_s.loadFromFile(DATA_PATH + "Snake/SnakeTailS.png");
    m_tail_d.loadFromFile(DATA_PATH + "Snake/SnakeTailD.png");

    //grid textures
    m_grid_texture_light.loadFromFile(DATA_PATH + "Floor/GrassLight.png");
    m_grid_texture_dark.loadFromFile(DATA_PATH + "Floor/GrassDark.png");

    //slider textures
    m_slider_bar_texture.loadFromFile(DATA_PATH + "Slider/SliderBar.png");
    m_slider_dot_texture.loadFromFile(DATA_PATH + "Slider/SliderDot.png");

    //settings textures
    m_difficulty_texture.loadFromFile(DATA_PATH + "Settings/Difficulty.png");
    m_volume_texture.loadFromFile(DATA_PATH + "Settings/Volume.png");
    m_menu_texture.loadFromFile(DATA_PATH + "Settings/Menu.png");

    //slider name textures
    m_slider_music_volume.loadFromFile(DATA_PATH + "Slider/MusicVolume.png");
    m_slider_eat_volume.loadFromFile(DATA_PATH + "Slider/EatVolume.png");
    m_slider_lost_volume.loadFromFile(DATA_PATH + "Slider/LostVolume.png");
    m_slider_click_volume.loadFromFile(DATA_PATH + "Slider/ClickVolume.png");
    m_slider_length.loadFromFile(DATA_PATH + "Slider/LengthSlider.png");
    m_difficulty_texture_array[0].loadFromFile(DATA_PATH + "Slider/EasySlider.png");
    m_difficulty_texture_array[1].loadFromFile(DATA_PATH + "Slider/MediumSlider.png");
    m_difficulty_texture_array[2].loadFromFile(DATA_PATH + "Slider/HardSlider.png");
    m_difficulty_texture_array[3].loadFromFile(DATA_PATH + "Slider/ExtremeSlider.png");
    m_difficulty_texture_array[4].loadFromFile(DATA_PATH + "Slider/ImpossibleSlider.png");

    //main menu textures
    m_logo_texture.loadFromFile(DATA_PATH + "Menu/SnakeLogo.png");
    m_play_texture.loadFromFile(DATA_PATH + "Menu/Play.png");
    m_quit_texture.loadFromFile(DATA_PATH + "Menu/Quit.png");
    m_settings_texture.loadFromFile(DATA_PATH + "Menu/Settings.png");

    //game menu textures
    m_game_menu_break_menu.loadFromFile(DATA_PATH + "GameMenu/BreakMenu.png");
    m_game_menu_resume.loadFromFile(DATA_PATH + "GameMenu/Resume.png");
    m_game_menu_menu.loadFromFile(DATA_PATH + "GameMenu/Menu.png");
    m_game_menu_game_over.loadFromFile(DATA_PATH + "GameMenu/GameOverMenu.png");
    m_game_menu_play_again.loadFromFile(DATA_PATH + "GameMenu/PlayAgain.png");

    //food textures
    m_food_texture.loadFromFile(DATA_PATH + "Floor/Apple.png");

    //sounds
    m_click_buffer.loadFromFile(DATA_PATH + "Sounds/ClickSound.wav");
    m_crunch_buffer.loadFromFile(DATA_PATH + "Sounds/Crunch.wav");
    m_game_over_buffer.loadFromFile(DATA_PATH + "Sounds/GameOverSound.wav");
    m_game_music.openFromFile(DATA_PATH + "Sounds/bgMusic.wav");

    //fonts
    m_game_font.loadFromFile(DATA_PATH + "Fonts/ARCADE_R.TTF");

    //icons
    m_snake_icon.loadFromFile(DATA_PATH + "Icons/SnakeIcon.png");
}

Resources& Resources::getInstance()
{
    return m_instance;
}