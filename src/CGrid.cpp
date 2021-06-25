#include "../headers/CGrid.hpp"


CGrid::CGrid(): sf::Drawable()
{
    //load grid resource
    gridTexture1.loadFromFile(dataPath + "Floor/Grass1.png");
    gridTexture2.loadFromFile(dataPath + "Floor/Grass2.png");
    //for loop creates grid mad of sprites
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) 
            {
                grid[i][j].setTexture(gridTexture1);
            }
            else 
            {
                grid[i][j].setTexture(gridTexture2);
            }
            grid[i][j].setPosition(i * 40, j * 40);
        }
    }
}

CGrid::~CGrid()
{}
//draw method draws each sprite in array
void CGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            target.draw(this->grid[i][j]);
        }
    }
}