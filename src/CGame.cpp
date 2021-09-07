#include "../headers/CGame.hpp"
#include <chrono>

#define START_POS_Y 480
#define START_POS_X 480

using namespace sf;
using namespace std;

//game constructor initializes snake, food pointer and grid
CGame::CGame():
m_settings_values(CSettingsValues::getInstance()),
m_resource(CResources::getInstance()), 
m_counter(0, 960, 35, false),
m_highscore(initHighscore(*m_settings_values.getDifficulty()), 40, 35, true)
{
    m_difficulty_f = convertDifficulty(*m_settings_values.getDifficulty());
    m_snake = make_shared<CSnake>(START_POS_X, START_POS_Y, *m_settings_values.getLength(), *m_settings_values.getFoodCount());
}

CGame::~CGame()
{
    //get new highscore
    switch(*m_settings_values.getDifficulty())
    {
        case Easy: m_highscore_easy = m_highscore.getScore(); break;
        case Medium: m_highscore_medium = m_highscore.getScore(); break;
        case Hard: m_highscore_hard = m_highscore.getScore(); break;
        case Extreme: m_highscore_extreme = m_highscore.getScore(); break;
        case Impossible: m_highscore_impossible = m_highscore.getScore(); break;
    }

    //write all highscores to file
    ofstream output;
    output.open(m_resource.DATA_PATH + "highscore.txt");
    output << "HighscoreEasy{" << m_highscore_easy << "}\n";
    output << "HighscoreMedium{" << m_highscore_medium << "}\n";
    output << "HighscoreHard{" << m_highscore_hard << "}\n";
    output << "HighscoreExtreme{" << m_highscore_extreme << "}\n";
    output << "HighscoreImpossible{" << m_highscore_impossible << "}\n";
    output.close();
}

//game tick function takes renderWindow as parameter to get input
WindowInstance CGame::gameTick(RenderWindow& renderWindow)
{
    //chang bool to determine if menu should be opened
    m_new_instance = Game;
    //eventloop
     if(m_snake->getChangedThisTick() == false)
     {
        Event event;
        while(renderWindow.pollEvent(event))
        {
            switch(event.type)
            {
                //close game when X is pressed
                case Event::Closed: 
                    renderWindow.close(); break;
                
                //determines the correct key press
                case Event::KeyPressed:
                         switch(event.key.code)
                        {
                            //W A S D for movement. Can't go in opposite direction
                            case Keyboard::W: if (m_snake->getState() != S) m_snake->setState(W); break;
                            case Keyboard::D: if (m_snake->getState() != A) m_snake->setState(D); break;
                            case Keyboard::S: if (m_snake->getState() != W) m_snake->setState(S); break;
                            case Keyboard::A: if (m_snake->getState() != D) m_snake->setState(A); break;
                            //if escape is pressed m_new_instance is set to true
                            case Keyboard::Escape:  m_new_instance = BreakMenu; break;
                            default: break;
                        }
                    //} 
                default: break;
            }
            break;
        }
     }
        //movement tick
        if (m_clock.getElapsedTime().asSeconds() > m_difficulty_f
            && m_new_instance == Game)
        {
            //if addHead returns true menu is opened
            if(m_snake->addHead(m_new_instance))
            {
                //counter gets increased by one and new coordinates are set
                if(m_counter.getScore() >= m_highscore.getScore())
                {
                    m_highscore.increaseScore(1);
                }
                m_counter.increaseScore(1);
            }
            m_clock.restart();
            m_snake->setChangedThisTick(false);
        }
    return m_new_instance;
}

//initialise the highscore from text file
unsigned int CGame::initHighscore(Difficulty difficulty)
{
    int arr[5], fst, lst;
    string tempString;

    ifstream input;
    input.open(m_resource.DATA_PATH + "highscore.txt");
    if(input.fail())
    {
        for(int i = 0; i < 5; i++)
        {
            arr[i] = 0;
        }
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            getline(input, tempString);
            //value is enclosed in curly brackets e.g. {20}
            fst = tempString.find("{");
            lst = tempString.find("}");
            //create substring only containing the value, convert it and write it to array
            //if value can't be determined set it to 0
            try 
            {
                arr[i] = stoi(tempString.substr(fst + 1, lst - fst));
            }
            catch(...)
            {
                arr[i] = 0;
            }
        }
    }
    //loop for retrieving values and writing them to temporary array
    
    
    //assign values from array to respective highscore variables
    m_highscore_easy = arr[0];
    m_highscore_medium = arr[1];
    m_highscore_hard = arr[2];
    m_highscore_extreme = arr[3];
    m_highscore_impossible = arr[4];

    input.close();

    //return difficulty value for highscore
    switch(difficulty)
    {
        case Easy: return m_highscore_easy;
        case Medium: return m_highscore_medium;
        case Hard: return m_highscore_hard;
        case Extreme: return m_highscore_extreme;
        case Impossible: return m_highscore_impossible;
    }
}

float CGame::convertDifficulty(Difficulty difficulty)
{
    switch(difficulty)
    {
        case Easy: return 0.1;
        case Medium: return 0.08;
        case Hard: return 0.06;
        case Extreme: return 0.04;
        case Impossible: return 0.02;

        default: return 0.1;
    }
}

//draw function draws grid food and snake
void CGame::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_grid);
    target.draw(*m_snake);
    target.draw(m_counter);
    target.draw(m_highscore);
}
