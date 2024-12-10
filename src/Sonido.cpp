#include "../include/Sonido.hpp"

Sonido::Sonido() {
    if (!Musica.openFromFile("../data/MusicaFondo.ogg")) {
        cout << "Error al cargar música de fondo" << endl;
    }
    Musica.setLoop(true);
    Musica.setVolume(15);
    
    if (!BufferSonidoLinea.loadFromFile("../data/NuevaLinea.ogg")) {
        cout << "Error al cargar sonido de línea" << endl;
    }
    
    if (!BufferSonidoNuevoPuntaje.loadFromFile("../data/ChillGuy.ogg")) {
        cout << "Error al cargar sonido de nuevo puntaje" << endl;
    }
    
    if (!BufferSonidoFinJuego.loadFromFile("../data/ChillGuy.ogg")) {
        cout << "Error al cargar sonido de fin de juego" << endl;
    }
    
    SonidoLinea.setBuffer(BufferSonidoLinea);
    SonidoNuevoPuntaje.setBuffer(BufferSonidoNuevoPuntaje);
    SonidoFinJuego.setBuffer(BufferSonidoFinJuego);
}

void Sonido::ReproducirMusica() {
    Musica.play();
}

void Sonido::PausarMusica() {
    Musica.pause();
}

void Sonido::ReproducirLinea() {
    SonidoLinea.play();
}

void Sonido::ReproducirNuevoPuntaje() {
    SonidoNuevoPuntaje.play();
}

void Sonido::ReproducirFinJuego() {
    SonidoFinJuego.play();
}
