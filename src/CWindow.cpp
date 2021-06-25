#include "../headers/CWindow.hpp"

//constructor initializes game/menuInstance with NULL and
//windowInstance with Menu so Menu is opend when object is created
CWindow::CWindow() : 
sf::Drawable(),
settings(new CSettings(false)),
gameInstance(NULL),
menuInstance(NULL),
breakMenuInstance(NULL),
gameOverMenuInstance(NULL),
settingsInstance(NULL),
windowInstance(Menu),
newInstance(Menu)
{
    //initialize music for game
    this->gameMusic.openFromFile(dataPath + "Sounds/bgMusic.wav");
    this->gameMusic.setLoop(true);
}

//window Tick takes renderWindow
void CWindow::windowTick(sf::RenderWindow& renderWindow)
{
    //instance is changed when changeInstanceBool is true
    this->changeInstance();
    //switch for Instance (either Menu or Game)
    switch(this->windowInstance)
    {
        case Menu: 
            //if no menuInstance exists
            if(this->menuInstance == NULL) 
            {
                //delete gameInstance and create new Menu Instance
                renderWindow.setKeyRepeatEnabled(false);
                delete this->breakMenuInstance;
                delete this->gameOverMenuInstance;
                delete this->gameInstance;
                delete this->settingsInstance;
                this->settingsInstance = NULL;
                this->breakMenuInstance = NULL;
                this->gameOverMenuInstance = NULL;
                this->gameInstance = NULL;
                this->menuInstance = new CMenu; 
                //stop game music
                this->gameMusic.stop();
            }
            else
            {
                //if menuInstance exists get bool from menuTick to determine whether or not to change the Instance
                this->newInstance = this->menuInstance->menuTick(renderWindow);
            }
            break;

        case Game: 
            //if no gameInstance exists
            if(this->gameInstance == NULL) 
            {
                //delete menuInstance and create new Game Instance
                delete this->menuInstance;
                if(gameOverMenuInstance != NULL) 
                {
                    delete this->gameOverMenuInstance;
                    this->gameOverMenuInstance = NULL;
                }
                this->menuInstance = NULL;
                this->gameInstance = new CGame; 
                //start playing gamemusic and set volume
                this->gameMusic.setVolume(settings->getVolumeMusic());
                this->gameMusic.play();
            }
            else
            {
                if(this->breakMenuInstance != NULL)
                {
                    delete this->breakMenuInstance;
                    this->breakMenuInstance = NULL;
                    this->gameMusic.play();
                }
                if(this->gameOverMenuInstance != NULL)
                {
                    delete this->gameOverMenuInstance;
                    this->gameOverMenuInstance = NULL;
                    this->gameMusic.play();
                }
                //if gameInstance exists get bool from gameTick to determine whether or not to change the Instance
                this->newInstance = this->gameInstance->gameTick(renderWindow);
            }
            break;
        case Settings:
            //if no settingsInstance exists
            if(this->settingsInstance == NULL) 
            {
                renderWindow.setKeyRepeatEnabled(true);
                //delete menuInstance and create new Settings Instance
                delete this->menuInstance;
                this->menuInstance = NULL; 
                this->settingsInstance = new CSettings(true);
            }
            else
            {
                //if menuInstance exists get bool from menuTick to determine whether or not to change the Instance
                this->newInstance = this->settingsInstance->settingsTick(renderWindow);
                if(newInstance != Settings)
                {
                    delete settings;
                    settings = new CSettings(false);
                }
            }
            break;
        
        case BreakMenu:
            if(this->breakMenuInstance == NULL)
            {
                this->breakMenuInstance = new CBreakMenu(gameInstance, 
                                                        dataPath + "GameMenu/BreakMenu.png", 
                                                        dataPath + "GameMenu/Resume.png", 
                                                        dataPath + "GameMenu/Menu.png");
                this->gameMusic.stop();
            }
            else
            {
                this->newInstance = this->breakMenuInstance->gameMenuTick(renderWindow);
            }
            break;

        case GameOverMenu: 
            if(this->gameOverMenuInstance == NULL)
            {
                this->gameOverMenuInstance = new CGameOverMenu(gameInstance, 
                                                        dataPath + "GameMenu/GameOverMenu.png", 
                                                        dataPath + "GameMenu/PlayAgain.png", 
                                                        dataPath + "GameMenu/Menu.png");
                this->gameMusic.stop();
            }
            else
            {
                this->newInstance = this->gameOverMenuInstance->gameMenuTick(renderWindow);
                if(this->newInstance == Game)
                {
                    delete gameInstance;
                    gameInstance = new CGame;
                }
            }
            break;
    }
}

//draw function either draws Game or Menu
void CWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch(this->windowInstance)
    {
        case Menu: target.draw(*this->menuInstance); break;
        case Game: target.draw(*this->gameInstance); break;
        case BreakMenu: target.draw(*this->breakMenuInstance); break;
        case GameOverMenu: target.draw(*this->gameOverMenuInstance); break;
        case Settings: target.draw(*this->settingsInstance); break;
    }
}

//changes Instance
void CWindow::changeInstance()
{
    if (newInstance != windowInstance)
    {
        switch(newInstance)
        {
            case Menu: this->windowInstance = Menu; break;
            case Game: this->windowInstance = Game; break;
            case BreakMenu: this->windowInstance = BreakMenu; break;
            case GameOverMenu: this->windowInstance = GameOverMenu; break;
            case Settings: this->windowInstance = Settings; break;
        }
    }
}
