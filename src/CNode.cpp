#include "../headers/CNode.hpp"
#include <iostream>

//constructor initializes nodeposition and next pointer
CNode::CNode(int posY, int posX, SnakeState snakeState):
nodePosX(posX),
nodePosY(posY),
nodeState(snakeState),
next(NULL)
{
    //dependent on direction load correct head node
    switch(snakeState)
    {
        case W: nodeTextureHead.loadFromFile(dataPath + "Snake/SnakeHeadW.png"); break;
        case A: nodeTextureHead.loadFromFile(dataPath + "Snake/SnakeHeadA.png"); break;
        case S: nodeTextureHead.loadFromFile(dataPath + "Snake/SnakeHeadS.png"); break;
        case D: nodeTextureHead.loadFromFile(dataPath + "Snake/SnakeHeadD.png"); break;
    }
    //set head node
    //set origin top left and set poition
    node.setTextureRect(sf::IntRect(0, 0, 40, 40));
    node.setTexture(nodeTextureHead);
    node.setOrigin(sf::Vector2f(0,0));
    node.setPosition(posX, posY);
        
}

//function to change texture once node isn't head anymore
void CNode::changeText(SnakeState snakeState, bool tailBool)
{
    if(tailBool == false)
    {
        if(snakeState != nodeState)
        {
            if(snakeState == A && nodeState == W || snakeState == S && nodeState == D) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyAW.png");
            else if(snakeState == D && nodeState == W || snakeState == S && nodeState == A) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyDW.png");
            else if(snakeState == A && nodeState == S || snakeState == W && nodeState == D) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyAS.png");
            else if(snakeState == D && nodeState == S || snakeState == W && nodeState == A) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyDS.png");
        }
        else if(snakeState == nodeState)
        {
            if(nodeState == W || nodeState == S) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyWS.png");
            else if (nodeState == A || nodeState == D) nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeBodyAD.png");
        }       
    }
    else
    {
        if (prev != NULL && (nodeState != prev->nodeState))
        {
            switch(prev->nodeState)
            {
                case W: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailW.png"); break;
                case A: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailA.png"); break;
                case S: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailS.png"); break;
                case D: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailD.png"); break;
            }
        }
        else
        {
            switch(nodeState)
            {
                case W: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailW.png"); break;
                case A: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailA.png"); break;
                case S: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailS.png"); break;
                case D: nodeTextureBody.loadFromFile(dataPath + "Snake/SnakeTailD.png"); break;
            }
        }
    }

    node.setTexture(nodeTextureBody);
}