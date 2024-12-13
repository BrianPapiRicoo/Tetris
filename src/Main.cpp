#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/TetrisTablero.hpp"
#include "../include/IU.hpp"
#include "../include/Sonido.hpp"
#include "../include/MenuFinJuego.hpp"
#include <fstream>

using namespace std;
using namespace sf;

// Constantes para la posición y escala originales del sprite ChillGuy
const Vector2f CHILLGUY_POS_ORIGINAL(265, 145);
const Vector2f CHILLGUY_ESCALA_ORIGINAL(0.27f, 0.27f);

int main() {
    TetrisTablero tablero;
    IU iu;
    Sonido sonido;
    MenuFinJuego menuFinJuego;

    Texture TexturaFondo;
    Texture TexturaChillGuy;
    Texture TexturaRotate;
    Texture TexturaSpeed;

    Sprite SpriteFondo;
    Sprite SpriteChillGuy;
    Sprite SpriteRotate;
    Sprite SpriteSpeed;

    RenderWindow window(VideoMode(400, 400), "Tetrix");
    window.setFramerateLimit(60);

    // Fondo
    if (!TexturaFondo.loadFromFile("../data/Fondo.jpg")) {
        cout << "Error al cargar la imagen 'Fondo.jpg'" << endl;
        return -1;
    }
    SpriteFondo.setTexture(TexturaFondo);
    SpriteFondo.setPosition(0, 0);
    SpriteFondo.setScale(400.0f / TexturaFondo.getSize().x, 400.0f / TexturaFondo.getSize().y);

    // ChillGuy
    if (!TexturaChillGuy.loadFromFile("../data/ChillGuyP.png")) {
        cout << "Error al cargar la imagen 'ChillGuyP.png'" << endl;
        return -1;
    }
    SpriteChillGuy.setTexture(TexturaChillGuy);
    SpriteChillGuy.setPosition(CHILLGUY_POS_ORIGINAL);
    SpriteChillGuy.setScale(CHILLGUY_ESCALA_ORIGINAL);

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
    SpriteSpeed.setPosition(205, 290);
    SpriteSpeed.setScale(0.17f, 0.17f);

    tablero.InstalarPartes();

    int derecha = 0, izquierda = 0, arriba = 0;
    int puntaje = 0;
    int maxPuntaje = 0;

    // Leer el puntaje maximo
    ifstream entrada("../data/MaxPuntaje.txt");
    entrada >> maxPuntaje;

    iu.EstablecerMaxPuntaje(maxPuntaje);
    iu.EstablecerPuntaje(puntaje);
    bool live = true;
    bool mostrandoMenu = false; 
    bool esNuevoMaxPuntaje = false; 
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
                tablero.ActualizarLimiteTimer(5); // Más velocidad
            } else {
                tablero.ActualizarLimiteTimer(30); // Velocidad normal
            }

            // Derecha
            if (Keyboard::isKeyPressed(Keyboard::Right) && !derecha) {
                tablero.MoverDerecha();
                derecha = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
                derecha = false;
            }

            // Izquierda
            if (Keyboard::isKeyPressed(Keyboard::Left) && !izquierda) {
                tablero.MoverIzquierda();
                izquierda = true;
            } else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
                izquierda = false;
            }

            // Actualizar tablero
            if (tablero.ActualizarTablero()) {
                if (!tablero.InstalarPartes()) {
                    live = false;
                    mostrandoMenu = true; // Activar el menu
                    tablero.LimpiarTablero();
                    sonido.PausarMusica();

                    if (puntaje > maxPuntaje) {
                        ofstream salida("../data/MaxPuntaje.txt");
                        salida << puntaje;
                        maxPuntaje = puntaje; // Actualizar maxPuntaje
                        esNuevoMaxPuntaje = true; //nuevo puntaje maximo
                        sonido.ReproducirNuevoPuntaje();
                    } else {
                        esNuevoMaxPuntaje = false;
                        sonido.ReproducirFinJuego();
                    }
                }
            }

            tablero.ActualizarColoresTablero();

           
            int nuevoPuntaje = tablero.RevisarLineas() * 5;
            puntaje += nuevoPuntaje;
            iu.EstablecerPuntaje(puntaje);

            if (nuevoPuntaje > 0) {
                sonido.ReproducirLinea();
            }
        } else if (mostrandoMenu) {
            // Mostrar el menu
            window.clear(Color(20, 20, 20));

        if (esNuevoMaxPuntaje) {
            menuFinJuego.MostrarMensaje(window, "New Max Score!", sf::Color::Green, 40, maxPuntaje);
        } else {
            menuFinJuego.MostrarMensaje(window, "Game Over", sf::Color::Red, 50);
        }

            menuFinJuego.MostrarOpciones(window);
            window.display();

            if (Keyboard::isKeyPressed(Keyboard::LShift)) {
                mostrandoMenu = false;
                live = true;

                sonido.DetenerEfectos();

                tablero.LimpiarTablero();
                puntaje = 0;
                iu.EstablecerPuntaje(0);
                iu.EstablecerMaxPuntaje(maxPuntaje);

                
                SpriteChillGuy.setPosition(CHILLGUY_POS_ORIGINAL);
                SpriteChillGuy.setScale(CHILLGUY_ESCALA_ORIGINAL);

                iu.ReiniciarEstado(); 
                sonido.ReproducirMusica();
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                window.close();
            }
        }

        if (live) {
            iu.ActualizarColorTetrix();
            window.clear(Color(20, 20, 20));

            
            window.draw(SpriteFondo);
            window.draw(SpriteRotate);
            window.draw(SpriteSpeed);
            window.draw(tablero);
            window.draw(iu);
            window.draw(SpriteChillGuy);

            window.display();
        }
    }

    return 0;
}
