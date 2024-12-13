#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MenuFinJuego {
private:
    sf::Font font;
    sf::Text mensaje;
    sf::Text maxScoreTexto;  
    sf::Text opcionReiniciar;
    sf::Text opcionSalir;

    sf::Texture chillGuyTexture;
    sf::Sprite chillGuySprite;

    sf::Texture shiftTexture;
    sf::Sprite shiftSprite;

    sf::Texture spaceTexture;
    sf::Sprite spaceSprite;

public:
    MenuFinJuego();
    void MostrarMensaje(sf::RenderWindow& window, const std::string& texto, const sf::Color& color, unsigned int size, int maxScore = -1);
    void MostrarOpciones(sf::RenderWindow& window);
    bool JuegoReiniciado();
    bool SalirDelJuego();
};
