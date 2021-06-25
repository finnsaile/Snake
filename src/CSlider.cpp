#include "../headers/CSlider.hpp"
#include <iostream>

CSlider::CSlider(int* variableAdress, int posX, int posY, std::string sliderNamePath) : 
sf::Drawable(),
variablePointer(variableAdress),
sliderPosX(posX),
sliderPosY(posY),
sliderMin(0),
sliderMax(100)
{
    sliderNameTexture.loadFromFile(sliderNamePath);
    sliderBarTexture.loadFromFile(dataPath + "Slider/SliderBar.png");
    sliderDotTexture.loadFromFile(dataPath + "Slider/SliderDot.png");
    sliderBarSprite.setTexture(sliderBarTexture);
    sliderDotSprite.setTexture(sliderDotTexture);
    sliderBarSprite.setOrigin(0/*int(sliderBarSprite.getGlobalBounds().width/2)*/, int(sliderBarSprite.getGlobalBounds().height/2));
    sliderDotSprite.setOrigin(int(sliderDotSprite.getGlobalBounds().width/2), int(sliderDotSprite.getGlobalBounds().height/2));
    sliderBarSprite.setPosition(sliderPosX - 125, sliderPosY);
    sliderDotSprite.setPosition(sliderBarSprite.getPosition().x + (*variablePointer) * 2.5, sliderPosY);
    sliderNameSprite.setTexture(sliderNameTexture);
    sliderNameSprite.setOrigin(int(sliderNameSprite.getGlobalBounds().width) / 2, int(sliderNameSprite.getGlobalBounds().height) / 2);
    sliderNameSprite.setPosition(sliderPosX, sliderPosY - 30);
}

void CSlider::moveSlider(int cordX)
{
    if(cordX >= sliderBarSprite.getPosition().x && cordX <= sliderBarSprite.getPosition().x + 250)
    {
        sliderDotSprite.setPosition(cordX, sliderPosY);
        *variablePointer = int((cordX - sliderBarSprite.getPosition().x) / 2.5);
    }
    else if(cordX < sliderBarSprite.getPosition().x)
    {
        sliderDotSprite.setPosition(sliderPosX - 125, sliderPosY);
        *variablePointer = 0;
    }
    else
    {
        sliderDotSprite.setPosition(sliderPosX + 125, sliderPosY);
        *variablePointer = 100;
    }
}

sf::FloatRect CSlider::getSliderBounds()
{
    return(sliderDotSprite.getGlobalBounds());
}

void CSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sliderBarSprite);
    target.draw(sliderDotSprite);
    target.draw(sliderNameSprite);
}