#include "../headers/CGameMenu.hpp"

CGameMenu::CGameMenu(CGame* game, std::string menuTexturePath, std::string button1TexturePath, std::string button2TexturePath, int button1Y, int button2Y, int gameMenuY) : 
sf::Drawable(),
gameInstance(game),
settings(false)
{   
    initGameMenu(menuTexturePath, gameMenuY);
    initButton1(button1TexturePath, button1Y);
    initButton2(button2TexturePath, button2Y);
    clickBuffer.loadFromFile(dataPath + "Sounds/ClickSound.wav");
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(settings.getVolumeClick());  
}

CGameMenu::~CGameMenu()
{}

WindowInstance CGameMenu::gameMenuTick(sf::RenderWindow& renderWindow)
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
                    case sf::Keyboard::Escape: return Menu; break;
                    case sf::Keyboard::Space: return Game; break;
                    default: break;
                }
                break;
            
            //mouse press event
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    //get coordinates of mouse press
                    sf::Vector2i cords = sf::Mouse::getPosition(renderWindow);
                    //check collition between mouse coordinates and resumeBound
                    if(button1Bound.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        sf::sleep(sf::milliseconds(300)); 
                        return button1Action();
                    }
                    //check collition between mouse coordinates and menuBound
                    else if(button2Bound.contains(cords.x, cords.y)) 
                    {
                        //play click sound wait and close window
                        clickSound.play(); 
                        sf::sleep(sf::milliseconds(300)); 
                        return button2Action(); 
                    }  
                }
                break;
            default: break;
        }
    }
    //default returns false so game doesn't start
    return BreakMenu;
}

void CGameMenu::initGameMenu(std::string texturePath, int y)
{
    gameMenuTexture.loadFromFile(texturePath);
    this->gameMenuSprite.setTexture(this->gameMenuTexture);
    this->gameMenuSprite.setOrigin(int(gameMenuSprite.getGlobalBounds().width/2), int(gameMenuSprite.getGlobalBounds().height/2));
    this->gameMenuSprite.setPosition(500, y);
}

void CGameMenu::initButton1(std::string texturePath, int y)
{
    button1Texture.loadFromFile(texturePath);
    //sets play texture, sets origin in center and sets position
    this->button1Sprite.setTexture(button1Texture);
    this->button1Sprite.setOrigin(int(button1Sprite.getGlobalBounds().width/2), int(button1Sprite.getGlobalBounds().height/2));
    this->button1Sprite.setPosition(500, y);
    //get bounds for mouseclick event
    this->button1Bound = button1Sprite.getGlobalBounds();
}

void CGameMenu::initButton2(std::string texturePath, int y)
{
    button2Texture.loadFromFile(texturePath);
    //sets play texture, sets origin in center and sets position
    this->button2Sprite.setTexture(button2Texture);
    this->button2Sprite.setOrigin(int(button2Sprite.getGlobalBounds().width/2), int(button2Sprite.getGlobalBounds().height/2));
    this->button2Sprite.setPosition(500, y);
    //get bounds for mouseclick event
    this->button2Bound = button2Sprite.getGlobalBounds();
}

void CGameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->gameInstance); 
    target.draw(this->gameMenuSprite);  
    target.draw(this->button1Sprite);
    target.draw(this->button2Sprite);
}

WindowInstance CGameMenu::button1Action()
{
    return Game;
}

WindowInstance CGameMenu::button2Action()
{
    return Menu;
}