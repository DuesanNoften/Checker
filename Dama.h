#include<iostream>

using namespace std;

class Dama
{
public:
    int column;
    int row;
    float crowned;

    Dama(int c, int r);

    void UpdateCoords(int c, int r);

    ToCrown(float cr);
};
