#include "../headers/CGrid.hpp"


CGrid::CGrid() : 
m_resource(CResources::getInstance())
{
    //for loop creates grid made of sprites
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) 
            {
                m_grid[i][j].setTexture(m_resource.m_grid_texture_dark);
            }
            else 
            {
                m_grid[i][j].setTexture(m_resource.m_grid_texture_light);
            }
            m_grid[i][j].setPosition(i * 40, j * 40);
        }
    }
}

CGrid::~CGrid()
{}

//draw method draws each sprite from array
void CGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            target.draw(this->m_grid[i][j]);
        }
    }
}