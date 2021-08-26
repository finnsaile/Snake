#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CWindow.hpp"

#define WIN_SIZE 1000

using namespace sf;


int main(int argc, char* argv[])
{
    //initialize time 
    srand(time(NULL));

    //create window with VSync
    RenderWindow gamewindow(VideoMode(WIN_SIZE, WIN_SIZE), "Snake", Style::Titlebar | Style::Close);
    gamewindow.setVerticalSyncEnabled(true);
    gamewindow.setKeyRepeatEnabled(false); 
    //create window object
    CWindow window;
    while(gamewindow.isOpen())
    {
        //game tick from window object
        window.windowTick(gamewindow);
        
        //clear, draw and display window object
        gamewindow.clear(Color (169,169,169));
        gamewindow.draw(window);
        gamewindow.display();
    }    
}
