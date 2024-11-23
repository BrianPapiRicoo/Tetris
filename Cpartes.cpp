#include "Cpartes.hpp"

Cpartes::Cpartes()
{
    partes = {{{1,1},
               {1,1}},

             {{0,0,0,0,0}, 
              {0,0,1,0,0},
              {0,0,1,1,0}, 
              {0,0,0,1,0}, 
              {0,0,0,1,0}} ,
              
             {{0,0,0,0,0}, 
              {0,0,0,0,0},
              {0,0,0,0,0}, 
              {1,0,0,1,0}, 
              {1,1,1,1,0}} ,

             {{0,0,0,0,0}, 
              {0,0,0,0,0},
              {0,0,1,0,0}, 
              {0,1,1,1,0}, 
              {0,0,0,0,0}} ,
              
             {{0,0,0,0,0}, 
              {0,1,1,0,0},
              {0,1,0,0,0}, 
              {0,1,0,0,0}, 
              {0,0,0,0,0}} ,

             {{0,0,1,0}, 
              {0,0,1,0},
              {0,0,1,0}, 
              {0,0,1,0}} ,};
}
vector<std::vector<bool>> Cpartes::ConsultPart(int ind)
{
    return partes[ind];
}


void Cpartes::RotarParte(int ind)
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

void Cpartes::DesRotar(int ind)
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