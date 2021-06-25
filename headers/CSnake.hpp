#pragma once
#include <SFML/Graphics.hpp>
#include "CNode.hpp"
#include "headerEnum.hpp"
#include "CFood.hpp"
#include <iostream>

//snake class
class CSnake : public sf::Drawable
{
    //functions to add/remove head/tail of snake to make it move
    public:
        CSnake(int, int);
        ~CSnake();
        void addHead(CFood&, WindowInstance&);
        void removeTail();
        void setState(SnakeState);
        void setChangedThisTick(bool);
        bool getChangedThisTick();
        SnakeState getState();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        SnakeState snakeState;
        bool changedThisTick;
        //node pointer for head and tail
        CNode *tail;
        CNode *head;        
};