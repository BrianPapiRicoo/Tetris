#include "Ctablero.hpp"

using namespace sf; 
using namespace std; 

Ctablero::Ctablero()
{
    
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            tablero[i][j] = 0;

            
            tableroShape[i][j] = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
            tableroShape[i][j].setPosition(j * 20.f, i * 20.f);
            tableroShape[i][j].setFillColor(sf::Color(50, 50, 50));
            tableroShape[i][j].setOutlineThickness(2.f);
            tableroShape[i][j].setOutlineColor(sf::Color(0, 0, 0));
        }
    }
}

bool Ctablero::UpdateTablero()
{
    bool limite = false; 
    int cont = 0;

    if (timer >= limite_de_timer)
    {
        for (int i = 18; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                if (tablero[i][j] == -1 && i + 1 < 20 && tablero[i + 1][j] <= 0)
                {
                    cont++;
                }
            }
        }

        if (cont == 4)
        {
            indY++; 
            for (int i = 18; i >= 0; i--)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (tablero[i][j] == -1 && i + 1 < 20)
                    {
                        tablero[i][j] = 0;
                        tablero[i + 1][j] = -1;
                    }
                }
            }

            cont = 0; 
            for (int i = 18; i >= 0; i--)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (tablero[i][j] == -1 && i + 1 < 20 && tablero[i + 1][j] <= 0)
                    {
                        cont++;
                    }
                }
            }

            if (cont != 4)
            {
                for (int i = 19; i >= 0; i--)
                {
                    for (int j = 0; j < 10; j++)
                    {  
                        if (tablero[i][j] == -1)
                        {
                            tablero[i][j] = indColorNewParte; // Arreglo del operador
                        }
                    }
                }
                limite = true; 
            }
        }
        else
        {
            limite = true; 
        }

        timer = 0; 
    }
    timer++; 
    return limite; 
}

bool Ctablero::InstalarPartes()
{
    srand(time(NULL)); 
    indNewParte = rand() % 7; 


    vector<vector<bool>> parte = partes.ConsultPart(indNewParte);
    int sz = (int)parte.size();


    indY = 0;
    indX = 5 - sz / 2;


    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            if (parte[i][j])
            {
                if (tablero[i + indY][j + indX] > 0)
                    return false; 
                tablero[i + indY][j + indX] = -1; 
            }
        }
    }

    
    int color = 1 + rand() % 7;
    indColorNewParte = color;

    switch (color)
    {
    case 1: NewParteColor = sf::Color(255, 166, 0); break;
    case 2: NewParteColor = sf::Color(245, 152, 245); break;
    case 3: NewParteColor = sf::Color(51, 204, 153); break;
    case 4: NewParteColor = sf::Color(255, 110, 110); break;
    case 5: NewParteColor = sf::Color(255, 204, 77); break;
    case 6: NewParteColor = sf::Color(166, 166, 255); break;
    case 7: NewParteColor = sf::Color(138, 194, 247); break;
    default: break;
    }

    return true;
}

void Ctablero::UpdateTableroColor()
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            switch (tablero[i][j])
            {
            case 0: 
                tableroShape[i][j].setFillColor(sf::Color(110, 109, 109));
                break;
            case -1: 
                tableroShape[i][j].setFillColor(NewParteColor);
                break;
            case 1:
                tableroShape[i][j].setFillColor(sf::Color(255, 166, 0));
                break;
            case 2:
                tableroShape[i][j].setFillColor(sf::Color(245, 152, 245));
                break;
            case 3:
                tableroShape[i][j].setFillColor(sf::Color(51, 204, 153));
                break;
            case 4:
                tableroShape[i][j].setFillColor(sf::Color(255, 110, 110));
                break;
            case 5:
                tableroShape[i][j].setFillColor(sf::Color(255, 204, 77));
                break;
            case 6:
                tableroShape[i][j].setFillColor(sf::Color(166, 166, 255));
                break;
            case 7:
                tableroShape[i][j].setFillColor(sf::Color(138, 194, 247));
                break;
            }
        }
    }
}

void Ctablero::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            rt.draw(tableroShape[i][j], rs);
        }
    }
}