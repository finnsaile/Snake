#include "../headers/CResources.hpp"
#include <iostream>


CResources CResources::m_instance;

CResources::CResources() :
DATA_PATH("/Users/finnsaile/Documents/CPP/OwnProjekts/SFML/Snake/resources/")
{
    m_head_w.loadFromFile(DATA_PATH + "Snake/SnakeHeadW.png");
    m_head_a.loadFromFile(DATA_PATH + "Snake/SnakeHeadA.png");
    m_head_s.loadFromFile(DATA_PATH + "Snake/SnakeHeadS.png");
    m_head_d.loadFromFile(DATA_PATH + "Snake/SnakeHeadD.png");

    m_body_ws.loadFromFile(DATA_PATH + "Snake/SnakeBodyWS.png");
    m_body_ad.loadFromFile(DATA_PATH + "Snake/SnakeBodyAD.png");
    m_body_aw.loadFromFile(DATA_PATH + "Snake/SnakeBodyAW.png");
    m_body_dw.loadFromFile(DATA_PATH + "Snake/SnakeBodyDW.png");
    m_body_as.loadFromFile(DATA_PATH + "Snake/SnakeBodyAS.png");
    m_body_ds.loadFromFile(DATA_PATH + "Snake/SnakeBodyDS.png");

    m_tail_w.loadFromFile(DATA_PATH + "Snake/SnakeTailW.png");
    m_tail_a.loadFromFile(DATA_PATH + "Snake/SnakeTailA.png");
    m_tail_s.loadFromFile(DATA_PATH + "Snake/SnakeTailS.png");
    m_tail_d.loadFromFile(DATA_PATH + "Snake/SnakeTailD.png");
}

CResources& CResources::getInstance()
{
    return m_instance;
}