#include "../headers/CSettings.hpp"

#define LEFT_SIDE_X 300
#define RIGHT_SIDE_X 700

using namespace std;
using namespace sf;

CSettings::CSettings(bool initBool) : 
m_active_settings_b(initBool)
{
    //read settings from file and write them to member variables
    getSettings();
    //initialise textures (only if object is an active settings instance)
    initTextures();
}

//destructor
CSettings::~CSettings()
{}

WindowInstance CSettings::settingsTick(RenderWindow& renderWindow)
{
    //wait Event to prevent unnecessary memory and cpu usage
    Event event;
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
                    case Keyboard::Escape: this->setSettings(); return Menu; break;
                    default: break;
                }
                break;
            
            //mouse press event
            case Event::MouseButtonPressed:
                if(event.mouseButton.button == Mouse::Left)
                {
                    //get coordinates of mouse press
                    Vector2i cords = Mouse::getPosition(renderWindow);
                    //check collition between mouse coordinates and playBound
                    if(m_difficulty_easy_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        m_click_sound.play(); 
                        m_difficulty = Easy;
                    }
                    else if(m_difficulty_medium_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        m_click_sound.play(); 
                        m_difficulty = Medium;
                    }
                    else if(m_difficulty_hard_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        m_click_sound.play(); 
                        m_difficulty = Hard;
                    }
                    else if(m_difficulty_extreme_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        m_click_sound.play(); 
                        m_difficulty = Extreme;
                    }
                    else if(m_difficulty_impossible_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gest started)
                        m_click_sound.play(); 
                        m_difficulty = Impossible;
                    } 
                    else if(m_slider_music->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider = m_slider_music;          
                    }
                    else if(m_slider_eat->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider = m_slider_eat;   
                            
                    }
                    else if(m_slider_game_over->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider = m_slider_game_over;         
                    }
                    else if(m_slider_click->getSliderBounds().contains(cords.x, cords.y))
                    {
                        m_active_slider = m_slider_click;     
                    }
                    else if(m_menu_bounds.contains(cords.x, cords.y)) 
                    {
                        //play click sound, wait and return true(game gets started)
                        m_click_sound.play(); 
                        this->setSettings();
                        sleep(milliseconds(LEFT_SIDE_X)); 
                        return Menu;
                    }
                }
                break;
            case Event::MouseButtonReleased:
                if(event.mouseButton.button == Mouse::Left)
                    if(m_active_slider != nullptr)
                        m_active_slider = nullptr;
                break;

            default: break;
        }
        moveSlider(renderWindow);
    }
    //default returns false so game doesn't start
    return Settings;
}

//write the settings to output file using the values from class members
void CSettings::setSettings()
{
    ofstream output;
    output.open(dataPath + "settings.txt");
    output << "VolumeMusic{" << m_volume_music << "}\n";
    output << "VolumeEat{" << m_volume_eat << "}\n";
    output << "VolumeClick{" << m_volume_click << "}\n";
    output << "VolumeGameOver{" << m_volume_game_over << "}\n";
    output << "Difficulty{" << m_difficulty << "}\n";
    output.close();
}

//retrieves settings from text file and assigns the values to the variables
void CSettings::getSettings()
{
    int arr[5], fst, lst;
    string tempString;
    ifstream input;
    input.open(dataPath + "settings.txt");

    //loop for retrieving values and writing them to temporary array
    for(int i = 0; i < 5; i++)
    {
        getline(input, tempString);
        //value is enclosed in curly brackets e.g. {20}
        fst = tempString.find("{");
        lst = tempString.find("}");
        //create substring only containing the value, convert it and write it to array
        arr[i] = stoi(tempString.substr(fst + 1, lst - fst));
    }
    //initialise all values with values from array
    m_volume_music = arr[0];
    m_volume_eat = arr[1];
    m_volume_click = arr[2];
    m_volume_game_over = arr[3];
    m_difficulty = static_cast<Difficulty>(arr[4]);

    input.close();
}

//moves the slider that is currently active to the x cursor position
void CSettings::moveSlider(const RenderWindow& renderWindow)
{
    if(m_active_slider != nullptr)
    {
        m_active_slider->moveSlider(Mouse::getPosition(renderWindow).x);
    }
}

void CSettings::initSliders()
{
    m_slider_music = make_shared<CSlider>(&m_volume_music, RIGHT_SIDE_X, 260, dataPath + "Slider/MusicVolume.png");
    m_slider_eat = make_shared<CSlider>(&m_volume_eat, RIGHT_SIDE_X, 380, dataPath + "Slider/EatVolume.png");
    m_slider_game_over = make_shared<CSlider>(&m_volume_game_over, RIGHT_SIDE_X, 500, dataPath + "Slider/LostVolume.png");
    m_slider_click = make_shared<CSlider>(&m_volume_click, RIGHT_SIDE_X, 620, dataPath + "Slider/ClickVolume.png");
}

//initialises all textures if settings are active
void CSettings::initTextures()
{
    if(m_active_settings_b)
    {
        loadFiles();
        m_difficulty_easy_bounds = initButton(m_difficulty_easy_sprite, m_difficulty_easy_texture, Vector2f(LEFT_SIDE_X, 260));
        m_difficulty_medium_bounds = initButton(m_difficulty_medium_sprite, m_difficulty_medium_texture, Vector2f(LEFT_SIDE_X, 380));
        m_difficulty_hard_bounds = initButton(m_difficulty_hard_sprite, m_difficulty_hard_texture, Vector2f(LEFT_SIDE_X, 500));
        m_difficulty_extreme_bounds = initButton(m_difficulty_extreme_sprite, m_difficulty_extreme_texture, Vector2f(LEFT_SIDE_X, 620));
        m_difficulty_impossible_bounds = initButton(m_difficulty_impossible_sprite, m_difficulty_impossible_texture, Vector2f(LEFT_SIDE_X, 740));
        m_menu_bounds = initButton(m_menu_sprite, m_menu_texture, Vector2f(500, 880));
        initButton(m_difficulty_sprite, m_difficulty_texture, Vector2f(LEFT_SIDE_X, 160));
        initButton(m_volume_sprite, m_volume_texture, Vector2f(RIGHT_SIDE_X, 160));
        //set sound source and volume for click sound
        m_click_sound.setBuffer(m_click_buffer);
        m_click_sound.setVolume(m_volume_click);
        //initialise sliders
        initSliders();
    }
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

//loads all assets from files
void CSettings::loadFiles()
{
    m_click_buffer.loadFromFile(dataPath + "Sounds/m_click_sound.wav");
    m_difficulty_easy_texture.loadFromFile(dataPath + "Settings/Easy.png");
    m_difficulty_medium_texture.loadFromFile(dataPath + "Settings/Medium.png");
    m_difficulty_hard_texture.loadFromFile(dataPath + "Settings/Hard.png");
    m_difficulty_extreme_texture.loadFromFile(dataPath + "Settings/Extreme.png");
    m_difficulty_impossible_texture.loadFromFile(dataPath + "Settings/Impossible.png");
    m_difficulty_texture.loadFromFile(dataPath + "Settings/Difficulty.png");
    m_volume_texture.loadFromFile(dataPath + "Settings/Volume.png");
    m_menu_texture.loadFromFile(dataPath + "Settings/Menu.png");
}

int CSettings::getVolumeMusic() const 
{
    return this->m_volume_music;
}

int CSettings::getVolumeEat() const
{
    return this->m_volume_eat;
}

int CSettings::getVolumeClick() const
{
    return this->m_volume_click;
}

int CSettings::getVolumeGameOver() const
{
    return this->m_volume_game_over;
}

Difficulty CSettings::getDifficulty() const
{
    return this->m_difficulty;
}

//draws all the sprites, buttons and sliders
void CSettings::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_difficulty_easy_sprite);
    target.draw(m_difficulty_medium_sprite);
    target.draw(m_difficulty_hard_sprite);
    target.draw(m_difficulty_extreme_sprite);
    target.draw(m_difficulty_impossible_sprite);
    target.draw(*m_slider_music);
    target.draw(*m_slider_eat);
    target.draw(*m_slider_click);
    target.draw(*m_slider_game_over);
    target.draw(m_difficulty_sprite);
    target.draw(m_volume_sprite);
    target.draw(m_menu_sprite);
}