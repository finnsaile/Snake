#include "../headers/CGame.hpp"
#include <chrono>

#define START_POS_Y 480
#define START_POS_X 480

using namespace sf;
using namespace std;

//game constructor initializes snake, food pointer and grid
CGame::CGame(): 
m_snake(START_POS_X, START_POS_Y, 2),
m_difficulty_f(convertDifficulty(m_settings.getDifficulty()))
{
    m_food = make_shared<CFood>(m_settings.getDifficulty(), m_snake.getHead());
}

CGame::~CGame()
{}

//game tick function takes renderWindow as parameter to get input
WindowInstance CGame::gameTick(RenderWindow& renderWindow)
{
    //chang bool to determine if menu should be opened
    m_new_instance = Game;
    //eventloop
     if(m_snake.getChangedThisTick() == false)
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
                            case Keyboard::W: if (m_snake.getState() != S) m_snake.setState(W); break;
                            case Keyboard::D: if (m_snake.getState() != A) m_snake.setState(D); break;
                            case Keyboard::S: if (m_snake.getState() != W) m_snake.setState(S); break;
                            case Keyboard::A: if (m_snake.getState() != D) m_snake.setState(A); break;
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
            m_snake.addHead(*m_food, m_new_instance);
            m_clock.restart();
            m_snake.setChangedThisTick(false);
        }
    return m_new_instance;
}

//draw function draws grid food and snake
void CGame::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_grid);
    target.draw(m_snake);
    target.draw(*m_food);
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