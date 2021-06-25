#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "dataPath.hpp"

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
        sf::Sprite grid[25][25];
        sf::Texture gridTexture1;
        sf::Texture gridTexture2;        
};