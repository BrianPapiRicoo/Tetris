#include <iostream>
#include <vector>
using namespace std; 

class TetrisPartes
{
    private:
    vector<vector<vector<bool>>> partes; 
    public:
    TetrisPartes();
    vector<vector<bool>> ConsultarParte(int ind);
    void RotarParte(int ind);
    void DesRotar(int ind); 

};
