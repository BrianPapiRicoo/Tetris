#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ctablero.hpp"
using namespace std; 
using namespace sf; 

int main()
{
    Ctablero tablero; 
    RenderWindow window(VideoMode(400,400),"Tetris");
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed) window.close();
        }
        tablero.UpdateTableroColor();
        window.clear(Color(20,20,20));
        window.draw(tablero)
        window.display();
    }
    return 0; 
}