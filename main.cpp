#include <iostream>
#include <SFML/Graphics.hpp>
#include "TetrisTablero.hpp"
#include "IU.hpp"
#include <fstream>

using namespace std;
using namespace sf;

int main() {
    TetrisTablero tablero;
    IU iu;

    RenderWindow window(VideoMode(400, 400), "Tetrix");
    window.setFramerateLimit(60);

    tablero.InstalarPartes();

    int derecha = 0, izquierda = 0, arriba = 0;
    int puntaje = 0;
    int maxPuntaje = 0;

    // Leer el puntaje maximo 
    ifstream entrada("MaxPuntaje.txt");
    entrada >> maxPuntaje;
    iu.EstablecerMaxPuntaje(maxPuntaje);
    iu.EstablecerPuntaje(puntaje);

    bool enVivo = true;

    while (window.isOpen()) {
        Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == Event::Closed) window.close();
        }

        if (enVivo) {
            // Rotar
            if (Keyboard::isKeyPressed(Keyboard::Up) && !arriba) {
                tablero.RotarParte();
                arriba = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
                arriba = false;
            }

            // Acelerar caida
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                tablero.ActualizarLimiteTimer(5); // Baja más rápido
            } else {
                tablero.ActualizarLimiteTimer(30); // Velocidad normal
            }

            // Derecha
            if (Keyboard::isKeyPressed(Keyboard::Right) && !derecha) {
                tablero.MoverDerecha();
                derecha = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
                derecha = false;
            } else if (Keyboard::isKeyPressed(Keyboard::Right) && derecha) {
                derecha++;
                if (derecha == 6) derecha = 0;
            }

            // Izquierda
            if (Keyboard::isKeyPressed(Keyboard::Left) && !izquierda) {
                tablero.MoverIzquierda();
                izquierda = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
                izquierda = false;
            } else if (Keyboard::isKeyPressed(Keyboard::Left) && izquierda) {
                izquierda++;
                if (izquierda == 6) izquierda = 0;
            }

            // Actualizar tablero
            if (tablero.ActualizarTablero()) {
                if (!tablero.InstalarPartes()) {
                    enVivo = false;
                    tablero.LimpiarTablero();

                    // Verificar si hay nuevo puntaje maximo
                    if (puntaje > maxPuntaje) {
                        iu.NuevoPuntajeMarcado();
                        ofstream salida("MaxPuntaje.txt");
                        salida << puntaje;
                    } else {
                        iu.FinDeJuego();
                    }
                }
            }
            tablero.ActualizarColoresTablero();

            // Revisar lineas completadas y actualizar puntaje
            int nuevoPuntaje = tablero.RevisarLineas() * 5;
            puntaje += nuevoPuntaje;
            iu.EstablecerPuntaje(puntaje);
        }

        // Actualizar el color del texto "TETRIX"
        iu.ActualizarColorTetrix();

        // Dibujar en la ventana
        window.clear(Color(20, 20, 20));
        window.draw(tablero);
        window.draw(iu);
        window.display();
    }

    return 0;
}
