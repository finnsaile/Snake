#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CSnake.hpp"
#include "../headers/CGrid.hpp"
#include "../headers/CGame.hpp"
#include "../headers/CWindow.hpp"

int main(int argc, char* argv[])
{
    //initialize time 
    srand(time(NULL));

    //create window with VSync
    sf::RenderWindow gamewindow(sf::VideoMode(1000, 1000), "Snake", sf::Style::Titlebar | sf::Style::Close);
    gamewindow.setVerticalSyncEnabled(true);
    gamewindow.setKeyRepeatEnabled(false); //maybe change
    //create window object
    CWindow window;
    while(gamewindow.isOpen())
    {
        //game tick from window object
        window.windowTick(gamewindow);
        
        //clear, draw and display window object
        gamewindow.clear(sf::Color (169,169,169));
        gamewindow.draw(window);
        gamewindow.display();
    }    
}
