#ifndef TETRAMINO_HPP
#define TETRAMINO_HPP

class Tetramino {
    protected:
        short shape[4][4];
        int maxDim;
        int type;
        //NOTE: type 1: SQUARE
        //           2: RECT
        //           3: J SHAPE
        //           4: L SHAPE
        //           5: S HAPE
        //           6: T SHAPE
        //           7: Z SHAPE

    public:
        Tetramino();

        void rotate(); // clockwise rotation

        void antiRotate(); // anti-clockwise rotation

        short ttrmnColor(int , int ); // returns the color of a specific Tetramino in a speficic (x, y) position

        int getMaxDim(); // returns this-> maxDim, the maximum dimension the Tetramino can occupy

        int getType();

    private:
        void cyclic_roll(short&, short&, short&, short&); // the actual matrix-rotation function
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
