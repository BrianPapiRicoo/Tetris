#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>

class Ctablero : public Drawable
{
    private:
    int tablero [20][10];
    RectangleShape tableroShape[20][10];
    public:
    Ctablero();
    void UpdateTableroColor();
    virtual void draw(RenderTarget&, RenderStates) const;
};