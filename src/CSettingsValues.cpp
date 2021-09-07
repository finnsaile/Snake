#include "../headers/CSettingsValues.hpp"

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
    output << "VolumeMusic{" << m_volume_music << "}\n";
    output << "VolumeEat{" << m_volume_eat << "}\n";
    output << "VolumeClick{" << m_volume_click << "}\n";
    output << "VolumeGameOver{" << m_volume_game_over << "}\n";
    output << "Length{" << m_length << "}\n";
    output << "Difficulty{" << static_cast<int>(m_difficulty) << "}\n";
    output.close();
}

//retrieves settings from text file and assigns the values to the variables
void CSettingsValues::getSettings()
{
    int arr[6], fst, lst;
    string tempString;
    ifstream input;
    input.open(m_resource.DATA_PATH + "settings.txt");
    if(input.fail())
    {
        for(int i = 0; i < 6; i++)
        {
            arr[i] = 0;
        }
    }
    else
    {
        //loop for retrieving values and writing them to temporary array
        for(int i = 0; i < 6; i++)
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
                for(int j = 0; j < 6; j++)
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
    m_difficulty = static_cast<Difficulty>(arr[5]);

    input.close();
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

Difficulty* CSettingsValues::getDifficulty() 
{
    return &m_difficulty;
}