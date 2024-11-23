#include "Cpartes.hpp"
#include <SFML/Graphics.hpp>
#include <cstring>
#include <time.h>

class Ctablero : public sf::Drawable
{
private:
    int tablero[20][10]; 
    sf::RectangleShape tableroShape[20][10]; 
    Cpartes partes; 
    int indX, indY; 
    int indNewParte, indColorNewParte;
    sf::Color NewParteColor;  
public:
    Ctablero();
    void UpdateTableroColor();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    bool InstalarPartes();
};
