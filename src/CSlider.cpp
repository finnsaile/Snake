#include "../headers/CSlider.hpp"
#include <iostream>

#define SLIDER_WIDTH 250
//initialise all textures and sprites for the slider
CSlider::CSlider(int* value_pointer, int pos_x, int pos_y, std::string sliderNamePath) : 
m_slider_value(value_pointer),
m_slider_pos_x(pos_x),
m_slider_pos_y(pos_y)
{   
    //load texture for slider name
    m_slider_name_texture.loadFromFile(sliderNamePath);

    //check if value of slider is out of bounds, 
    //if yes change value to upper or lower bound respectively 
    if(*m_slider_value > m_slider_max)
        *m_slider_value = m_slider_max;
    else if(*m_slider_value < m_slider_min)
        *m_slider_value = m_slider_min;    

    initSlider(); 
}

//move slider to given x coordinate if the slider dot is still within the slider bounds
void CSlider::moveSlider(int cord_x)
{   
    //if input coordinate is within the bounds of the slider coordinates move slider dot
    if(cord_x >= m_slider_bar_sprite.getPosition().x && cord_x <= m_slider_bar_sprite.getPosition().x + SLIDER_WIDTH)
    {
        //move slider dot to input x position and slider y position
        m_slider_dot_sprite.setPosition(cord_x, m_slider_pos_y);
        //set value which the slider regulates according to postion of the slider dot, min and max value of the slider
        *m_slider_value = m_slider_min + static_cast<int>((cord_x - m_slider_bar_sprite.getPosition().x) / (static_cast<float>(SLIDER_WIDTH)/(m_slider_max - m_slider_min)));
    }   
    //if input cords are smaller than lower bound
    else if(cord_x < m_slider_bar_sprite.getPosition().x)
    {   
        //set slider dot to lower bound position
        m_slider_dot_sprite.setPosition(m_slider_pos_x - SLIDER_WIDTH/2, m_slider_pos_y);
        //set slider value to min value
        *m_slider_value = m_slider_min;
    }
    //if input cors are larger than upper bound position
    else
    {   
        //set slider dot to upper bound position
        m_slider_dot_sprite.setPosition(m_slider_pos_x + SLIDER_WIDTH/2, m_slider_pos_y);
        //set slider value to max value
        *m_slider_value = m_slider_max;
    }
}

//init position, origin and textures for slider components
void CSlider::initSlider()
{
    m_slider_bar_texture.loadFromFile(dataPath + "Slider/SliderBar.png");
    m_slider_dot_texture.loadFromFile(dataPath + "Slider/SliderDot.png");

    m_slider_bar_sprite.setTexture(m_slider_bar_texture);
    m_slider_dot_sprite.setTexture(m_slider_dot_texture);
    m_slider_name_sprite.setTexture(m_slider_name_texture);

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
sf::FloatRect CSlider::getSliderBounds()
{
    return(m_slider_dot_sprite.getGlobalBounds());
}

//draws all slider components
void CSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_slider_bar_sprite);
    target.draw(m_slider_dot_sprite);
    target.draw(m_slider_name_sprite);
}