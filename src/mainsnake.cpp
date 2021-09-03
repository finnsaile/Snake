#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CWindow.hpp"
#include "../headers/CResources.hpp"

#define TODO_LIST_

#ifdef TODO_LIST
#warning TODO Music Player
#warning TODO Init Length Setting
#warning TODO Make Difficulty Slider Textures
#warning TODO Fun Mode/Toggle Wall And Self Crash
#warning TODO ???Apple Slider???
#endif


#define WIN_SIZE 1000

using namespace sf;

int main(int argc, char* argv[])
{   
    CResources& resource = CResources::getInstance();
    //initialize time 
    srand(time(NULL));
    //create window with VSync
    RenderWindow render_window(VideoMode(WIN_SIZE, WIN_SIZE), "Snake", Style::Titlebar | Style::Close);
    render_window.setIcon(resource.m_snake_icon.getSize().x, resource.m_snake_icon.getSize().y, resource.m_snake_icon.getPixelsPtr());
    render_window.setVerticalSyncEnabled(true);
    //render_window.setFramerateLimit(60);
    render_window.setKeyRepeatEnabled(false); 
    //create window object
    CWindow window;
    while(render_window.isOpen())
    {
        //game tick from window object
        window.windowTick(render_window);
        
        //clear, draw and display window object
        render_window.clear(Color(169,169,169));
        render_window.draw(window);
        render_window.display();
    }    
}
