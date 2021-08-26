#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CResources.hpp"

//class to draw grid in the background
class CGrid : public sf::Drawable
{
    public:
    //constructor takes rectangle size and texture adress
        CGrid();
        ~CGrid();
    private:
    //grid to store all sprites in
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        CResources& m_resource;
        sf::Sprite m_grid[25][25];      
};