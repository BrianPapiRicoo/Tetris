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
    Texture TexturaFondo;
    Texture TexturaChillGuy;
    Texture TexturaRotate;
    Sprite SpriteFondo;
    Sprite SpriteChillGuy;
    Sprite SpriteRotate;
    Texture TexturaSpeed;
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
    SpriteSpeed.setPosition(205, 290); 
    SpriteSpeed.setScale(0.17f, 0.17f);

    tablero.InstalarPartes();

    int derecha = 0, izquierda = 0, arriba = 0;
    int puntaje = 0;
    int maxPuntaje = 0;

    // Leer el puntaje máximo
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
                        SpriteChillGuy.setPosition(50, 180);
                        SpriteChillGuy.setScale(0.35f, 0.35f);
                        sonido.ReproducirNuevoPuntaje();
                    } else {
                        SpriteChillGuy.setPosition(50, 180);
                        SpriteChillGuy.setScale(0.35f, 0.35f);
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

        // Dibujar fondo
        window.draw(SpriteFondo);

        // Dibujar sprites
        window.draw(SpriteRotate);
        window.draw(SpriteSpeed);

        window.draw(tablero);
        window.draw(iu);
        window.draw(SpriteChillGuy);
        window.display();
    }

    return 0;
}
