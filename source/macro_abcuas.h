#ifndef MACRO_ABCUAS_H
#define MACRO_ABCUAS_H
#include "bits/stdc++.h"
#include "database.h"
#include "b_tree.h"
#include "macro_abcuas.h"
using namespace std;
struct Abcuas_cal
{
    int rowN;
    int wc,qc;
    Abcuas_cal():rowN(0),wc(0),qc(0){};
};
class Btree_Abcuas{
    private:
        B_Tree T;
        int XC;
    public:
        Btree_Abcuas(B_Tree b_tree): T(b_tree){};
        void find_X();
        void dfs(int,Abcuas_cal &,vector<int>&);
        int get_X(){return XC;};
};
#endif