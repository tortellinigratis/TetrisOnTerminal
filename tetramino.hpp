#ifndef TETRAMINO_HPP
#define TETRAMINO_HPP

class Tetramino {
    protected:
        short shape[4][4];
        int maxDim;
        //NOTE: 1: SQUARE
        //      2: RECT
        //      3: J SHAPE
        //      4: L SHAPE
        //      5: S HAPE
        //      6: T SHAPE
        //      7: Z SHAPE

    public:
        int type; 
        Tetramino();

        void rotate();

        void antiRotate();

        void cyclic_roll(short&, short&, short&, short&);
            
        short ttrmnColor(int , int );

        int getMaxDim();
};

class Square: public Tetramino {
public:
    Square();
};

class Rect: public Tetramino {
public:
    Rect() ;
};

class J_SHAPE: public Tetramino {
public:
    J_SHAPE();
};

class L_SHAPE: public Tetramino {
public:
    L_SHAPE();
};

class S_HAPE: public Tetramino {
public:
    S_HAPE() ;
};

class T_SHAPE: public Tetramino {
public:
    T_SHAPE();
};

class Z_SHAPE: public Tetramino {
public:
    Z_SHAPE();
};

#endif
