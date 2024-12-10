#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/TetrisTablero.hpp"
#include "../include/IU.hpp"
#include "../include/Sonido.hpp"
#include <fstream>

using namespace std;
using namespace sf;

int main() {
    TetrisTablero tablero;
    IU iu;
    Sonido sonido;

    RenderWindow window(VideoMode(400, 400), "Tetrix");
    window.setFramerateLimit(60);

    tablero.InstalarPartes();

    int derecha = 0, izquierda = 0, arriba = 0;
    int puntaje = 0;
    int maxPuntaje = 0;

    //ChillGuy
    Texture texturaImagen;
    if (!texturaImagen.loadFromFile("../data/ChillGuyP.png")) {
        cout << "Error al cargar la imagen 'ChillGuyP.png'" << endl;
        return -1;
    }
    Sprite spriteImagen;
    spriteImagen.setTexture(texturaImagen);
    spriteImagen.setPosition(265, 277); 
    spriteImagen.setScale(0.3f, 0.3f);

    // Leer el puntaje maximo
    ifstream entrada("../data/MaxPuntaje.txt");
    entrada >> maxPuntaje;

    iu.EstablecerMaxPuntaje(maxPuntaje);
    iu.EstablecerPuntaje(puntaje);
    bool live = true;
    sonido.ReproducirMusica();

    while (window.isOpen()) {
        Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == Event::Closed) window.close();
        }

        if (live) {
            // Rotar
            if (Keyboard::isKeyPressed(Keyboard::Up) && !arriba) {
                tablero.RotarParte();
                arriba = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
                arriba = false;
            }

            // Acelerar
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                tablero.ActualizarLimiteTimer(5); // Mas velocidad
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
                    live = false;
                    tablero.LimpiarTablero();
                    sonido.PausarMusica();
                    if (puntaje > maxPuntaje) {
                        iu.NuevoPuntajeMarcado();
                        ofstream salida("../data/MaxPuntaje.txt");
                        salida << puntaje;
                        sonido.ReproducirNuevoPuntaje();
                    } else {
                        iu.FinDeJuego();
                        sonido.ReproducirFinJuego();
                    }
                }
            }
            tablero.ActualizarColoresTablero();
            // Revisar lineas y actualizar puntaje
            int nuevoPuntaje = tablero.RevisarLineas() * 5;
            puntaje += nuevoPuntaje;
            iu.EstablecerPuntaje(puntaje);
            // Sonido linea
            if (nuevoPuntaje > 0) {
                sonido.ReproducirLinea();
            }
        }
        iu.ActualizarColorTetrix();
        window.clear(Color(20, 20, 20));
        window.draw(spriteImagen); 
        window.draw(tablero);
        window.draw(iu);
        window.display();
    }

    return 0;
}
