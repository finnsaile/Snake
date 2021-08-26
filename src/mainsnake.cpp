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
    RenderWindow render_window(VideoMode(WIN_SIZE, WIN_SIZE), "Snake", Style::Titlebar | Style::Close);
    render_window.setVerticalSyncEnabled(false);
    render_window.setFramerateLimit(144);
    render_window.setKeyRepeatEnabled(false); 
    //create window object
    CWindow window;
    while(render_window.isOpen())
    {
        //game tick from window object
        window.windowTick(render_window);
        
        //clear, draw and display window object
        render_window.clear(Color (169,169,169));
        render_window.draw(window);
        render_window.display();
    }    
}
