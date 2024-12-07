#include "TetrisPartes.hpp"

TetrisPartes::TetrisPartes()
{
partes = {
    //Cuadrado
    {{1, 1},
     {1, 1}},

    //Z
    {{0, 0, 0, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 1, 1, 0, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    //S
    {{0, 0, 0, 0, 0},
     {0, 1, 1, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    //L
    {{0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 0, 0, 0}},

    //J
    {{0, 0, 0, 0, 0},
     {0, 0, 0, 1, 0},
     {0, 0, 0, 1, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 0, 0, 0}},

    //T 
    {{0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    //I
    {{0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0}}
};
}
vector<std::vector<bool>> TetrisPartes::ConsultarParte(int ind)
{
    return partes[ind];
}


void TetrisPartes::RotarParte(int ind)
{
 vector<vector<bool>> vAux=partes[ind];
 int indI = 0, indJ = 0; 
 int sz= (int)partes[ind].size();

 for(int i =0 ; i<sz ; i++)
 {
    for(int j = sz-1; j >= 0; j--)
    {
        partes[ind][indI][indJ] = vAux[j][i];
        indJ++ ;
    }
    indI++;
    indJ=0;
 }
}

void TetrisPartes::DesRotar(int ind)
{
     vector<vector<bool>> vAux=partes[ind];
 int indI = 0, indJ = 0; 
 int sz= (int)partes[ind].size();

 for(int i = sz-1 ; i >= 0 ; i--)
 {
    for(int j = 0; j < sz; j++)
    {
        partes[ind][indI][indJ] = vAux[j][i];
        indJ++ ;
    }
    indI++;
    indJ=0;
    }

}