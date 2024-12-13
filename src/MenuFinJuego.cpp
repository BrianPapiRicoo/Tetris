#include "../include/MenuFinJuego.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

MenuFinJuego::MenuFinJuego() {
    if (!font.loadFromFile("../data/Animal.otf")) {
        std::cout << "Error al cargar la fuente para el menú de fin de juego" << std::endl;
    }

    // Configurar el mensaje central
    mensaje.setFont(font);
    mensaje.setCharacterSize(50);
    mensaje.setFillColor(sf::Color::Red);
    mensaje.setOutlineThickness(1.5f);
    mensaje.setOutlineColor(sf::Color::Black);
    mensaje.setPosition(30, 20);

   
    maxScoreTexto.setFont(font);
    maxScoreTexto.setCharacterSize(25);
    maxScoreTexto.setFillColor(sf::Color::White);
    maxScoreTexto.setOutlineThickness(1.0f);
    maxScoreTexto.setOutlineColor(sf::Color::Black);
    maxScoreTexto.setPosition(100, 60);  

    // Configurar opciones
    opcionReiniciar.setFont(font);
    opcionReiniciar.setString("Restart");
    opcionReiniciar.setCharacterSize(20);
    opcionReiniciar.setFillColor(sf::Color::White);
    opcionReiniciar.setPosition(39, 120);

    opcionSalir.setFont(font);
    opcionSalir.setString("Exit");
    opcionSalir.setCharacterSize(20);
    opcionSalir.setFillColor(sf::Color::White);
    opcionSalir.setPosition(60, 210);

    //textura ChillGuy
    if (!chillGuyTexture.loadFromFile("../data/ChillGuyP.png")) {
        std::cout << "Error al cargar la textura 'ChillGuyP.png'" << std::endl;
    }
    chillGuySprite.setTexture(chillGuyTexture);
    chillGuySprite.setPosition(130, 70); // Posición inicial del sprite

    //Shift
    if (!shiftTexture.loadFromFile("../data/Shift.png")) {
        std::cout << "Error al cargar la textura 'Shift.png'" << std::endl;
    }
    shiftSprite.setTexture(shiftTexture);
    shiftSprite.setPosition(30, 150); 

    //Space
    if (!spaceTexture.loadFromFile("../data/Space.png")) {
        std::cout << "Error al cargar la textura 'Space.png'" << std::endl;
    }
    spaceSprite.setTexture(spaceTexture);
    spaceSprite.setPosition(30, 240); 
}

void MenuFinJuego::MostrarMensaje(sf::RenderWindow& window, const std::string& texto, const sf::Color& color, unsigned int size, int maxScore) {
    // Configurar el mensaje principal
    mensaje.setString(texto);
    mensaje.setFillColor(color);
    mensaje.setCharacterSize(size);
    window.draw(mensaje);
    if (maxScore != -1) {
        maxScoreTexto.setString("Max Score: " + std::to_string(maxScore));
        window.draw(maxScoreTexto);
    }

    //ChillGuy
    window.draw(chillGuySprite);
}

void MenuFinJuego::MostrarOpciones(sf::RenderWindow& window) {
   
    window.draw(opcionReiniciar);
    window.draw(shiftSprite);
    window.draw(opcionSalir);
    window.draw(spaceSprite);
}

bool MenuFinJuego::JuegoReiniciado() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}

bool MenuFinJuego::SalirDelJuego() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}
