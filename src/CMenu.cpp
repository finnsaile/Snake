#include "../headers/CMenu.hpp"
#define hallo 4
//constructor initializes 2 colors
CMenu::CMenu():
sf::Drawable(),
settings(false),
myBlack(0, 0, 0, 200), 
myGreen(0, 255, 0, 200)
{
    //menu Font, png files for buttons and click sound gets imported
    menuFont.loadFromFile(dataPath + "Fonts/ARCADE_R.TTF"); 
    logoTexture.loadFromFile(dataPath + "Menu/SnakeLogo.png");
    playTexture.loadFromFile(dataPath + "Menu/Play.png");
    quitTexture.loadFromFile(dataPath + "Menu/Quit.png");
    settingsTexture.loadFromFile(dataPath + "Menu/Settings.png");
    clickBuffer.loadFromFile(dataPath + "Sounds/ClickSound.wav");
    //clickSound gets initialized
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(settings.getVolumeClick());
    //logo, play and quit buttons get initialized
    initLogo();
    initPlay();
    initQuit(); 
    initSettings();
}

//menuTick function
WindowInstance CMenu::menuTick(sf::RenderWindow& renderWindow)
{
    //wait Event to prevent unnecessary memory and cpu usage
    sf::Event event;
    while(renderWindow.waitEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                renderWindow.close(); break;
            
            //can navigate window with buttons
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Space: return Settings; break;
                    case sf::Keyboard::Escape:  renderWindow.close(); break;
                    default: break;
                }
                break;
            
            //mouse press event
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    //get coordinates of mouse press
                    sf::Vector2i cords = sf::Mouse::getPosition(renderWindow);
                    //check collition between mouse coordinates and playBound
                    if(playBound.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        sf::sleep(sf::milliseconds(300)); 
                        return Game;
                    }
                    //check collition between mouse coordinates and quitBound
                    else if(quitBound.contains(cords.x, cords.y)) 
                    {
                        //play click sound wait and close window
                        clickSound.play(); 
                        sf::sleep(sf::milliseconds(300)); 
                        renderWindow.close();  
                    }  
                    else if(settingsBound.contains(cords.x, cords.y)) 
                    {
                        //play click sound wait and close window
                        clickSound.play(); 
                        sf::sleep(sf::milliseconds(300)); 
                        return Settings;  
                    }  
                }
                break;
            default: break;
        }
    }
    //default returns false so game doesn't start
    return Menu;
}

//draw dunction draws all 3 logos/buttons
void CMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(logo);
    target.draw(play);
    target.draw(quit);
    target.draw(settingsSprite);
}

//initializes logo
void CMenu::initLogo()
{
    //sets logo texture, sets origin in center and sets position
    this->logo.setTexture(logoTexture);
    this->logo.setOrigin(int(logo.getGlobalBounds().width/2), int(logo.getGlobalBounds().height/2));
    this->logo.setPosition(500, 300);
}

//initialize play button
void CMenu::initPlay()
{
    //sets play texture, sets origin in center and sets position
    this->play.setTexture(playTexture);
    this->play.setOrigin(int(play.getGlobalBounds().width/2), int(play.getGlobalBounds().height/2));
    this->play.setPosition(500, 500);
    //get bounds for mouseclick event
    this->playBound = play.getGlobalBounds();
}

//initialize quit button
void CMenu::initSettings()
{
    //sets quit texture, sets origin in center and sets position
    this->settingsSprite.setTexture(settingsTexture);
    this->settingsSprite.setOrigin(int(settingsSprite.getGlobalBounds().width/2), int(settingsSprite.getGlobalBounds().height/2));
    this->settingsSprite.setPosition(500, 680);
    //get bounds for mouseclick event
    this->settingsBound = settingsSprite.getGlobalBounds();
}

//initialize quit button
void CMenu::initQuit()
{
    //sets quit texture, sets origin in center and sets position
    this->quit.setTexture(quitTexture);
    this->quit.setOrigin(int(quit.getGlobalBounds().width/2), int(quit.getGlobalBounds().height/2));
    this->quit.setPosition(500, 860);
    //get bounds for mouseclick event
    this->quitBound = quit.getGlobalBounds();
}