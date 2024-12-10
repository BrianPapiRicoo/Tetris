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
    Texture TexturaChillGuy;
    Texture TexturaRotate;
    Sprite SpriteChillGuy;
    Sprite SpriteRotate;
    Texture TexturaSpeed;
    Sprite SpriteSpeed;

    RenderWindow window(VideoMode(400, 400), "Tetrix");
    window.setFramerateLimit(60);

    tablero.InstalarPartes();

    int derecha = 0, izquierda = 0, arriba = 0;
    int puntaje = 0;
    int maxPuntaje = 0;

    // ChillGuy
    if (!TexturaChillGuy.loadFromFile("../data/ChillGuyP.png")) {
        cout << "Error al cargar la imagen 'ChillGuyP.png'" << endl;
        return -1;
    }
    SpriteChillGuy.setTexture(TexturaChillGuy);
    SpriteChillGuy.setPosition(265, 145);
    SpriteChillGuy.setScale(0.27f, 0.27f);

    // Rotate
    if (!TexturaRotate.loadFromFile("../data/rotate.png")) {
        cout << "Error al cargar la imagen 'rotate.png'" << endl;
        return -1;
    }
    SpriteRotate.setTexture(TexturaRotate);
    SpriteRotate.setPosition(300, 288); 
    SpriteRotate.setScale(0.17f, 0.17f);

    // Speed
    if (!TexturaSpeed.loadFromFile("../data/Speed.png")) {
        cout << "Error al cargar la imagen 'Speed.png'" << endl;
        return -1;
    }
    SpriteSpeed.setTexture(TexturaSpeed);
    SpriteSpeed.setPosition(205, 290); // Posicion ajustada
    SpriteSpeed.setScale(0.17f, 0.17f);

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
            // Revisar líneas y actualizar puntaje
            int nuevoPuntaje = tablero.RevisarLineas() * 5;
            puntaje += nuevoPuntaje;
            iu.EstablecerPuntaje(puntaje);
            // Sonido línea
            if (nuevoPuntaje > 0) {
                sonido.ReproducirLinea();
            }
        }
        iu.ActualizarColorTetrix();
        window.clear(Color(20, 20, 20));

        // Dibujar sprites
        window.draw(SpriteChillGuy);
        window.draw(SpriteRotate);
        window.draw(SpriteSpeed);

        window.draw(tablero);
        window.draw(iu);
        window.display();
    }

    return 0;
}
