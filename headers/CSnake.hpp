#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "CNode.hpp"
#include "headerEnum.hpp"
#include "CFood.hpp"
#include "CSettingsValues.hpp"


//snake class
class CSnake : public sf::Drawable
{
    //functions to add/remove head/tail of snake to make it move
    public:
        CSnake(int, int, unsigned int, unsigned int);
        ~CSnake();
        bool addHead(WindowInstance&);
        void removeTail();
        void setState(SnakeState);
        void setChangedThisTick(bool);
        bool getChangedThisTick();
        SnakeState getState();
        CNode* getHead();
    private:
        SnakeState m_snake_state = W;
        bool m_changed_this_tick_b = false;
        std::vector<CFood> m_food_vec;

        CSettingsValues& m_settings_values;

        //node pointer for head and tail
        CNode *tail;
        CNode *head;        
        
        bool checkFoodBounds(sf::FloatRect&);

        void initSnake(const unsigned int);
        void initFood(const unsigned int);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};