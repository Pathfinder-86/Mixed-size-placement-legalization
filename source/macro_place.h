#ifndef MACRO_PLCAE_H
#define MACRO_PLCAE_H
#include "bits/stdc++.h"
#include "b_tree.h"
#include "database.h"
using namespace std;
class B_Trees_place
{
    private:
        vector<B_Tree> b_trees;
        int N;
        int MaxX,MaxY;
        vector<int> in_degree;
        vector<vector<int>> front;
        vector<vector<int>> next;
    public:
        B_Trees_place(vector<B_Tree> trees): b_trees(trees){};
        void solve();
        void create_graph_x();
        void create_graph_y();
        void place_x();
        void place_y();
        void shift_mid();
        void out_of_range();
        void set_blocks();
};
#endif