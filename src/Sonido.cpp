#include "../include/Sonido.hpp"

Sonido::Sonido() {
    if (!Musica.openFromFile("../data/MusicaFondo.ogg")) {
        cout << "Error al cargar musica de fondo" << endl;
    }
    Musica.setLoop(true);
    Musica.setVolume(15);

    if (!BufferSonidoLinea.loadFromFile("../data/NuevaLinea.ogg")) {
        cout << "Error al cargar sonido de linea" << endl;
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

    // Configuración inicial de volúmenes
    SonidoLinea.setVolume(100);
    SonidoNuevoPuntaje.setVolume(100);
    SonidoFinJuego.setVolume(100);
}

void Sonido::ReproducirMusica() {
    if (Musica.getStatus() != sf::SoundSource::Playing) {
        Musica.play();
    }
}

void Sonido::PausarMusica() {
    if (Musica.getStatus() == sf::SoundSource::Playing) {
        Musica.pause();
    }
}

void Sonido::DetenerMusica() {
    Musica.stop();
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

void Sonido::DetenerEfectos() {
    SonidoLinea.stop();
    SonidoNuevoPuntaje.stop();
    SonidoFinJuego.stop();
}

void Sonido::EstablecerVolumenMusica(float volumen) {
    Musica.setVolume(volumen);
}

void Sonido::EstablecerVolumenEfectos(float volumen) {
    SonidoLinea.setVolume(volumen);
    SonidoNuevoPuntaje.setVolume(volumen);
    SonidoFinJuego.setVolume(volumen);
}