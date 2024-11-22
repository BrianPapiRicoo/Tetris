#include "Ctablero.hpp"
using namespace std; 
using namespace sf; 


Ctablero::Ctablero()
{
    memset(tablero,0,sizeof(tablero));
    for(int i=0; i<20 ; i++ )
    {
        for(int j=0; j<20 ; j++ )
        {
            tableroShape[i][j]=RectangleShape(Vector2f(20,20));
            tableroShape[i][j].setPosition(j*20, i*20);
            tableroShape[i][j].setFillColor(Color(50,50,50));
            tableroShape[i][j].setOutlineThickness(2);
            tableroShape[i][j].setOutlineColor(Color(0,0,0));
        }
    }
}
    void Ctablero::UpdateTableroColor()
    {
            for(int i=0; i<20 ; i++ )
    {
        for(int j=0; j<20 ; j++ )
        {
            switch (tablero[i][j])
            {
            case 0: 
                tableroShape[i][j].setFillColor(Color(50,50,50));
                break;
             case 1: 
                tableroShape[i][j].setFillColor(Color(255,166,0));
                break;
             case 2: 
                tableroShape[i][j].setFillColor(Color(245,152,245));
                break;
             case 3: 
                tableroShape[i][j].setFillColor(Color(51,204,153));
                break;
             case 4: 
                tableroShape[i][j].setFillColor(Color(255,110,110));
                break;
             case 5: 
                tableroShape[i][j].setFillColor(Color(255,204,77));
                break;
             case 6: 
                tableroShape[i][j].setFillColor(Color(166,166,255));
                break;
             case 7: 
                tableroShape[i][j].setFillColor(Color(138,194,247));
                break;
            
            }
        }
    }
    }
void Ctablero::draw(RenderTarget &rt, RenderStates rs) const
{
  for(int i=0; i<20 ; i++ )
    {
        for(int j=0; j<20 ; j++ )
        {
            rt.draw(tableroShape[i][j], rs);
        }
    }
}

