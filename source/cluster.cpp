#include "cluster.h"
void Cluster :: solve()
{
    init();
    clustering();
    creating_bTrees();
    handle_out_of_range();
    DB.layout("cluster.txt");
    // need check
    //findX_bTrees();    
    place_bTrees();
}

void Cluster :: init()
{
    for(auto &it : DB.macros)
    {
        C_Node node;
        node.cx = it.lx;
        node.cy = it.ly;
        node.nodes.push_back(it.id);
        c_nodes.push_back(node);
    }
    cout<<"cluster init finished"<<endl;
}

void Cluster :: clustering()
{
    clusterN = c_nodes.size();
    // cal
    while(clusterN > 10){
        cout<<"clustering"<<endl;
        relation_cal();
        merge();
        clusterN = c_nodes.size();
    }

}

void Cluster :: relation_cal()
{
    while(!pq.empty())    
        pq.pop();    
    const int N = c_nodes.size();
    cout<<"relation_cal:"<<N<<endl;
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            auto &it1 = c_nodes[i], &it2 = c_nodes[j];
            int cost = abs(it1.cx-it2.cx) + abs(it1.cy-it2.cy);
            pq.push({cost,i,j});
        }
    }    
}

void Cluster :: merge(){
    cout<<"merge:"<<clusterN<<endl;
    unordered_set<int> visit;
    vector<C_Node> new_nodes;
    while(!pq.empty())
    {
        const auto &it = pq.top();
        // have been merged
        if(visit.count(it[1]) || visit.count(it[2]))
        {
            pq.pop();
            continue;
        }
        // merge
        visit.insert(it[1]);
        visit.insert(it[2]);
        C_Node new_node;    
        auto &it1 = c_nodes[it[1]],&it2 = c_nodes[it[2]];
        pq.pop();
        for(auto i : it1.nodes)
            new_node.nodes.push_back(i);
        for(auto i : it2.nodes)
            new_node.nodes.push_back(i);
        new_node.cx = (it1.nodes.size()*it1.cx + it2.nodes.size()*it2.cx) / (it1.nodes.size() + it2.nodes.size());
        new_node.cy = (it1.nodes.size()*it1.cy + it2.nodes.size()*it2.cy) / (it1.nodes.size() + it2.nodes.size());
        new_nodes.push_back(new_node);
    }
    // add unvisited back
    for(int i=0;i<c_nodes.size();i++)
    {
        if(!visit.count(i))
        {
            new_nodes.push_back(c_nodes[i]);
            visit.insert(i);
        }
    }
    cout<<"after merge"<<new_nodes.size()<<endl;
    c_nodes.clear();
    c_nodes = new_nodes;
}

void Cluster :: creating_bTrees()
{
    DB.group = clusterN;
    for(int i=0;i<clusterN;i++)
    {
        cout<<"b_tree "<<i<<endl;
        for(auto id : c_nodes[i].nodes)
            DB.macros[id].group = i;
        B_Tree b_tree(c_nodes[i].nodes);
        b_tree.solve(100000);
        b_trees.push_back(b_tree);
    }
}

void Cluster :: findX_bTrees()
{
    int idx = 0;
    for(auto &it : b_trees)
    {
        /*cout<<"findX_bTrees"<<endl;
        Btree_Abcuas abcuas(it);
        abcuas.find_X();
        int x = abcuas.get_X();*/
        it.update(c_nodes[idx].cx,c_nodes[idx].cy); 
        idx++;
    }    
}

void Cluster :: handle_out_of_range()
{
    int idx = 0;
    for(auto &it : b_trees)
    {
        int x = c_nodes[idx].cx,y = c_nodes[idx].cy;
        if(c_nodes[idx].cx < 0)
            x = 0;
        if(c_nodes[idx].cx + it.B_maxX > DB.dieW)
            x = DB.dieW - it.B_maxX;
        if(c_nodes[idx].cy < 0)
            y = 0;
        if(c_nodes[idx].cy + it.B_maxY > DB.dieH)
            y = DB.dieH - it.B_maxY;
        it.update(x,y);
        idx++;
    }  
}

void Cluster :: place_bTrees()
{
    // overlap graph create
    // sort by x
    B_Trees_place bTrees_place(b_trees);
    bTrees_place.solve();
}


