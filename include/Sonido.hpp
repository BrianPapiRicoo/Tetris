#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Sonido {
    private:
        Music Musica;
        Sound SonidoLinea;
        Sound SonidoNuevoPuntaje;
        Sound SonidoFinJuego;
        SoundBuffer BufferSonidoLinea;
        SoundBuffer BufferSonidoNuevoPuntaje;
        SoundBuffer BufferSonidoFinJuego;

    public:
        Sonido();
        void ReproducirMusica();
        void PausarMusica();
        void ReproducirLinea();
        void ReproducirFinJuego();
        void ReproducirNuevoPuntaje();
};
