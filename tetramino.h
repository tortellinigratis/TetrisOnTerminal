class Tetramino {
    protected:
        short shape[4][4];
        int maxDim;
        //0: SQUARE
        //1: RECT
        //2: J SHAPE
        //3: L SHAPE
        //4: S HAPE
        //5: T SHAPE
        //6: Z SHAPE

        // REVIEW could be useless
        void clearTtrmn() {

        }

    public:
        int type; 
        Tetramino() {
            // nothing here
            // every subclass autoinitializes itself
        }

        // REVIEW change to a more efficient algorithm
        void rotate() {
            for ( int i = 0; i < maxDim /2; i++ ) {
                for ( int j = 0; j < (maxDim +1) /2; j++ ) {
                    cyclic_roll(shape[j][maxDim-1-i], shape[i][j], shape[maxDim-1-j][i], shape[maxDim-1-i][maxDim-1-j]);
                }
            }
            /* if ( maxDim > 2 ) {
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
            } */
        }

        void antiRotate() {
            for(int i=0; i<maxDim/2; i++)
                for(int j=0; j<(maxDim+1)/2; j++)
                    cyclic_roll(shape[j][maxDim-1-i], shape[maxDim-1-i][maxDim-1-j], shape[maxDim-1-j][i], shape[i][j]);
        }

        void cyclic_roll(short &a, short &b, short &c, short &d) {
            int temp = a;
            a = b;
            b = c;
            c = d;
            d = temp;
        }
            /*
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
        } */
        

        short ttrmnColor(int i, int j) {
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
        type = 0;
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j ++ ) {
                if ( j < 2 && i < 2 ) {
                    shape[i][j] = this->type;
                } else {
                    shape[i][j] = -1;
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
        type = 1;
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
};

class J_SHAPE: public Tetramino {
private:
    
public:
    J_SHAPE() {
        type = 2;
        shape[0][0]=this->type;    shape[0][1]=-1;  shape[0][2]=-1;  shape[0][3]=-1;
        shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
        shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
        shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;

        maxDim = 3;
    }
};

class L_SHAPE: public Tetramino {
private:
    
public:
    L_SHAPE() {
        type = 3;
        shape[0][0]=-1;    shape[0][1]=-1;  shape[0][2]=this->type;  shape[0][3]=-1;
        shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
        shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
        shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;

        maxDim = 3;
    }
};

class S_HAPE: public Tetramino {
private:
    
public:
    S_HAPE() {
        type = 4;
        shape[0][0]=-1;    shape[0][1]=this->type;  shape[0][2]=this->type;  shape[0][3]=-1;
        shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=-1;   shape[1][3]=-1;
        shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
        shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;

        maxDim = 3;
    }
};

class T_SHAPE: public Tetramino {
private:
    
public:
    T_SHAPE() {
        type = 5;
        shape[0][0]=-1;    shape[0][1]=this->type;  shape[0][2]=-1;  shape[0][3]=-1;
        shape[1][0]=this->type;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
        shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
        shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;

        maxDim = 3;
    }
};

class Z_SHAPE: public Tetramino {
private:
    
public:
    Z_SHAPE() {
        type = 6;
        shape[0][0]=this->type;    shape[0][1]=this->type;  shape[0][2]=-1;  shape[0][3]=-1;
        shape[1][0]=-1;    shape[1][1]=this->type;   shape[1][2]=this->type;   shape[1][3]=-1;
        shape[2][0]=-1;   shape[2][1]=-1;  shape[2][2]=-1;  shape[2][3]=-1;
        shape[3][0]=-1;   shape[3][1]=-1;  shape[3][2]=-1;  shape[3][3]=-1;

        maxDim = 3;
    }
};
