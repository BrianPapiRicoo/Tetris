#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf; 
class Sonido {
private:
    sf::Music Musica;
    sf::SoundBuffer BufferSonidoLinea;
    sf::SoundBuffer BufferSonidoNuevoPuntaje;
    sf::SoundBuffer BufferSonidoFinJuego;
    sf::Sound SonidoLinea;
    sf::Sound SonidoNuevoPuntaje;
    sf::Sound SonidoFinJuego;

public:
    Sonido();
    void ReproducirMusica();
    void PausarMusica();
    void DetenerMusica(); 
    void ReproducirLinea();
    void ReproducirNuevoPuntaje();
    void ReproducirFinJuego();
    void DetenerEfectos(); 
    void EstablecerVolumenMusica(float volumen);
    void EstablecerVolumenEfectos(float volumen);
};