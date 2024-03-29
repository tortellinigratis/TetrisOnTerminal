class Tetramino {
    protected:
        bool shape[4][4];
        int maxDim;

        // REVIEW could be useless
        void clearTtrmn() {

        }

    public:
        Tetramino() {
            // nothing here
            // every subclass autoinitializes itself
        }

        // REVIEW change to a more efficient algorithm
        void antiRotate() {
            if ( maxDim > 2 ) {
                bool clone[maxDim][maxDim -2];
                bool extra = shape[3][1];
                for ( int i = 0; i < maxDim; i++ ) {
                    for ( int j = 0; j < maxDim -2; j++ ) {
                        clone[i][j] = shape[i][j+2];
                    }
                }
                int t, z = maxDim -1;
                for ( int y = 0; y < maxDim; y++ ) {
                    t = 0;
                    for ( int x = 0; x < maxDim; x++ ) {
                        if ( y == 3 && x == 1 ) {
                            shape[t][z] = extra;
                        } else if ( x > 1 ) {
                            shape[t][z] = clone[y][x-2];
                        } else {
                            shape[t][z] = shape[y][x];
                        }
                        t++;
                    }
                    z--;
                }
            }
        }

        void rotate() {
            if ( maxDim > 2 ) {
                bool clone[maxDim -2][maxDim];
                bool extra = shape[1][0];
                for ( int i = 0; i < maxDim -2; i++ ) {
                    for ( int j = 0; j < maxDim; j++ ) {
                        clone[i][j] = shape[i+2][j];
                    }
                }
                int t, z = 0;
                for ( int y = 0; y < maxDim; y++ ) {
                    t = maxDim -1;
                    for ( int x = 0; x < maxDim; x++ ) {
                        if ( y == 1 && x == 0 ) {
                            shape[t][z] = extra;
                        } else if ( y > 1 ) {
                            shape[t][z] = clone[y-2][x];
                        } else {
                            shape[t][z] = shape[y][x];
                        }
                        t--;
                    }
                    z++;
                }
            }
        }

        bool isTrue(int i, int j) {
            return this-> shape[i][j];
        }

        int getMaxDim() {
            return this-> maxDim;
        }
};

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

class Rect: public Tetramino {
private:

public:
    Rect() {
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                if ( i == 1 ) {
                    shape[i][j] = true;
                } else {
                    shape[i][j] = false;
                }
            }
        }
        maxDim = 4;
    }
};