#ifndef Cluster_H
#define Cluster_H
#include "database.h"
#include "bits/stdc++.h"
#include "b_tree.h"
#include "macro_place.h"
#include "macro_abcuas.h"
struct C_Node{
    vector<int> nodes;
    int cx,cy;
};
class Cluster
{
    private:
        int clusterN;
        vector<B_Tree> b_trees;
        vector<C_Node> c_nodes;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
    public:
        Cluster(){};
        void solve();
        void init();
        void clustering();
        void relation_cal();
        void creating_bTrees();
        void merge();
        void findX_bTrees();
        //
        void handle_out_of_range();
        void place_bTrees();
        void update();
};
#endif