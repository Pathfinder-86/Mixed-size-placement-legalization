#ifndef tetris_h
#define tetris_h
#include "bits/stdc++.h"
#include "database.h"
using namespace std;
struct Space{
    int row;
    int x,y,len;
};
class Tetris{
    private:
        vector<Space> spaces; // for std;      
    public:
        Tetris(){};
        void solve();
        void find_spaces();
        void place();
        void traverse(Gate &gate);
};
#endif
