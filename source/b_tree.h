#ifndef B_TREE_H
#define B_TREE_H
#include "database.h"
#include "bits/stdc++.h"
using namespace std;
struct Contour
{
    int front = -1,back = -1;
};
struct B_Node{
    int idx,parent,left,right;
    bool isLeaf(){return left==-1 && right==-1;};
};
struct Solution{
      int nodes_root;
      vector<B_Node> nodes;
      double cost;
      Solution(){cost = 1;}
};
class B_Tree{
    public:
        // actual node id
        unordered_map<int,int> idx_id;
        vector<int> ids;  
        // parameters
        int modules_N;
        int nodes_root,contour_root;
        int B_maxX,B_maxY;
        int lx,ly,rx,ry;
        vector<B_Node> nodes; 
        vector<Contour> contour;
        // solution
        Solution best_sol,cur_sol;
    public:
        // basic
        B_Tree(){};
        B_Tree(vector<int> &nodes): ids(nodes){};
        void solve(const int);
        void init();    
        void packing(int);
        // solution
        void keep_sol();
        void keep_best();
        void recover();
        void recover(const Solution &);
        void recover_best();
        void place_module(int,int,bool);
        void get_solution(Solution&);
        // SA 
        void perturb();
        void swap_node(B_Node &,B_Node &);
        void insert_node(B_Node &,B_Node &);
        void delete_node(B_Node &);
        // helper
        double getCost();
        void clear();
        void update(const int &,const int &);
};
#endif