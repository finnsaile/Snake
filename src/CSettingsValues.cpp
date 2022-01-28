#include "../headers/CSettingsValues.hpp"

#define MAX_INIT_LENGTH ((12 * 13) + 1)
#define MAX_FOOD_COUNT 10
#define SETTINGS_COUNT 9

using namespace std;

CSettingsValues CSettingsValues::m_instance;

CSettingsValues::CSettingsValues() :
m_resource(CResources::getInstance())
{
    getSettings();
}

CSettingsValues::~CSettingsValues()
{
    setSettings();
}

void CSettingsValues::setSettings()
{
    ofstream output;
    output.open(m_resource.DATA_PATH + "settings.txt");
    output << "VolumeMusic{" << m_volume_music << "}\n"
    << "VolumeEat{" << m_volume_eat << "}\n"
    << "VolumeClick{" << m_volume_click << "}\n"
    << "VolumeGameOver{" << m_volume_game_over << "}\n"
    << "Length{" << m_length << "}\n"
    << "FoodCount{" << m_food_count << "}\n"
    << "WallCrash{" << static_cast<int>(m_wall_crash_b) << "}\n"
    << "SelfCrash{" << static_cast<int>(m_self_crash_b) << "}\n"
    << "Difficulty{" << static_cast<int>(m_difficulty) << "}\n";
    output.close();
}

//retrieves settings from text file and assigns the values to the variables
void CSettingsValues::getSettings()
{
    int arr[SETTINGS_COUNT], fst, lst;
    string tempString;
    ifstream input;
    input.open(m_resource.DATA_PATH + "settings.txt");
    if(input.fail())
    {
        for(int i = 0; i < SETTINGS_COUNT; i++)
        {
            arr[i] = 0;
        }
    }
    else
    {
        //loop for retrieving values and writing them to temporary array
        for(int i = 0; i < SETTINGS_COUNT; i++)
        {
            getline(input, tempString);
            //value is enclosed in curly brackets e.g. {20}
            fst = tempString.find("{");
            lst = tempString.find("}");
            //try create substring only containing the value, convert it and write it to array
            //if value can't be determined set it to 0
            try 
            {
                arr[i] = stoi(tempString.substr(fst + 1, lst - fst));
            }
            catch(...)
            {
                for(int j = 0; j < SETTINGS_COUNT; j++)
                    arr[j] = 0;
                break;
            }
        } 
    }

    //initialise all values with values from array
    m_volume_music = arr[0];
    m_volume_eat = arr[1];
    m_volume_click = arr[2];
    m_volume_game_over = arr[3];
    m_length = arr[4];
    m_food_count = arr[5];
    m_wall_crash_b = static_cast<bool>(arr[6]);
    m_self_crash_b = static_cast<bool>(arr[7]);
    m_difficulty = static_cast<Difficulty>(arr[8]);

    input.close();
    if(m_length > MAX_INIT_LENGTH) m_length = MAX_INIT_LENGTH;
    else if(m_length < 2) m_length = 2;

    if(m_food_count < 1) m_food_count = 1;
    else if(m_food_count > MAX_FOOD_COUNT) m_food_count = MAX_FOOD_COUNT;
}

CSettingsValues& CSettingsValues::getInstance()
{
    return m_instance;
}

int* CSettingsValues::getVolumeMusic()
{
    return &m_volume_music;
}

int* CSettingsValues::getVolumeClick()
{
    return &m_volume_click;
}

int* CSettingsValues::getVolumeEat()
{
    return &m_volume_eat;
}

int* CSettingsValues::getVolumeGameOver()
{
    return &m_volume_game_over;
}

int* CSettingsValues::getLength()
{
    return &m_length;
}

int* CSettingsValues::getFoodCount()
{
    return &m_food_count;
}

bool* CSettingsValues::getWallCrash()
{
    return &m_wall_crash_b;
}

bool* CSettingsValues::getSelfCrash()
{
    return &m_self_crash_b;
}

Difficulty* CSettingsValues::getDifficulty() 
{
    return &m_difficulty;
}