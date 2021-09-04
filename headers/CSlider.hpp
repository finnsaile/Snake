#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CResources.hpp"

#define SLIDER_WIDTH 250

//template class. type determines the type of value that the slider controlls 
template<typename T>
class CSlider : public sf::Drawable
{
    public:
        //constructor
        CSlider(T*, int, int, sf::Texture&, int = 0, int = 100);
        //move slider according to input coordinate
        bool moveSlider(int);
        //return slider bounds for activation
        sf::FloatRect getSliderBounds() const; 
        void setSliderName(sf::Texture&);
    private:
        //initialises all slider sprites
        void initSlider();

        //values for calulating the correct positions and values
        T* m_slider_value;
        int m_slider_min;
        int m_slider_max;
        int m_slider_pos_x;
        int m_slider_pos_y;

        CResources& m_resource;
        //textures and sprites
        const sf::Texture* m_slider_name_texture;

        sf::Sprite m_slider_bar_sprite;
        sf::Sprite m_slider_dot_sprite;
        sf::Sprite m_slider_name_sprite;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

//initialise all textures and sprites for the slider
template<typename T>
CSlider<T>::CSlider(T* value_pointer, int pos_x, int pos_y, sf::Texture& slider_name_texture, int slider_min, int slider_max) : 
m_slider_max(slider_max),
m_slider_min(slider_min),
m_slider_value(value_pointer),
m_slider_pos_x(pos_x),
m_slider_pos_y(pos_y),
m_resource(CResources::getInstance()),
m_slider_name_texture(&slider_name_texture)
{   
    //check if value of slider is out of bounds, 
    //if yes change value to upper or lower bound respectively 
    if(*m_slider_value > static_cast<T>(m_slider_max))
        *m_slider_value = static_cast<T>(m_slider_max);
    else if(*m_slider_value < static_cast<T>(m_slider_min))
        *m_slider_value = static_cast<T>(m_slider_min);    

    initSlider(); 
}

//move slider to given x coordinate if the slider dot is still within the slider bounds
template<typename T>
bool CSlider<T>::moveSlider(int cord_x)
{   
    int temp_slider_value;
    //if input coordinate is within the bounds of the slider coordinates move slider dot
    if(cord_x >= m_slider_bar_sprite.getPosition().x && cord_x <= m_slider_bar_sprite.getPosition().x + SLIDER_WIDTH)
    {
        //move slider dot to input x position and slider y position
        m_slider_dot_sprite.setPosition(cord_x, m_slider_pos_y);
        //set value which the slider regulates according to postion of the slider dot, min and max value of the slider. Add 0.5 to round up or down on 0.5
        temp_slider_value = m_slider_min + static_cast<int>(0.5 + (cord_x - m_slider_bar_sprite.getPosition().x) / (static_cast<float>(SLIDER_WIDTH)/(m_slider_max - m_slider_min)));
    }   
    //if input cords are smaller than lower bound
    else if(cord_x < m_slider_bar_sprite.getPosition().x)
    {   
        //set slider dot to lower bound position
        m_slider_dot_sprite.setPosition(m_slider_pos_x - SLIDER_WIDTH/2, m_slider_pos_y);
        //set slider value to min value
        temp_slider_value = m_slider_min;
    }
    //if input cors are larger than upper bound position
    else
    {   
        //set slider dot to upper bound position
        m_slider_dot_sprite.setPosition(m_slider_pos_x + SLIDER_WIDTH/2, m_slider_pos_y);
        //set slider value to max value
        temp_slider_value = m_slider_max;
    }
    //change the value the slider controlls to the calculated value
    if(*m_slider_value != static_cast<T>(temp_slider_value))
    {
        *m_slider_value = static_cast<T>(temp_slider_value);
        return true;
    }

    return false;    
}

//init position, origin and textures for slider components
template<typename T>
void CSlider<T>::initSlider()
{
    m_slider_bar_sprite.setTexture(m_resource.m_slider_bar_texture);
    m_slider_dot_sprite.setTexture(m_resource.m_slider_dot_texture);
    m_slider_name_sprite.setTexture(*m_slider_name_texture);

    //origin of slider bar is on the lower bound in the center
    m_slider_bar_sprite.setOrigin(0, int(m_slider_bar_sprite.getGlobalBounds().height/2));
    m_slider_dot_sprite.setOrigin(int(m_slider_dot_sprite.getGlobalBounds().width/2), int(m_slider_dot_sprite.getGlobalBounds().height/2));
    m_slider_name_sprite.setOrigin(int(m_slider_name_sprite.getGlobalBounds().width) / 2, int(m_slider_name_sprite.getGlobalBounds().height) / 2);

    //position of slider bar is set according to slider location and slider bar origin
    m_slider_bar_sprite.setPosition(m_slider_pos_x - SLIDER_WIDTH/2, m_slider_pos_y);
    //slider dot x position is set using slider value and min value to determine the value, and slider width over slider value delta to determin the scale
    m_slider_dot_sprite.setPosition(m_slider_bar_sprite.getPosition().x + (*m_slider_value - m_slider_min) * (static_cast<float>(SLIDER_WIDTH)/(m_slider_max - m_slider_min)), m_slider_pos_y);
    m_slider_name_sprite.setPosition(m_slider_pos_x, m_slider_pos_y - 30); 
}

//get bounds of slider dot to check for activation
template<typename T> 
sf::FloatRect CSlider<T>::getSliderBounds() const
{
    return(m_slider_dot_sprite.getGlobalBounds());
}

//change the texture of the slider name
template<typename T>
void CSlider<T>::setSliderName(sf::Texture& slider_name_texture)
{
    m_slider_name_texture = &slider_name_texture;
    sf::IntRect temp_int_rect(0, 0, m_slider_name_texture->getSize().x, m_slider_name_texture->getSize().y);
    m_slider_name_sprite.setTextureRect(temp_int_rect);
    m_slider_name_sprite.setTexture(*m_slider_name_texture);
    m_slider_name_sprite.setOrigin(int(m_slider_name_sprite.getGlobalBounds().width) / 2, int(m_slider_name_sprite.getGlobalBounds().height) / 2);
    m_slider_name_sprite.setPosition(m_slider_pos_x, m_slider_pos_y - 30); 
}

//draws all slider components
template<typename T>
void CSlider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_slider_bar_sprite);
    target.draw(m_slider_dot_sprite);
    target.draw(m_slider_name_sprite);
}