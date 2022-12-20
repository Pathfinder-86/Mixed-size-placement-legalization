#include "macro_place.h"

void B_Trees_place :: solve()
{
    create_graph_y();
    place_y();
    out_of_range();
    DB.layout("yAdjust.txt");
    create_graph_x();    
    place_x();
    DB.layout("xAdjust.txt");
    shift_mid();
    DB.layout("ans.txt");
    set_blocks();
}

void B_Trees_place :: create_graph_x()
{
    sort(b_trees.begin(),b_trees.end(),[](auto &a,auto &b){
        return a.lx < b.lx;
    });
    N = b_trees.size();
    in_degree = vector<int>(N,0);
    next = vector<vector<int>>(N);
    front = vector<vector<int>>(N);
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(min(b_trees[i].ry,b_trees[j].ry) > max(b_trees[i].ly,b_trees[j].ly))            
            {
                next[i].push_back(j);
                in_degree[j]++;
                front[j].push_back(i);
            }            
        }
    }
}

void B_Trees_place :: create_graph_y()
{
    sort(b_trees.begin(),b_trees.end(),[](auto &a,auto &b){
        return a.ly < b.ly;
    });
    N = b_trees.size();
    in_degree = vector<int>(N,0);
    next = vector<vector<int>>(N);
    front = vector<vector<int>>(N);
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(min(b_trees[i].rx,b_trees[j].rx) > max(b_trees[i].lx,b_trees[j].lx))
            {
                next[i].push_back(j);
                in_degree[j]++;
                front[j].push_back(i);
            }            
        }
    }
}

void B_Trees_place :: place_y()
{
    unordered_set<int> placed;
    queue<int> Queue;
    for(int i=0;i<N;i++)
        if(in_degree[i]==0)
            Queue.push(i);
    int y = INT_MIN;
    int pop_num;
    while(!Queue.empty())
    {        
        pop_num = Queue.size();
        while(pop_num--)
        {
            int idx = Queue.front();
            Queue.pop();
            for(auto j : next[idx])
                in_degree[j]--;
            placed.insert(idx);
            for(auto j : front[idx])
                y = max(y,b_trees[j].ry);
            y = (y==INT_MIN)? 0 : y;
            b_trees[idx].update(0,y - b_trees[idx].ly);
            y = INT_MIN;
        }
        for(int i=0;i<N;i++)
            if(!placed.count(i) && in_degree[i]==0)
                Queue.push(i);
    }
}

void B_Trees_place :: out_of_range()
{
    for(auto &it : b_trees){
        if(it.ry > DB.dieH)
            it.update(0,DB.dieH-it.ry);
    }
}

void B_Trees_place :: place_x()
{
    unordered_set<int> placed;
    queue<int> Queue;
    for(int i=0;i<N;i++)
        if(in_degree[i]==0)
            Queue.push(i);
    int x = INT_MIN;
    int pop_num;
    while(!Queue.empty())
    {        
        pop_num = Queue.size();
        while(pop_num--)
        {
            int idx = Queue.front();
            Queue.pop();
            for(auto j : next[idx])
                in_degree[j]--;
            placed.insert(idx);
            for(auto j : front[idx])
                x = max(x,b_trees[j].rx);
            x = (x==INT_MIN)? 0 : x;            
            b_trees[idx].update(x - b_trees[idx].lx,0);            
            x = INT_MIN;
        }
        for(int i=0;i<N;i++)
            if(!placed.count(i) && in_degree[i]==0)
                Queue.push(i);
    }    
}

void B_Trees_place :: shift_mid()
{
    // shift b_trees to mid
    for(auto &it : b_trees){
        MaxX = max(it.rx,MaxX);
        MaxY = max(it.ry,MaxY);
    }
    int x_shift = (DB.dieW - MaxX)/2;
    int y_shift = (DB.dieH - MaxY)/2;
    for(auto &it : b_trees)    
        it.update(x_shift,y_shift);
}


// for std
void B_Trees_place :: set_blocks()
{
    for(auto &it : b_trees)
    {
        Block block;
        block.lx = it.lx, block.ly = it.ly, block.rx = it.rx , block.ry = it.ry;
        DB.blocks.push_back(block);
    }
}