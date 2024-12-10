#include "../include/TetrisTablero.hpp"

TetrisTablero::TetrisTablero() {
    memset(tablero, 0, sizeof(tablero));
    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 0; columna < 10; ++columna) {
            tableroShape[fila][columna] = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
            tableroShape[fila][columna].setPosition(columna * 20.f, fila * 20.f);

         
            tableroShape[fila][columna].setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

           
            tableroShape[fila][columna].setOutlineThickness(2.f);
            tableroShape[fila][columna].setOutlineColor(sf::Color(0, 0, 0));
        }
    }
}

bool TetrisTablero::InstalarPartes() {
    srand(time(NULL));
    indNewParte = rand() % 7;

    std::vector<std::vector<bool>> parte = partes.ConsultarParte(indNewParte);

    int sz = static_cast<int>(parte.size());

    indY = 0;
    indX = 5 - sz / 2;

    for (int fila = 0; fila < sz; ++fila) {
        for (int columna = 0; columna < sz; ++columna) {
            if (parte[fila][columna]) {
                if (tablero[fila][columna + indX] > 0) return false;
                tablero[fila][columna + indX] = -1;
            }
        }
    }

   
    int color = 1 + rand() % 7;
    indColorNewParte = color;

    switch (color) {
        case 1: NewParteColor = sf::Color(255, 105, 180); break; // Rosa 
        case 2: NewParteColor = sf::Color(0, 255, 255); break;   // Cian 
        case 3: NewParteColor = sf::Color(255, 215, 0); break;   // Amarillo 
        case 4: NewParteColor = sf::Color(255, 69, 0); break;    // Naranja 
        case 5: NewParteColor = sf::Color(124, 252, 0); break;   // Verde
        case 6: NewParteColor = sf::Color(194, 140, 255); break;  // lila
        case 7: NewParteColor = sf::Color(30, 144, 255); break;  // Azul 
    }

    return true;
}

bool TetrisTablero::ActualizarTablero() {
    bool limite = false;
    int aux;

    if (timer >= limite_de_timer) {
        aux = 0;
        for (int fila = 18; fila >= 0; --fila) {
            for (int columna = 0; columna < 10; ++columna) {
                if (tablero[fila][columna] == -1) {
                    if (tablero[fila + 1][columna] <= 0) aux++;
                }
            }
        }

        if (aux == 4) {
            indY++;
            for (int fila = 18; fila >= 0; --fila) {
                for (int columna = 0; columna < 10; ++columna) {
                    if (tablero[fila][columna] == -1) {
                        tablero[fila][columna] = 0;
                        tablero[fila + 1][columna] = -1;
                    }
                }
            }
        } else {
            for (int fila = 19; fila >= 0; --fila) {
                for (int columna = 0; columna < 10; ++columna) {
                    if (tablero[fila][columna] == -1) tablero[fila][columna] = indColorNewParte;
                }
            }
            limite = true;
        }

        timer = 0;
    }

    timer++;
    return limite;
}

void TetrisTablero::ActualizarColoresTablero() {
    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 0; columna < 10; ++columna) {
            switch (tablero[fila][columna]) {
                case 0: 
                    tableroShape[fila][columna].setFillColor(sf::Color(50, 50, 50)); // Fondo oscuro
                    break;
                case 1: 
                    tableroShape[fila][columna].setFillColor(sf::Color(255, 105, 180)); // Rosa intenso
                    break;
                case 2: 
                    tableroShape[fila][columna].setFillColor(sf::Color(0, 255, 255)); //Cian 
                    break;
                case 3: 
                    tableroShape[fila][columna].setFillColor(sf::Color(255, 215, 0)); //Amarillo 
                    break;
                case 4: 
                    tableroShape[fila][columna].setFillColor(sf::Color(255, 69, 0)); //Naranja
                    break;
                case 5: 
                    tableroShape[fila][columna].setFillColor(sf::Color(124, 252, 0)); //Verde 
                    break;
                case 6: 
                    tableroShape[fila][columna].setFillColor(sf::Color(194, 140, 255)); //Lila
                    break;
                case 7: 
                    tableroShape[fila][columna].setFillColor(sf::Color(30, 144, 255)); //Azul 
                    break;
                default: 
                    tableroShape[fila][columna].setFillColor(NewParteColor); 
                    break;
            }
        }
    }
}

void TetrisTablero::ActualizarLimiteTimer(int limite) {
    limite_de_timer = limite;
}

void TetrisTablero::RotarParte() {
    partes.RotarParte(indNewParte);
    std::vector<std::vector<bool>> parte = partes.ConsultarParte(indNewParte);

    int sz = static_cast<int>(parte.size());

    for (int fila = 0; fila < sz; ++fila) {
        for (int columna = 0; columna < sz; ++columna) {
            if (parte[fila][columna]) {
                if (indY + fila < 0 || indY + fila >= 20 || indX + columna < 0 || indX + columna >= 10 || tablero[indY + fila][indX + columna] > 0) {
                    partes.DesRotar(indNewParte);
                    return;
                }
            }
        }
    }

    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 0; columna < 10; ++columna) {
            if (tablero[fila][columna] == -1) tablero[fila][columna] = 0;
        }
    }

    for (int fila = 0; fila < sz; ++fila) {
        for (int columna = 0; columna < sz; ++columna) {
            if (parte[fila][columna]) {
                tablero[fila + indY][columna + indX] = -1;
            }
        }
    }
}

void TetrisTablero::MoverDerecha() {
    int aux = 0;
    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 0; columna < 9; ++columna) {
            if (tablero[fila][columna] == -1 && tablero[fila][columna + 1] <= 0) aux++;
        }
    }

    if (aux == 4) {
        indX++;
        for (int fila = 0; fila < 20; ++fila) {
            for (int columna = 9; columna >= 0; --columna) {
                if (tablero[fila][columna] == -1) {
                    tablero[fila][columna] = 0;
                    tablero[fila][columna + 1] = -1;
                }
            }
        }
    }
}

void TetrisTablero::MoverIzquierda() {
    int aux = 0;
    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 1; columna < 10; ++columna) {
            if (tablero[fila][columna] == -1 && tablero[fila][columna - 1] <= 0) aux++;
        }
    }

    if (aux == 4) {
        indX--;
        for (int fila = 0; fila < 20; ++fila) {
            for (int columna = 0; columna < 10; ++columna) {
                if (tablero[fila][columna] == -1) {
                    tablero[fila][columna] = 0;
                    tablero[fila][columna - 1] = -1;
                }
            }
        }
    }
}

int TetrisTablero::RevisarLineas() {
    int aux = 0, lineas = 0;

    for (int fila = 19; fila >= 0; --fila) {
        aux = 0;
        for (int columna = 0; columna < 10; ++columna) {
            if (tablero[fila][columna] > 0) aux++;
            if (lineas > 0) {
                tablero[fila + lineas][columna] = tablero[fila][columna];
                tablero[fila][columna] = 0;
            }
        }
        if (aux == 10) {
            for (int columna = 0; columna < 10; ++columna) tablero[fila][columna] = 0;
            lineas++;
        }
    }

    return lineas;
}

void TetrisTablero::LimpiarTablero() {
    memset(tablero, 0, sizeof(tablero));
}

void TetrisTablero::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    for (int fila = 0; fila < 20; ++fila) {
        for (int columna = 0; columna < 10; ++columna) {
            rt.draw(tableroShape[fila][columna], rs);
        }
    }
}