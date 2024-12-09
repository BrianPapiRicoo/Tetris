#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class IU : public Drawable {
    private:
        Font Fuente;
        Text TextoTituloPuntaje;
        Text TextoTituloTetrix;
        Text TextoPuntaje;
        Text TextoTituloMaxPuntaje;
        Text TextoMaxPuntaje;
        Text TextoAutor;
        Text TextoFinJuego;
        Text TextoNuevoPuntaje;
        bool NuevoPuntaje = false;
        bool FinJuego = false;

    public:
        IU();
        void EstablecerPuntaje(int);
        void EstablecerMaxPuntaje(int);
        void FinDeJuego();
        void NuevoPuntajeMarcado();
        void ActualizarColorTetrix();
        virtual void draw(RenderTarget& target, RenderStates states) const override;
};