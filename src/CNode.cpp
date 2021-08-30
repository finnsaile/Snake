#include "../headers/CNode.hpp"
#include <iostream>

using namespace sf;
//constructor initializes nodeposition and next pointer
CNode::CNode(int pos_y, int pos_x, SnakeState snake_state):
m_node_state(snake_state),
m_node_pos_y(pos_y),
m_node_pos_x(pos_x),
next(NULL),
m_resource(CResources::getInstance())
{
    //depeningent on direction of snake reference correct texture
    switch(snake_state)
    {
        case W: m_node_texture = &m_resource.m_head_w; break;
        case A: m_node_texture = &m_resource.m_head_a; break;
        case S: m_node_texture = &m_resource.m_head_s; break;
        case D: m_node_texture = &m_resource.m_head_d; break;
    }

    //set position, texture, and origin of node
    m_node.setTexture(*m_node_texture);
    m_node.setOrigin(Vector2f(0,0));
    m_node.setPosition(pos_x, pos_y);     
}

//function to change texture once node isn't head anymore
//this funtion gets called once for every node when a new head is created right above it
void CNode::changeTexture(SnakeState snake_state, bool tailBool)
{
    //if the node is not the last node of the snake
    if(tailBool == false)
    {   
        //if the snake is moving straigth
        if(snake_state == m_node_state)
        {
            //chose either the horizontal or vertical texture
            if(m_node_state == W || m_node_state == S) m_node_texture = &m_resource.m_body_ws;
            else if (m_node_state == A || m_node_state == D) m_node_texture = &m_resource.m_body_ad;
        }
        //if the new head is not moving in the same direction as the node,
        //meaning that the snake is turning, the texture needs to be a curve texture
        else
        {
            //load the right texture according to the combination of node- and snakestate
            if(snake_state == A && m_node_state == W || snake_state == S && m_node_state == D) m_node_texture = &m_resource.m_body_aw;
            else if(snake_state == D && m_node_state == W || snake_state == S && m_node_state == A) m_node_texture = &m_resource.m_body_dw;
            else if(snake_state == A && m_node_state == S || snake_state == W && m_node_state == D) m_node_texture = &m_resource.m_body_as;
            else if(snake_state == D && m_node_state == S || snake_state == W && m_node_state == A) m_node_texture = &m_resource.m_body_ds;
        }     
    }
    //if the node is the tail node
    else
    {
        //create temporary state pointer to avoid multiple switch cases
        SnakeState* temp_state;
        //if the snake is of size one head == tail. if this is not the case AND the previous node has a different state,
        //meaning that the current node is a curve node, set temp state to prev state so the texture of the tail
        //and the prev node allign 
        if (prev != NULL) //&& (m_node_state != prev->m_node_state)
            temp_state = &prev->m_node_state;
        //else set temp state to the current node state
        else    
            temp_state = &m_node_state;


        //chose correct texture according to temp state
        switch(*temp_state)
        {
            case W: m_node_texture = &m_resource.m_tail_w; break;
            case A: m_node_texture = &m_resource.m_tail_a; break;
            case S: m_node_texture = &m_resource.m_tail_s; break;
            case D: m_node_texture = &m_resource.m_tail_d; break;
        }
    }

    //set the texture of the node
    m_node.setTexture(*m_node_texture);
}