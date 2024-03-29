#ifndef tetramino_h

#include "tetramino.h"

#endif

class Rect: public Tetramino {
private:

public:
    Rect() {
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                if ( j == 1 ) {
                    shape[i][1] = true;
                } else {
                    shape[i][j] = false;
                }
            }
        }
        maxDim = 4;
    }
};