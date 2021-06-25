#include "../headers/CSnake.hpp"

//constructor takes new head position as argument 
//and initializes new node as head, snakeState(direction) and changedState
CSnake::CSnake(int initX, int initY): 
sf::Drawable(),
snakeState(W),
head(new CNode(initY, initX, W)),
changedThisTick(false)
{  
    //tail = head (only 1 node exists)
    this->head->prev = NULL;
    this->tail = head;
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
void CSnake::addHead(CFood& food, WindowInstance& newInstance)
{
    //change texture of old head to normal body texture

    this->head->changeText(this->snakeState, false);

    int tempY, tempX;
    switch(this->snakeState)
    {
        //position of new head gets calculated using old heads position and moving direction
        case W: tempY = this->head->nodePosY - 40;  tempX = this->head->nodePosX; break;
        case D: tempY = this->head->nodePosY;       tempX = this->head->nodePosX + 40; break;
        case S: tempY = this->head->nodePosY + 40;  tempX = this->head->nodePosX; break;
        case A: tempY = this->head->nodePosY;       tempX = this->head->nodePosX - 40; break;
    }
    //new head gets created at calculated coordinates. All pointers are set to link the head to the list
    this->head->prev = new CNode(tempY, tempX, snakeState);
    this->head->prev->next = head;
    this->head = head->prev;
    this->head->prev = NULL;

    //bounds for head food and body to check for collition when creating the new head
    sf::FloatRect foodBound = food.returnRect();
    sf::FloatRect headBound = this->head->node.getGlobalBounds();
    sf::FloatRect bodyBound;
    
    //if the head collides with one of the body nodes true is returned
    CNode *temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    //if new head is created outside the window(player crashed into border) true is returned
    if( this->head->nodePosX < 0|
        this->head->nodePosX >= 1000|
        this->head->nodePosY < 0|
        this->head->nodePosY >= 1000) newInstance = GameOverMenu;

    //if the head collides with the food 
    if(headBound.intersects(foodBound))
    {
        temp->changeText(snakeState, true);
        //food gets relocated
        food.gotEaten(head);
        
        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            bodyBound = temp->node.getGlobalBounds();
            if(headBound.intersects(bodyBound)) newInstance = GameOverMenu;
        }
    }
    else
    {
        if(temp->prev->prev != NULL) temp->prev->changeText(snakeState, true);
        //tail gests removed only when no food is eaten (snake grows)
        this->removeTail();

        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            bodyBound = temp->node.getGlobalBounds();
            if(headBound.intersects(bodyBound)) newInstance = GameOverMenu;
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
void CSnake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{   
    //draw each nodes circle from back to front
    CNode *temp = tail;
    while(temp != NULL)
    {
        target.draw(temp->node);
        temp = temp->prev;
    }
}

//returns state(direction) of snake
SnakeState CSnake::getState()
{
    return this->snakeState;
}

//returns whether snake changed already in current tick
bool CSnake::getChangedThisTick()
{
    return this->changedThisTick;
}

//sets new state(new direction) and sets changedState to true
void CSnake::setState(SnakeState newState)
{
    this->snakeState = newState;
    this->changedThisTick = true;
}

//sets changedState to parameter
void CSnake::setChangedThisTick(bool changed)
{
    this->changedThisTick = changed;
}



