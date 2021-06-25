#include "../headers/CSettings.hpp"

using namespace std;
CSettings::CSettings(bool initBool) : 
sf::Drawable(),
delBool(initBool)
{
    int fst, lst;
    string tempString;
    ifstream input;
    input.open(dataPath + "settings.txt");
    
    //get volumeMusic line
    getline(input, tempString);
    fst = tempString.find("{");
    lst = tempString.find("}");
    //safe value to volumeMusic
    this->volumeMusic = stoi(tempString.substr(fst + 1, lst - fst));

    //get volumeEat line
    getline(input, tempString);
    fst = tempString.find("{");
    lst = tempString.find("}");
    //safe value to volumeEat
    this->volumeEat = stoi(tempString.substr(fst + 1, lst - fst));

    //get volumeClick line
    getline(input, tempString);
    fst = tempString.find("{");
    lst = tempString.find("}");
    //safe value to volumeClick
    this->volumeClick = stoi(tempString.substr(fst + 1, lst - fst));

    //get volumeGameOver line
    getline(input, tempString);
    fst = tempString.find("{");
    lst = tempString.find("}");
    //safe value to volumeGameOver
    this->volumeGameOver = stoi(tempString.substr(fst + 1, lst - fst));

    //get difficulty line
    getline(input, tempString);
    fst = tempString.find("{");
    lst = tempString.find("}");
    //safe value to difficulty
    this->difficulty = (Difficulty)stoi(tempString.substr(fst + 1, lst - fst));
    
    input.close();

    if(initBool)
    {
        clickBuffer.loadFromFile(dataPath + "Sounds/ClickSound.wav");
        clickSound.setBuffer(clickBuffer);
        clickSound.setVolume(volumeClick);

        initDifficultyEasy();
        initDifficultyMedium();
        initDifficultyHard();
        initDifficultyExtreme();
        initDifficultyImpossible();
        initSliders();
        initHeadline();
        initMenu();
    }
}

CSettings::~CSettings()
{
    if(delBool)
    {
        delete sliderMusic;
        delete sliderGameOver;
        delete sliderEat;
        delete sliderClick;
    }
}

WindowInstance CSettings::settingsTick(sf::RenderWindow& renderWindow)
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
                    case sf::Keyboard::Escape: this->setSettings(); return Menu; break;
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
                    if(difficultyEasyBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        difficulty = Easy;
                    }
                    else if(difficultyMediumBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        difficulty = Medium;
                    }
                    else if(difficultyHardBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        difficulty = Hard;
                    }
                    else if(difficultyExtremeBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        difficulty = Extreme;
                    }
                    else if(difficultyImpossibleBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        difficulty = Impossible;
                    } 
                    else if(sliderMusic->getSliderBounds().contains(cords.x, cords.y))
                    {
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {   
                                sliderMusic->moveSlider(sf::Mouse::getPosition(renderWindow).x);
                                renderWindow.clear(sf::Color (169,169,169));
                                renderWindow.draw(*this);
                                renderWindow.display();
                        }        
                    }
                    else if(sliderEat->getSliderBounds().contains(cords.x, cords.y))
                    {
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {   
                                sliderEat->moveSlider(sf::Mouse::getPosition(renderWindow).x);
                                renderWindow.clear(sf::Color (169,169,169));
                                renderWindow.draw(*this);
                                renderWindow.display();
                        }
                            
                    }
                    else if(sliderGameOver->getSliderBounds().contains(cords.x, cords.y))
                    {
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {   
                                sliderGameOver->moveSlider(sf::Mouse::getPosition(renderWindow).x);
                                renderWindow.clear(sf::Color (169,169,169));
                                renderWindow.draw(*this);
                                renderWindow.display();
                        }
                            
                    }
                    else if(sliderClick->getSliderBounds().contains(cords.x, cords.y))
                    {
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {   
                                sliderClick->moveSlider(sf::Mouse::getPosition(renderWindow).x);
                                renderWindow.clear(sf::Color (169,169,169));
                                renderWindow.draw(*this);
                                renderWindow.display();
                        }
                            
                    }
                    else if(menuBounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        clickSound.play(); 
                        this->setSettings();
                        sf::sleep(sf::milliseconds(300)); 
                        return Menu;
                    }
                }
                break;
            default: break;
        }
    }
    //default returns false so game doesn't start
    return Settings;
}


void CSettings::setSettings()
{
    ofstream output;
    output.open(dataPath + "settings.txt");
    output << "VolumeMusic{" << this->volumeMusic << "}\n";
    output << "VolumeEat{" << this->volumeEat << "}\n";
    output << "VolumeClick{" << this->volumeClick << "}\n";
    output << "VolumeGameOver{" << this->volumeGameOver << "}\n";
    output << "Difficulty{" << this->difficulty << "}\n";
    output.close();
}

int CSettings::getVolumeMusic()
{
    return this->volumeMusic;
}

int CSettings::getVolumeEat()
{
    return this->volumeEat;
}

int CSettings::getVolumeClick()
{
    return this->volumeClick;
}

int CSettings::getVolumeGameOver()
{
    return this->volumeGameOver;
}

Difficulty CSettings::getDifficulty()
{
    return this->difficulty;
}

void CSettings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(difficultyEasySprite);
    target.draw(difficultyMediumSprite);
    target.draw(difficultyHardSprite);
    target.draw(difficultyExtremeSprite);
    target.draw(difficultyImpossibleSprite);
    target.draw(*sliderMusic);
    target.draw(*sliderEat);
    target.draw(*sliderClick);
    target.draw(*sliderGameOver);
    target.draw(difficultySprite);
    target.draw(volumeSprite);
    target.draw(menuSprite);
}

void CSettings::initHeadline()
{
    this->difficultyTexture.loadFromFile(dataPath + "Settings/Difficulty.png");
    this->volumeTexture.loadFromFile(dataPath + "Settings/Volume.png");
    this->volumeSprite.setTexture(volumeTexture);
    this->difficultySprite.setTexture(difficultyTexture);
    this->difficultySprite.setOrigin(int(difficultySprite.getGlobalBounds().width/2), int(difficultySprite.getGlobalBounds().height/2));
    this->volumeSprite.setOrigin(int(volumeSprite.getGlobalBounds().width/2), int(volumeSprite.getGlobalBounds().height/2));
    this->volumeSprite.setPosition(700, 160);
    this->difficultySprite.setPosition(300, 160);

}

void CSettings::initSliders()
{
    sliderMusic = new CSlider(&volumeMusic, 700, 260, dataPath + "Slider/MusicVolume.png");
    sliderEat = new CSlider(&volumeEat, 700, 380, dataPath + "Slider/EatVolume.png");
    sliderGameOver = new CSlider(&volumeGameOver, 700, 500, dataPath + "Slider/LostVolume.png");
    sliderClick = new CSlider(&volumeClick, 700, 620, dataPath + "Slider/ClickVolume.png");
}

//initialize quit button
void CSettings::initDifficultyEasy()
{
    difficultyEasyTexture.loadFromFile(dataPath + "Settings/Easy.png");
    //sets quit texture, sets origin in center and sets position
    this->difficultyEasySprite.setTexture(difficultyEasyTexture);
    this->difficultyEasySprite.setOrigin(int(difficultyEasySprite.getGlobalBounds().width/2), int(difficultyEasySprite.getGlobalBounds().height/2));
    this->difficultyEasySprite.setPosition(300, 260);
    //get bounds for mouseclick event
    this->difficultyEasyBounds = difficultyEasySprite.getGlobalBounds();
}

//initialize quit button
void CSettings::initDifficultyMedium()
{
    difficultyMediumTexture.loadFromFile(dataPath + "Settings/Medium.png");
    //sets quit texture, sets origin in center and sets position
    this->difficultyMediumSprite.setTexture(difficultyMediumTexture);
    this->difficultyMediumSprite.setOrigin(int(difficultyMediumSprite.getGlobalBounds().width/2), int(difficultyMediumSprite.getGlobalBounds().height/2));
    this->difficultyMediumSprite.setPosition(300, 380);
    //get bounds for mouseclick event
    this->difficultyMediumBounds = difficultyMediumSprite.getGlobalBounds();
}

//initialize quit button
void CSettings::initDifficultyHard()
{
    difficultyHardTexture.loadFromFile(dataPath + "Settings/Hard.png");
    //sets quit texture, sets origin in center and sets position
    this->difficultyHardSprite.setTexture(difficultyHardTexture);
    this->difficultyHardSprite.setOrigin(int(difficultyHardSprite.getGlobalBounds().width/2), int(difficultyHardSprite.getGlobalBounds().height/2));
    this->difficultyHardSprite.setPosition(300, 500);
    //get bounds for mouseclick event
    this->difficultyHardBounds = difficultyHardSprite.getGlobalBounds();
}

//initialize quit button
void CSettings::initDifficultyExtreme()
{
    difficultyExtremeTexture.loadFromFile(dataPath + "Settings/Extreme.png");
    //sets quit texture, sets origin in center and sets position
    this->difficultyExtremeSprite.setTexture(difficultyExtremeTexture);
    this->difficultyExtremeSprite.setOrigin(int(difficultyExtremeSprite.getGlobalBounds().width/2), int(difficultyExtremeSprite.getGlobalBounds().height/2));
    this->difficultyExtremeSprite.setPosition(300, 620);
    //get bounds for mouseclick event
    this->difficultyExtremeBounds = difficultyExtremeSprite.getGlobalBounds();
}

//initialize quit button
void CSettings::initDifficultyImpossible()
{
    difficultyImpossibleTexture.loadFromFile(dataPath + "Settings/Impossible.png");
    //sets quit texture, sets origin in center and sets position
    this->difficultyImpossibleSprite.setTexture(difficultyImpossibleTexture);
    this->difficultyImpossibleSprite.setOrigin(int(difficultyImpossibleSprite.getGlobalBounds().width/2), int(difficultyImpossibleSprite.getGlobalBounds().height/2));
    this->difficultyImpossibleSprite.setPosition(300, 740);
    //get bounds for mouseclick event
    this->difficultyImpossibleBounds = difficultyImpossibleSprite.getGlobalBounds();
}

//initialize quit button
void CSettings::initMenu()
{
    menuTexture.loadFromFile(dataPath + "Settings/Menu.png");
    //sets quit texture, sets origin in center and sets position
    this->menuSprite.setTexture(menuTexture);
    this->menuSprite.setOrigin(int(menuSprite.getGlobalBounds().width/2), int(menuSprite.getGlobalBounds().height/2));
    this->menuSprite.setPosition(500, 880);
    //get bounds for mouseclick event
    this->menuBounds = menuSprite.getGlobalBounds();
}


