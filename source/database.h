#ifndef DATABASE_H
#define DATABASE_H
#include "bits/stdc++.h"
using namespace std;

struct Block{  // for tetris
    int lx,ly,rx,ry;
};
struct Gate{
    int group;
    int lx,ly,rx,ry;
    int w,h;
    int id;
    bool type;
};
class Database{
    public:
        // parameters
        long long dieH,dieW;
        int rowHeight,rowN;
        int macroN,cellN;
        int group;
        string in_filename,out_filename;
        // data
        vector<Gate> init_cells; // const
        vector<Gate> init_macros; // const
        vector<Gate> cells;
        vector<Gate> macros;
        vector<Block> blocks;
        // return val
        long long std_dis,macro_dis,total_dis;
        long long die_area_macro;
        double die_area_rate;
    public:
        Database(){};
        void set(const string&,const string&);
        long long displacement_cal();
        long long displacement(bool);
        // cal in b_tree
        //long long die_area_macro();  
        //double die_area_macro_rate();
        bool out_of_range_check();
        bool out_of_range(bool);
        bool overlap(bool);
        bool overlap_check();
        void print_gate(const Gate&);
        void result();        
        // test
        void init_layout();
        void layout(string);
};

extern Database DB;
#endif