#include "../headers/CWindow.hpp"

using namespace sf;

//constructor initializes game/menuInstance with nullptr and
//windowInstance with Menu so Menu is opend when object is created
CWindow::CWindow() :
m_resource(CResources::getInstance()),
m_settings_values(CSettingsValues::getInstance())
{
    m_resource.m_game_music.setLoop(true);
}

//window Tick takes renderWindow
void CWindow::windowTick(RenderWindow& renderWindow)
{
    //instance is changed when changeInstanceBool is true 
    this->changeInstance();
    //switch for Instance (either Menu or Game)
    switch(m_window_instance)
    {
        case Menu: 
            //if no menuInstance exists
            if(m_menu_instance == nullptr) 
            {
                //delete gameInstance and create new Menu Instance
                renderWindow.setKeyRepeatEnabled(false);
                delete m_break_menu_instance;
                delete m_game_over_menu_instance;
                delete m_game_instance;
                delete m_settings_instance;
                m_settings_instance = nullptr;
                m_break_menu_instance = nullptr;
                m_game_over_menu_instance = nullptr;
                m_game_instance = nullptr;
                m_menu_instance = new CMenu; 
                //stop game music
                m_resource.m_game_music.stop();
            }
            else
            {
                //if menuInstance exists get bool from menuTick to determine whether or not to change the Instance
                m_new_instance = m_menu_instance->menuTick(renderWindow);
            }
            break;

        case Game: 
            //if no gameInstance exists
            if(m_game_instance == nullptr) 
            {
                //delete menuInstance and create new Game Instance
                delete m_menu_instance;
                if(m_game_over_menu_instance != nullptr) 
                {
                    delete m_game_over_menu_instance;
                    m_game_over_menu_instance = nullptr;
                }
                m_menu_instance = nullptr;
                m_game_instance = new CGame; 
                //start playing gamemusic and set volume
                m_resource.m_game_music.setVolume(*m_settings_values.getVolumeMusic());
                m_resource.m_game_music.play();
            }
            else
            {
                if(m_break_menu_instance != nullptr)
                {
                    delete m_break_menu_instance;
                    m_break_menu_instance = nullptr;
                    m_resource.m_game_music.play();
                }
                if(m_game_over_menu_instance != nullptr)
                {
                    delete m_game_over_menu_instance;
                    m_game_over_menu_instance = nullptr;
                    m_resource.m_game_music.play();
                }
                //if gameInstance exists get bool from gameTick to determine whether or not to change the Instance
                m_new_instance = m_game_instance->gameTick(renderWindow);
            }
            break;
        case Settings:
            //if no settingsInstance exists
            if(m_settings_instance == nullptr) 
            {
                renderWindow.setKeyRepeatEnabled(false);
                //delete menuInstance and create new Settings Instance
                delete m_menu_instance;
                m_menu_instance = nullptr; 
                m_settings_instance = new CSettings;
            }
            else
            {
                //if menuInstance exists get bool from menuTick to determine whether or not to change the Instance
                m_new_instance = m_settings_instance->settingsTick(renderWindow);
            }
            break;
        
        case BreakMenu:
            if(m_break_menu_instance == nullptr)
            {
                m_break_menu_instance = new CBreakMenu(m_game_instance, 
                                                        m_resource.m_game_menu_break_menu, 
                                                        m_resource.m_game_menu_resume, 
                                                        m_resource.m_game_menu_menu);
                m_resource.m_game_music.stop();
            }
            else
            {
                m_new_instance = m_break_menu_instance->gameMenuTick(renderWindow);
            }
            break;

        case GameOverMenu: 
            if(m_game_over_menu_instance == nullptr)
            {
                m_game_over_menu_instance = new CGameOverMenu(m_game_instance, 
                                                        m_resource.m_game_menu_game_over, 
                                                        m_resource.m_game_menu_play_again, 
                                                        m_resource.m_game_menu_menu);
                m_resource.m_game_music.stop();
            }
            else
            {
                m_new_instance = m_game_over_menu_instance->gameMenuTick(renderWindow);
                if(m_new_instance == Game)
                {
                    delete m_game_instance;
                    m_game_instance = new CGame;
                }
            }
            break;
    }
}

//draw function either draws Game or Menu
void CWindow::draw(RenderTarget& target, RenderStates states) const
{
    switch(m_window_instance)
    {
        case Menu: target.draw(*m_menu_instance); break;
        case Game: target.draw(*m_game_instance); break;
        case BreakMenu: target.draw(*m_break_menu_instance); break;
        case GameOverMenu: target.draw(*m_game_over_menu_instance); break;
        case Settings: target.draw(*m_settings_instance); break;
    }
}

//changes Instance
void CWindow::changeInstance()
{
    if (m_new_instance != m_window_instance)
        m_window_instance = m_new_instance;
}
