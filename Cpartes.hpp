#include <iostream>
#include <vector>
using namespace std; 

class Cpartes
{
    private:
    vector<vector<vector<bool>>> partes; 
    public:
    Cpartes();
    vector<vector<bool>> ConsultPart(int ind);
    void RotarParte(int ind);
    void DesRotar(int ind); 

};
