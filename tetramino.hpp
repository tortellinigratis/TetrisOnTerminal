#ifndef TETRAMINO_HPP
#define TETRAMINO_HPP

class Tetramino {
    protected:
        short shape[4][4];
        int maxDim;
        //1: SQUARE
        //2: RECT
        //3: J SHAPE
        //4: L SHAPE
        //5: S HAPE
        //6: T SHAPE
        //7: Z SHAPE

        // REVIEW could be useless
        void clearTtrmn() {

        }

    public:
        int type; 
        Tetramino(); // nothing here
                     // every subclass autoinitializes itself
           
        

        // REVIEW change to a more efficient algorithm
        void rotate();

        void antiRotate();

        void cyclic_roll(short&, short&, short&, short&);
            
        short ttrmnColor(int , int );

        int getMaxDim();
};

class Square: public Tetramino {
private:

public:
    Square();
};

class Rect: public Tetramino {
private:
    
public:
    Rect() ;
};

class J_SHAPE: public Tetramino {
private:
    
public:
    J_SHAPE();
};

class L_SHAPE: public Tetramino {
private:
    
public:
    L_SHAPE();
};

class S_HAPE: public Tetramino {
private:
    
public:
    S_HAPE() ;
};

class T_SHAPE: public Tetramino {
private:
    
public:
    T_SHAPE();
};

class Z_SHAPE: public Tetramino {
private:
    
public:
    Z_SHAPE();
};

#endif
