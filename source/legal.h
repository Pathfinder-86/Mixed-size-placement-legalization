#ifndef LEGAL_H
#define LEGAL_H
#include "bits/stdc++.h"
#include "database.h"
#include "b_tree.h"
#include "cluster.h"
#include "tetris.h"
using namespace std;
class Legal{
    private:
        int B_treeN;
        vector<B_Tree> B_trees;
    public:
        void solve();
        void solve_Macro();
        void solve_std();
        void clustering_Macro();
};
#endif