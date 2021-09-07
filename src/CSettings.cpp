#include "../headers/CSettings.hpp"
#include <iostream>
#define LEFT_SIDE_X 300
#define RIGHT_SIDE_X 700
#define MAX_INIT_LENGTH (12 * 13)
#define MAX_FOOD_COUNT 10

using namespace std;
using namespace sf;

CSettings::CSettings() : 
m_resource(CResources::getInstance()),
m_settings_values(CSettingsValues::getInstance())
{
    //read settings from file and write them to member variables
    m_settings_values.getSettings();
    initValues();
    //initialise textures (only if object is an active settings instance)
    initTextures();
}

//destructor
CSettings::~CSettings()
{
    m_settings_values.setSettings();
}

WindowInstance CSettings::settingsTick(RenderWindow& renderWindow)
{
    Event event;
    static bool wait = true;
    static int b = 0;
    while(renderWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                renderWindow.close(); break;
            
            //can navigate window with buttons
            case Event::KeyPressed:
                switch(event.key.code)
                {
                    case Keyboard::Escape: return Menu; break;
                    default: break;
                }
                break;

            //mouse press event
            case Event::MouseButtonPressed:
                if(event.mouseButton.button == Mouse::Left)
                {
                    //get coordinates of mouse press
                    Vector2i cords = Mouse::getPosition(renderWindow);

                    //compare click position with slider dot bounds and set m_active_slider accordingly
                    if(m_slider_music->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_music;          
                    }
                    else if(m_slider_eat->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_eat;   
                    }
                    else if(m_slider_game_over->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_game_over;         
                    }
                    else if(m_slider_click->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_click;     
                    }
                    else if(m_slider_length->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_length;     
                    }
                    else if(m_slider_food_count->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_int = m_slider_food_count;     
                    }
                    else if(m_slider_difficulty->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider_diff = m_slider_difficulty;     
                    }
                    else if(m_menu_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, save settings, wait and return Menu
                        m_click_sound.play(); 
                        sleep(milliseconds(300)); 
                        return Menu;
                    }
                }
                break;

            case Event::MouseButtonReleased:
                //if left mousebutton is released and 
                if(event.mouseButton.button == Mouse::Left)
                {
                    
                    if(m_active_slider_int != nullptr)
                        m_active_slider_int = nullptr; 
                    else if(m_active_slider_diff != nullptr)
                        m_active_slider_diff = nullptr;
                }

                break;

            default: break;
        }
        moveSlider(renderWindow);
    }
    //default returns false so game doesn't start
    return Settings;
}


//moves the slider that is currently active to the x cursor position
void CSettings::moveSlider(const RenderWindow& renderWindow)
{
    if(m_active_slider_int != nullptr)
    {
        if(m_active_slider_int->moveSlider(Mouse::getPosition(renderWindow).x))
        {
            if(m_active_slider_int == m_slider_length)
                m_active_slider_int->setSliderLabel("Length:" + to_string(*m_length));
            else if(m_active_slider_int == m_slider_food_count)
                m_active_slider_int->setSliderLabel("Apples:" + to_string(*m_food_count));
        }
        
    }
    else if(m_active_slider_diff != nullptr)
    {
        if(m_active_slider_diff->moveSlider(Mouse::getPosition(renderWindow).x))
            //set the slider name texture to the corresponding texture from the texture array according to m_difficulty only 
            m_active_slider_diff->setSliderLabel(difficulty_string_arr[static_cast<int>(*m_difficulty)]);
    }
}

//initialise all sliders
void CSettings::initSliders()
{
    m_slider_music = make_shared<CSlider<int>>(m_volume_music, RIGHT_SIDE_X, 260, "Music");
    m_slider_eat = make_shared<CSlider<int>>(m_volume_eat, RIGHT_SIDE_X, 380, "Eat");
    m_slider_game_over = make_shared<CSlider<int>>(m_volume_game_over, RIGHT_SIDE_X, 500, "Lost");
    m_slider_click = make_shared<CSlider<int>>(m_volume_click, RIGHT_SIDE_X, 620, "Click");
    m_slider_difficulty = make_shared<CSlider<Difficulty>>(m_difficulty, LEFT_SIDE_X, 260, difficulty_string_arr[static_cast<int>(*m_difficulty)], 0, 4);
    m_slider_length = make_shared<CSlider<int>>(m_length, LEFT_SIDE_X, 380, "Length:" + to_string(*m_length), 2, MAX_INIT_LENGTH);
    m_slider_food_count = make_shared<CSlider<int>>(m_food_count, LEFT_SIDE_X, 500, "Apples:" + to_string(*m_food_count), 1, MAX_FOOD_COUNT);
}

//initialises all textures if settings are active
void CSettings::initTextures()
{
        m_menu_bounds = initButton(m_menu_sprite, m_resource.m_menu_texture, Vector2f(500, 880));
        initButton(m_difficulty_sprite, m_resource.m_difficulty_texture, Vector2f(LEFT_SIDE_X, 160));
        initButton(m_volume_sprite, m_resource.m_volume_texture, Vector2f(RIGHT_SIDE_X, 160));
        //set sound source and volume for click sound
        m_click_sound.setBuffer(m_resource.m_click_buffer);
        m_click_sound.setVolume(*m_volume_click);
        //initialise sliders
        initSliders();
        
}

void CSettings::initValues()
{
    m_volume_music = m_settings_values.getVolumeMusic();
    m_volume_click = m_settings_values.getVolumeClick();
    m_volume_eat = m_settings_values.getVolumeEat();
    m_volume_game_over = m_settings_values.getVolumeGameOver();
    m_length = m_settings_values.getLength();
    m_food_count = m_settings_values.getFoodCount();
    m_difficulty = m_settings_values.getDifficulty();
}

//used to initialise a button with a texture, position and origin
FloatRect CSettings::initButton(Sprite& sprite, Texture& texture, Vector2f pos)
{
    sprite.setTexture(texture);
    sprite.setOrigin(int(sprite.getGlobalBounds().width/2), int(sprite.getGlobalBounds().height/2));
    sprite.setPosition(pos);

    //returns global bounds for button click-detection
    return sprite.getGlobalBounds();
}

//draws all the sprites, buttons and sliders
void CSettings::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(*m_slider_music);
    target.draw(*m_slider_eat);
    target.draw(*m_slider_click);
    target.draw(*m_slider_game_over);
    target.draw(*m_slider_length);
    target.draw(*m_slider_difficulty);
    target.draw(*m_slider_food_count);

    target.draw(m_difficulty_sprite);
    target.draw(m_volume_sprite);
    target.draw(m_menu_sprite);
}