#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <fstream>
#include "CCounter.hpp"
#include "CNode.hpp"
#include "CResources.hpp"
#include "CSettingsValues.hpp"

//food class to create food
class CFood : public sf::Drawable
{
    public:
        CFood(Difficulty, CNode*, std::vector<CFood>&);
        ~CFood();
        //gotEaten to relocate food
        void gotEaten(CNode*, std::vector<CFood>&);
        //returnRect to get bounds of food
        sf::FloatRect getFoodBounds();
    private:
        int m_pos_x;
        int m_pos_y;

        CResources& m_resource;    
        CSettingsValues& m_settings_values;

        sf::Sprite m_food_sprite;
        sf::Sound m_crunch_sound;

        Difficulty m_difficulty;
        
        void setRandCoordinates(CNode* head, std::vector<CFood>&);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};