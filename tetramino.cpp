#include "tetramino.hpp"

Tetramino::Tetramino() {
    // every subclass autoinitializes itself
}

void Tetramino::rotate() {
    for ( int i = 0; i < maxDim /2; i++ )
        for ( int j = 0; j < (maxDim +1) /2; j++ )
            cyclic_roll(shape[j][maxDim-1-i], shape[i][j], shape[maxDim-1-j][i], shape[maxDim-1-i][maxDim-1-j]);
}

void Tetramino::antiRotate() {
    for(int i=0; i<maxDim/2; i++)
        for(int j=0; j<(maxDim+1)/2; j++)
            cyclic_roll(shape[j][maxDim-1-i], shape[maxDim-1-i][maxDim-1-j], shape[maxDim-1-j][i], shape[i][j]);
}

void Tetramino::cyclic_roll(short &a, short &b, short &c, short &d) {
    int temp = a;
    a = b;
    b = c;
    c = d;
    d = temp;
}

short Tetramino::ttrmnColor(int i, int j) {
    return this-> shape[i][j];
}

int Tetramino::getMaxDim() {
    return this-> maxDim;
}


Square::Square() {
    type = 1;
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4 ;j ++ ) {
            if ( j < 2 && i < 2 ) {
                shape[i][j] = this->type;
            } else {
                shape[i][j] = -1;
            }
        }
    }
    maxDim = 2;
}

Rect::Rect() {
    type = 2;
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            if ( i == 1 ) {
                shape[i][j] = this->type;
            } else {
                shape[i][j] = -1;
            }
        }
    }
    maxDim = 4;
}

J_SHAPE::J_SHAPE() {
    type = 3;
    shape[0][0]=this->type;    shape[0][1]=-1;  shape[0][2]=-1;  shape[0][3]=-1;
    shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
    shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
    shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;
    maxDim = 3;
}

L_SHAPE::L_SHAPE() {
    type = 4;
    shape[0][0]=-1;    shape[0][1]=-1;  shape[0][2]=this->type;  shape[0][3]=-1;
    shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
    shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
    shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;
    maxDim = 3;
}

S_HAPE::S_HAPE() {
    type = 5;
    shape[0][0]=-1;    shape[0][1]=this->type;  shape[0][2]=this->type;  shape[0][3]=-1;
    shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=-1;   shape[1][3]=-1;
    shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
    shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;
    maxDim = 3;
}

T_SHAPE::T_SHAPE() {
    type = 6;
    shape[0][0]=-1;    shape[0][1]=this->type;  shape[0][2]=-1;  shape[0][3]=-1;
    shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
    shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
    shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;
    maxDim = 3;
}

Z_SHAPE::Z_SHAPE() {
    type = 7;
    shape[0][0]=this->type;    shape[0][1]=this->type;  shape[0][2]=-1;  shape[0][3]=-1;
    shape[1][0]=-1;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
    shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
    shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;
    maxDim = 3;
}
