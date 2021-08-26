#include "../headers/CSnake.hpp"

using namespace sf;
using namespace std;

//constructor takes new head position as argument 
//and initializes new node as head, snakeState(direction) and changedState
CSnake::CSnake(int init_x, int init_y): 
head(new CNode(init_y, init_x, W))
{  
    //tail = head (only 1 node exists)
    head->prev = NULL;
    tail = head;
}

CSnake::~CSnake()
{
    CNode* temp = head;
    while (head != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }  
}

//function to add head for movement/growth food pointer as arguments
void CSnake::addHead(CFood& food, WindowInstance& new_instance)
{
    //change texture of old head to normal body texture

    head->changeTexture(m_snake_state, false);

    int temp_y, temp_x;
    switch(m_snake_state)
    {
        //position of new head gets calculated using old heads position and moving direction
        case W: temp_y = head->m_node_pos_y - 40;  temp_x = head->m_node_pos_x; break;
        case D: temp_y = head->m_node_pos_y;       temp_x = head->m_node_pos_x + 40; break;
        case S: temp_y = head->m_node_pos_y + 40;  temp_x = head->m_node_pos_x; break;
        case A: temp_y = head->m_node_pos_y;       temp_x = head->m_node_pos_x - 40; break;
    }
    //new head gets created at calculated coordinates. All pointers are set to link the head to the list
    head->prev = new CNode(temp_y, temp_x, m_snake_state);
    head->prev->next = head;
    head = head->prev;
    head->prev = NULL;

    //bounds for head food and body to check for collition when creating the new head
    FloatRect food_bound = food.returnRect();
    FloatRect head_bound = head->m_node.getGlobalBounds();
    FloatRect body_bound;
    
    //if the head collides with one of the body nodes true is returned
    CNode *temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    //if new head is created outside the window(player crashed into border) true is returned
    if( head->m_node_pos_x < 0|
        head->m_node_pos_x >= 1000|
        head->m_node_pos_y < 0|
        head->m_node_pos_y >= 1000) new_instance = GameOverMenu;

    //if the head collides with the food 
    if(head_bound.intersects(food_bound))
    {
        temp->changeTexture(m_snake_state, true);
        //food gets relocated
        food.gotEaten(head);
        
        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            body_bound = temp->m_node.getGlobalBounds();
            if(head_bound.intersects(body_bound)) new_instance = GameOverMenu;
        }
    }
    else
    {
        if(temp->prev->prev != NULL) temp->prev->changeTexture(m_snake_state, true);
        //tail gests removed only when no food is eaten (snake grows)
        removeTail();

        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            body_bound = temp->m_node.getGlobalBounds();
            if(head_bound.intersects(body_bound)) new_instance = GameOverMenu;
        }
    }
}

//function that removes the tail node to make it seem like the snake is moving
void CSnake::removeTail()
{
    tail = tail->prev;
    delete tail->next;
    tail->next = NULL;
}

//draw function so snake can be drawn in window. Itterates through list and draws every node
void CSnake::draw(RenderTarget& target, RenderStates states) const
{   
    //draw each nodes circle from back to front
    CNode *temp = tail;
    while(temp != NULL)
    {
        target.draw(temp->m_node);
        temp = temp->prev;
    }
}

//returns state(direction) of snake
SnakeState CSnake::getState()
{
    return m_snake_state;
}

//returns whether snake changed already in current tick
bool CSnake::getChangedThisTick()
{
    return m_changed_this_tick_b;
}

//sets new state(new direction) and sets changedState to true
void CSnake::setState(SnakeState new_state)
{
    m_snake_state = new_state;
    m_changed_this_tick_b = true;
}

//sets changedState to parameter
void CSnake::setChangedThisTick(bool changed)
{
    m_changed_this_tick_b = changed;
}



