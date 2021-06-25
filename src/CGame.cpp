#include "../headers/CGame.hpp"

//game constructor initializes snake, food pointer and grid
CGame::CGame(): 
sf::Drawable(), 
mysnake(480, 480),
settings(false)
{
    food = new CFood(settings.getDifficulty());
}

CGame::~CGame()
{
    delete food;
}

//game tick function takes renderWindow as parameter to get input
WindowInstance CGame::gameTick(sf::RenderWindow& renderWindow)
{
    //chang bool to determine if menu should be opened
    newInstance = Game;
     //eventloop
     if(mysnake.getChangedThisTick() == false)
     {
        sf::Event event;
        while(renderWindow.pollEvent(event))
        {
            switch(event.type)
            {
                //close game when X is pressed
                case sf::Event::Closed: 
                    renderWindow.close(); break;
                
                //determines the correct key press
                case sf::Event::KeyPressed:
                    //getChangedThisTick to allow only one movement per tick
                    //if(mysnake.getChangedThisTick() == false)
                    //{
                         switch(event.key.code)
                        {
                            //W A S D for movement. Can't go in opposite direction
                            case sf::Keyboard::W: if (mysnake.getState() != S) mysnake.setState(W); break;
                            case sf::Keyboard::D: if (mysnake.getState() != A) mysnake.setState(D); break;
                            case sf::Keyboard::S: if (mysnake.getState() != W) mysnake.setState(S); break;
                            case sf::Keyboard::A: if (mysnake.getState() != D) mysnake.setState(A); break;
                            //if escape is pressed newInstance is set to true
                            case sf::Keyboard::Escape:  newInstance = BreakMenu; break;
                            default: break;
                        }
                    //} 
                default: break;
            }
            break;
        }
     }
        //movement tick(snake moves every 0.1 seconds)
        if (clock.getElapsedTime().asSeconds() > convertDifficulty(settings.getDifficulty()) //0.02 Impossible, 0.04 Extreme, 0.06 Hard, 0.08 Medium, 0.1 Easy
            && newInstance == Game)
        {
            //if addHead returns true menu is opened
            mysnake.addHead(*food, newInstance);
            clock.restart();
            mysnake.setChangedThisTick(false);
        }
    return newInstance;
}

//draw function draws grid food and snake
void CGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(grid);
    target.draw(mysnake);
    target.draw(*food);
}

float CGame::convertDifficulty(Difficulty n)
{
    switch(n)
    {
        case Easy: return 0.1;
        case Medium: return 0.08;
        case Hard: return 0.06;
        case Extreme: return 0.04;
        case Impossible: return 0.02;
        default: return 0.1;
    }
}