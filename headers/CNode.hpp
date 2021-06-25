#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "dataPath.hpp"

//node class to build the parts of the snake
struct CNode
{
    CNode(int, int, SnakeState);
    int nodePosX;   //x and y pos
    int nodePosY;
    CNode *prev;    //prev and next pointer for linked list
    CNode *next;
    sf::Sprite node;
    SnakeState nodeState;
    sf::Texture nodeTextureBody; //circle shape to safe all attributs of shape for drawing
    sf::Texture nodeTextureHead;
    void changeText(SnakeState, bool);
};

