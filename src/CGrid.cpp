#include "../headers/CGrid.hpp"

#define GRID_SIZE 25
#define TILE_SIZE 40

CGrid::CGrid() : 
m_resource(CResources::getInstance())
{
    //for loop creates grid made of sprites
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) 
            {
                m_grid[i][j].setTexture(m_resource.m_grid_texture_dark);
            }
            else 
            {
                m_grid[i][j].setTexture(m_resource.m_grid_texture_light);
            }
            m_grid[i][j].setPosition(i * TILE_SIZE, j * TILE_SIZE);
        }
    }
}

CGrid::~CGrid()
{}

//draw method draws each sprite from array
void CGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            target.draw(this->m_grid[i][j]);
        }
    }
}