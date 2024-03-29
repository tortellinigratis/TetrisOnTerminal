#ifndef tetramino_h

#include "tetramino.h"

#endif

class Square: public Tetramino {
private:
    
public:
    Square() {
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j ++ ) {
                if ( j < 2 && i < 2 ) {
                    shape[i][j] = true;
                } else {
                    shape[i][j] = false;
                }
            }
        }
        maxDim = 2;
    }
};