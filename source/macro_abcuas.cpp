#include "macro_abcuas.h"
void Btree_Abcuas :: find_X()
{
    vector<int> ret; // store xc
    Abcuas_cal data;

    data.rowN++;
    int id = T.idx_id[T.nodes_root];
    data.qc+= (DB.init_macros[id].lx-data.wc);
    data.wc+=DB.macros[id].w;

    dfs(T.nodes_root,data,ret);
    int sum = 0;
    for(auto i: ret)
        sum+=i;
    XC = sum/ret.size();
}

void Btree_Abcuas :: dfs(int root,Abcuas_cal &data,vector<int>& ret)
{
    if(T.nodes[root].isLeaf())
    {
        int xc = data.qc / data.rowN;
        ret.push_back(xc);
        return;
    }
    if(T.nodes[root].left != -1)
    {   
        int left = T.nodes[root].left;
        data.rowN++;
        int id = T.idx_id[left];
        data.qc+= (DB.init_macros[id].lx-data.wc);
        data.wc+=DB.macros[id].w;
        dfs(left,data,ret);
        data.qc-=(DB.init_macros[id].lx-data.wc);
        data.wc-=DB.macros[id].w;
    }
    if(T.nodes[root].right != -1)
    {        
        int right = T.nodes[root].right;
        data.rowN++;
        int id = T.idx_id[right];
        data.qc+=(DB.init_macros[id].lx-data.wc);
        data.wc+=DB.macros[id].w;
        dfs(right,data,ret);
        data.qc-=(DB.init_macros[id].lx-data.wc);
        data.wc-=DB.macros[id].w; 
    }
}
