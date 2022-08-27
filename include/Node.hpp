#pragma once
#include <SFML/Graphics.hpp>
#include "headerEnum.hpp"
#include "Resources.hpp"

//node class to build the parts of the snake
struct Node
{
    Node(int, int, SnakeState);

    Resources& m_resource;

    int m_node_pos_y;
    int m_node_pos_x;

    Node *prev;    //prev and next pointer for linked list
    Node *next;

    sf::Sprite m_node;
    SnakeState m_node_state;

    sf::Texture* m_node_texture;
    sf::Texture* nodeTextureBody; //circle shape to safe all attributs of shape for drawing
    sf::Texture* nodeTextureHead;
    void changeTexture(SnakeState, bool);
};

