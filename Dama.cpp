#include <iostream>
#include "Dama.h"

using namespace std;

Dama::Dama(int c, int r){
    column = c;
    row = r;
    crowned = false;
};

Dama::UpdateCoords(int c, int r) {
    column =  c;
    row = r;
}

int Dama::ToCrown(float cr) {
    crowned = cr;
}