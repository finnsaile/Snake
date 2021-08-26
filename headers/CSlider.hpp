#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CResources.hpp"


class CSlider : public sf::Drawable
{
    public:
        //constructor
        CSlider(int*, int, int, sf::Texture&);
        //move slider according to input coordinate
        void moveSlider(int);
        //return slider bounds for activation
        sf::FloatRect getSliderBounds();
    private:
        //initialises all slider sprites
        void initSlider();

        //values for calulating the correct positions and values
        int* m_slider_value;
        int m_slider_min = 0;
        int m_slider_max = 100;
        int m_slider_pos_x;
        int m_slider_pos_y;

        CResources& m_resource;
        //textures and sprites
        sf::Texture& m_slider_name_texture;
        sf::Sprite m_slider_bar_sprite;
        sf::Sprite m_slider_dot_sprite;
        sf::Sprite m_slider_name_sprite;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};