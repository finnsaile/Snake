#pragma once
#include <SFML/Graphics.hpp>
#include "dataPath.hpp"
#include <iostream>

class CSlider : public sf::Drawable
{
    public:
        CSlider(int*, int, int, std::string);
        void moveSlider(int);
        sf::FloatRect getSliderBounds();
    private:
        int* variablePointer;
        int sliderMin;
        int sliderMax;
        int sliderPosX;
        int sliderPosY;
        sf::Texture sliderBarTexture;
        sf::Texture sliderDotTexture;
        sf::Texture sliderNameTexture;
        sf::Sprite sliderBarSprite;
        sf::Sprite sliderDotSprite;
        sf::Sprite sliderNameSprite;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};