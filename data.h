#ifndef DATA_H
#define DATA_H
#include "bits/stdc++.h"
using namespace std;
struct Gate
{
    int h,w;
    int x,y;
};
class Data{
    private:
        // intput
        long long dieW,dieH;
        double macro_pre,std_pre;
        string filename;
        // setting
        int rowHeight;        
        long long die_area,macro_area,std_area;
        // parameters
        vector<Gate> macros;
        vector<Gate> std_cells;
    public:
        Data(){};
        void generate(const vector<string> &strs);
        void solve();
        void setting();
        void output();
        void generate_data(bool);
        void dispersion();
};      

#endif