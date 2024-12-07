#include <iostream>
#include <SFML/Graphics.hpp>
#include "TetrisTablero.hpp"

int main()
{
    TetrisTablero tablero;


    sf::RenderWindow window(sf::VideoMode(400, 400), "Tetris");
    window.setFramerateLimit(60);

    tablero.InstalarPartes();
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(tablero.ActualizarTablero())
        {
            tablero.InstalarPartes();
        }
        tablero.ActualizarColoresTablero();
        window.clear(sf::Color(20, 20, 20));
        window.draw(tablero);
        window.display();
    }

    return 0;
}