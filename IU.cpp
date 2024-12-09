#include "IU.hpp"

IU::IU() {
    if (!Fuente.loadFromFile("Animal.otf")) {
        cout << "Error al cargar fuente de texto" << endl;
    }

    
    TextoTituloTetrix.setFont(Fuente);
    TextoTituloTetrix.setPosition(Vector2f(208, 10)); 
    TextoTituloTetrix.setString("TETRIX");
    TextoTituloTetrix.setCharacterSize(50); 
    TextoTituloTetrix.setFillColor(Color::Red); 

    TextoTituloPuntaje.setFont(Fuente);
    TextoTituloPuntaje.setFillColor(Color::White);
    TextoTituloPuntaje.setPosition(Vector2f(245, 80));
    TextoTituloPuntaje.setString("Score:");

    TextoTituloMaxPuntaje.setFont(Fuente);
    TextoTituloMaxPuntaje.setFillColor(Color::White);
    TextoTituloMaxPuntaje.setPosition(Vector2f(240, 220));
    TextoTituloMaxPuntaje.setString("Max Score:");
    TextoTituloMaxPuntaje.setCharacterSize(20);

    TextoPuntaje.setFont(Fuente);
    TextoPuntaje.setFillColor(Color::White);
    TextoPuntaje.setPosition(Vector2f(260, 120));

    TextoMaxPuntaje.setFont(Fuente);
    TextoMaxPuntaje.setFillColor(Color::White);
    TextoMaxPuntaje.setPosition(Vector2f(270, 245));

    TextoAutor.setFont(Fuente);
    TextoAutor.setFillColor(Color::White);
    TextoAutor.setPosition(Vector2f(239, 370));
    TextoAutor.setString("BrianP Company");
    TextoAutor.setCharacterSize(15);

    TextoFinJuego.setFont(Fuente);
    TextoFinJuego.setFillColor(Color::White);
    TextoFinJuego.setPosition(Vector2f(25, 150));
    TextoFinJuego.setString("Game Over ");
    TextoFinJuego.setCharacterSize(25);

    TextoNuevoPuntaje.setFont(Fuente);
    TextoNuevoPuntaje.setFillColor(Color::White);
    TextoNuevoPuntaje.setPosition(Vector2f(8, 150));
    TextoNuevoPuntaje.setString("New Score");
    TextoNuevoPuntaje.setCharacterSize(25);
}

void IU::ActualizarColorTetrix() {
    static int contador = 0;
    static int frameDelay = 30; 

    if (contador >= frameDelay) {
      
        static int colorIndex = 0;
        switch (colorIndex % 3) {
            case 0: TextoTituloTetrix.setFillColor(Color::Red); break;
            case 1: TextoTituloTetrix.setFillColor(Color::Green); break;
            case 2: TextoTituloTetrix.setFillColor(Color::Blue); break;
        }
        colorIndex++;
        contador = 0; 
    } else {
        contador++; 
    }
}

void IU::EstablecerPuntaje(int x) {
    if (x <= 9) TextoPuntaje.setString("000" + to_string(x));
    else if (x <= 99) TextoPuntaje.setString("00" + to_string(x));
    else if (x <= 999) TextoPuntaje.setString("0" + to_string(x));
    else if (x <= 9999) TextoPuntaje.setString(to_string(x));
    else TextoPuntaje.setString("9999");
}

void IU::EstablecerMaxPuntaje(int x) {
    if (x <= 9) TextoMaxPuntaje.setString("000" + to_string(x));
    else if (x <= 99) TextoMaxPuntaje.setString("00" + to_string(x));
    else if (x <= 999) TextoMaxPuntaje.setString("0" + to_string(x));
    else if (x <= 9999) TextoMaxPuntaje.setString(to_string(x));
    else TextoMaxPuntaje.setString("9999");
}

void IU::FinDeJuego() {
    FinJuego = true;
}

void IU::NuevoPuntajeMarcado() {
    NuevoPuntaje = true;
}

void IU::draw(RenderTarget &target, RenderStates states) const {
    target.draw(TextoTituloTetrix, states); // Dibuja el texto "TETRIX"
    target.draw(TextoTituloPuntaje, states);
    target.draw(TextoPuntaje, states);
    target.draw(TextoTituloMaxPuntaje, states);
    target.draw(TextoMaxPuntaje, states);
    target.draw(TextoAutor, states);
    if (FinJuego) target.draw(TextoFinJuego, states);
    if (NuevoPuntaje) target.draw(TextoNuevoPuntaje, states);
}
