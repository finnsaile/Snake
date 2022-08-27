#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Resources.hpp"

//class to draw grid in the background
class Grid : public sf::Drawable
{
    public:
    //constructor takes rectangle size and texture adress
        Grid();
        ~Grid();
    private:
    //grid to store all sprites in
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Resources& m_resource;
        sf::Sprite m_grid[25][25];      
};