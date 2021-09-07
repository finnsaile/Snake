#include "../headers/CSnake.hpp"

#define TILE_SIZE 40
#define GRID_SIZE 25
#define MAX_INIT_LENGTH (12 * 13)
using namespace sf;
using namespace std;

//constructor takes new head position as argument 
//and initializes new node as head, snakeState(direction) and changedState
CSnake::CSnake(int init_x, int init_y, unsigned int length, unsigned int food_amount): 
head(new CNode(init_y, init_x, W)),
m_settings_values(CSettingsValues::getInstance())
{  
    //tail = head (only 1 node exists)
    head->prev = NULL;
    tail = head;
    initSnake(length);
    initFood(food_amount);
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
bool CSnake::addHead(WindowInstance& new_instance)
{
    //change texture of old head to normal body texture

    head->changeTexture(m_snake_state, false);

    int temp_y = head->m_node_pos_y;
    int temp_x = head->m_node_pos_x;
    switch(m_snake_state)
    {
        //position of new head gets calculated using old heads position and moving direction
        case W: temp_y -= TILE_SIZE; break;
        case A: temp_x -= TILE_SIZE; break;
        case S: temp_y += TILE_SIZE; break;
        case D: temp_x += TILE_SIZE; break;
    }

    //** CRASH WHEN HITTING WALL **//
    //if new head is created outside the window(player crashed into border) true is returned
    if( temp_x < 0|
        temp_x >= 1000|
        temp_y < 0|
        temp_y >= 1000) new_instance = GameOverMenu;

    //** DON'T CRASH WHEN HITTING WALL **//
    // if(temp_x < 0) temp_x += 1000;
    // else if(temp_x >= 1000) temp_x -= 1000;
    // else if(temp_y < 0) temp_y += 1000;
    // else if(temp_y >= 1000) temp_y -= 1000;

    //new head gets created at calculated coordinates. All pointers are set to link the head to the list
    head->prev = new CNode(temp_y, temp_x, m_snake_state);
    head->prev->next = head;
    head = head->prev;
    head->prev = NULL;
    

    //bounds for head and body to check for collition when creating the new head
    FloatRect head_bound = head->m_node.getGlobalBounds();
    FloatRect body_bound;

    //if the head collides with the food 
    if(checkFoodBounds(head_bound))
    {
        tail->changeTexture(m_snake_state, true);
        return true;
    }
    else
    {
        if(tail->prev->prev != NULL) tail->prev->changeTexture(m_snake_state, true);
        //tail gets removed only when no food is eaten (snake grows)
        removeTail();

        //** GAME OVER WHEN SNAKE HITS SNAKE **//
        CNode* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            body_bound = temp->m_node.getGlobalBounds();
            if(head_bound.intersects(body_bound)) new_instance = GameOverMenu;
        }
    }
    return false;
}

bool CSnake::checkFoodBounds(FloatRect& head_bound)
{
    bool return_value = false;
    for_each(m_food_vec.begin(), m_food_vec.end(), 
        [&](CFood& food) 
        {
            if(food.getFoodBounds().intersects(head_bound))
            {
                food.gotEaten(head, m_food_vec);
                return_value = true;
            }

        });
    return return_value;
}
void CSnake::initSnake(unsigned int length)
{   
    unsigned int tail_length = length - 1;
    int delta_y, delta_x;
    CNode* temp = head;
    SnakeState state;

    if(tail_length > MAX_INIT_LENGTH) tail_length = MAX_INIT_LENGTH;

    for(int i = 0; i < tail_length; i++)
    {   
        delta_x = static_cast<int>(i / 12);

        if((delta_x % 2) == 1) 
        {
            delta_y = 12 - ( (i % 12));
            if(delta_y == 1) state = A;
            else state = S;
        }       
        else 
        {
            delta_y = (1 + (i % 12));
            if(delta_y == 12) state = A;
            else state = W;
        }

        temp->next = new CNode(head->m_node_pos_y + delta_y * TILE_SIZE, head->m_node_pos_x + delta_x * TILE_SIZE, state);
        temp->next->prev = temp;
        temp->next->next = NULL;
        temp = temp->next;
        temp->changeTexture(temp->prev->m_node_state, false);
    }
    temp->changeTexture(W, true);
    tail = temp;
}

void CSnake::initFood(const unsigned int food_amount)
{
    for(int i = 0; i < food_amount; i++)
    {
        m_food_vec.push_back(CFood(*m_settings_values.getDifficulty(), this->head, m_food_vec));
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

    for_each(m_food_vec.begin(), m_food_vec.end(), [&](CFood food) {target.draw(food);});
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

CNode* CSnake::getHead()
{
    return head;
}


