#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CNode.hpp"
#include "headerEnum.hpp"
#include "CFood.hpp"


//snake class
class CSnake : public sf::Drawable
{
    //functions to add/remove head/tail of snake to make it move
    public:
        CSnake(int, int, unsigned int);
        ~CSnake();
        void addHead(CFood&, WindowInstance&);
        void removeTail();
        void setState(SnakeState);
        void setChangedThisTick(bool);
        bool getChangedThisTick();
        SnakeState getState();
        CNode* getHead();
    private:
        SnakeState m_snake_state = W;
        bool m_changed_this_tick_b = false;
        
        //node pointer for head and tail
        CNode *tail;
        CNode *head;        
        
        void initSnake(const unsigned int);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};