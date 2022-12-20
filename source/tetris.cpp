#include "tetris.h"
void Tetris :: solve()
{
    find_spaces();
    place();
}

void Tetris :: find_spaces()
{
    vector<vector<pair<int,int>>> non_spaces;
    non_spaces.resize(DB.rowN);
    for(auto &it : DB.blocks)
    {    
        int r1 = it.ly/DB.rowHeight; // bot at which row
        int r2 = it.ry /DB.rowHeight; // top at which row      
        int d2 = it.ry % DB.rowHeight;

        non_spaces[r1].push_back(make_pair(it.lx,it.rx));
        if(r1 == r2) // terminal in one row only
            continue;
        else
        {
            if(d2 == 0)  // terminal only reach r2-1
                r2 = r2-1;
            for(int i=r1+1;i<=r2;i++)
                non_spaces[i].push_back(make_pair(it.lx,it.rx));
        }
    }
    // sort
    for(auto &it : non_spaces)
    {
        sort(it.begin(),it.end(),[](auto &a,auto &b){
            return a.first < b.first;
        });
    }

    for(int i=0;i<DB.rowN;i++)
    {        
        pair<int,int> range;
        range.first = 0,range.second = DB.dieW;        
        for(auto &it : non_spaces[i])
        {
            if(it.first==range.first) // left edge            
                range.first = it.second;            
            else
            {
                Space space;
                space.x = range.first,space.y = DB.rowHeight*i;
                space.len = it.first-range.first;
                spaces.push_back(space);
                range.first = it.second;
            }
        }
        if(range.first != range.second)
        {
            Space space;
            space.x = range.first,space.y = DB.rowHeight*i;
            space.len = range.second-range.first;
            spaces.push_back(space);
        }
    }
}

void Tetris :: place()
{   
    sort(DB.cells.begin(), DB.cells.end(),[](auto &a,auto &b)
    {  return a.lx < b.lx;});

    for(auto &it : DB.cells)    
        traverse(it);
}

void Tetris :: traverse(Gate &gate)
{    
    int best_idx = -1,best_cost = INT_MAX;
    for(int i=0;i<spaces.size();i++)
    {   
        auto &it = spaces[i];
        if(it.len >= gate.w)
        {
            int cost = abs(gate.lx - it.x) + abs(gate.ly - it.y);
            best_idx = (cost < best_cost) ? i : best_idx;
            best_cost = min(cost,best_cost);            
        }
    }
    if(best_idx != -1)
    {
        gate.lx = spaces[best_idx].x;
        gate.ly = spaces[best_idx].y;
        gate.rx += gate.w;
        gate.ry = gate.h;
        spaces[best_idx].len -= gate.w;
        spaces[best_idx].x = spaces[best_idx].x + gate.w;
    }
    else
        cerr<<"can't place"<<gate.id<<endl;
}