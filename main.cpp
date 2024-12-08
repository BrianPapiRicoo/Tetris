#include <iostream>
#include <SFML/Graphics.hpp>
#include "TetrisTablero.hpp"
using namespace std;
using namespace sf;
int main()
{
    TetrisTablero tablero;

    int derecha = 0, arriba = 0, izquierda = 0; 
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
    bool enVivo = true;

    if (enVivo) {
        //Rotar
        if (Keyboard::isKeyPressed(Keyboard::Up) && !arriba) {
            tablero.RotarParte();
            arriba = true;
        } else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
            arriba = false;
        }
        
        //Acelerar Caida
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            // Baja mas rapido
            tablero.ActualizarLimiteTimer(5); 
        } else {
            // Velocidad normal
            tablero.ActualizarLimiteTimer(30); 
        }
        
        //Derecha
        if (Keyboard::isKeyPressed(Keyboard::Right) && !derecha) {
            tablero.MoverDerecha();
            derecha = true;
        } else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
            derecha = false;
        } else if (Keyboard::isKeyPressed(Keyboard::Right) && derecha) {
            derecha++;
            if (derecha == 6) derecha = 0;
        }
        
        //Izquierda
        if (Keyboard::isKeyPressed(Keyboard::Left) && !izquierda) {
            tablero.MoverIzquierda();
            izquierda = true;
        } else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
            izquierda = false;
        } else if (Keyboard::isKeyPressed(Keyboard::Left) && izquierda) {
            izquierda++;
            if (izquierda == 6) izquierda = 0;
        }
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