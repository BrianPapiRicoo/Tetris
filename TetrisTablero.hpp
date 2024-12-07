#include "TetrisPartes.hpp"
#include <SFML/Graphics.hpp>
#include <cstring>
#include <time.h>

class TetrisTablero : public sf::Drawable
{
private:
    int tablero[20][10];
    sf::RectangleShape tableroShape[20][10]; 
    TetrisPartes partes; 
    int indX, indY; 
    int indNewParte, indColorNewParte;
    sf::Color NewParteColor; 
    int timer = 0; 
    int limite_de_timer = 10; 
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override; 

public:
    TetrisTablero(); 

    void ActualizarColoresTablero(); 
    bool ActualizarTablero(); 
    bool InstalarPartes(); 
    void ActualizarLimiteTimer(int limite); 
    void RotarParte(); 
    void MoverDerecha(); 
    void MoverIzquierda(); 
    int RevisarLineas(); 
    void LimpiarTablero(); 
};