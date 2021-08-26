#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "dataPath.hpp"
#include "CResources.hpp"

//node class to build the parts of the snake
struct CNode
{
    CNode(int, int, SnakeState);

    CResources& m_resource;

    int m_node_pos_y;
    int m_node_pos_x;

    CNode *prev;    //prev and next pointer for linked list
    CNode *next;

    sf::Sprite m_node;
    SnakeState m_node_state;

    sf::Texture* m_node_texture;
    sf::Texture* nodeTextureBody; //circle shape to safe all attributs of shape for drawing
    sf::Texture* nodeTextureHead;
    void changeTexture(SnakeState, bool);
};

