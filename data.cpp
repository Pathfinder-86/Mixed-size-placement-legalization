#include "data.h"
void Data :: generate(const vector<string> &strs){
    dieW = stoll(strs[0]);
    dieH = stoll(strs[1]);
    macro_pre = stod(strs[2]);
    std_pre = stod(strs[3]);
    filename = strs[4];
    die_area = dieH * dieW;
    cout<<"check:"<<macro_pre<<" "<<std_pre<<endl;
    macro_area = macro_pre * die_area;
    std_area = std_pre * die_area;
    cout<<"check area:"<<die_area<<" "<<macro_area<<" "<<std_area<<endl;
    solve();
}

void Data :: solve(){    
    setting();
    generate_data(true);
    generate_data(false);
    dispersion();
    output();
}


void Data :: setting()
{
    // define rowHeight = 20
    // 1. 500 : small: rows:25
    // 2. 2000 : median: rows:100
    // 3. 1e5 : very large: rows: 500
    
    if(dieH < 5000)
        rowHeight = 20;
    else
        rowHeight = 40;

    //rowHeight = 40;
}


void Data :: generate_data(bool type) // true : Macro, false : std_cells;
{
    long long area_sum = 0,area_max;
    int h_max,w_max,h_min, w_min;
    h_max = (type)? 10*rowHeight : 0;
    h_min = (type)? 3.16*rowHeight : 0;
    w_max = (type)? 10*rowHeight : rowHeight*2;
    w_min = (type)? 3.16*rowHeight : rowHeight;
    area_max = (type)? macro_area : std_area;
    int h_diff = h_max-h_min;
    int w_diff = w_max-w_min;
    vector<Gate> &gates = (type)? macros : std_cells;
    
    while(area_sum < area_max)
    {
        double mul = double(rand())/RAND_MAX; //mul [0~1]        
        int h = (type)? h_min + mul * h_diff : rowHeight; 
        int w = w_min + mul * w_diff; //mul [0~1]
        Gate gate;
        gate.h = h;
        gate.w = w;
        area_sum+=h*w;
        gates.push_back(gate);
    }    
}

void Data :: dispersion()
{
    double mul;
    for(auto &it : macros)
    {        
        mul = double(rand())/RAND_MAX;
        it.x = dieW*mul;
        mul = double(rand())/RAND_MAX;
        it.y = dieH*mul;
    }
    for(auto &it : std_cells)
    {
        mul = double(rand())/RAND_MAX;
        it.x = dieW*mul;
        mul = double(rand())/RAND_MAX;
        it.y = dieH*mul;
    }
}

void Data :: output()
{
    ofstream file(filename);
    file<<dieW<<" "<<dieH<<" "<<rowHeight<<endl;
    file<<"Macro"<<" "<<macros.size()<<endl;
    for(auto &it : macros)
    {
        file<<it.x<<" "<<it.y<<" "<<it.w<<" "<<it.h<<endl;
    }
    file<<"std_cell"<<" "<<std_cells.size()<<endl;
    for(auto &it : std_cells)
    {
        file<<it.x<<" "<<it.y<<" "<<it.w<<" "<<it.h<<endl;
    }
    file.close();

    ofstream layout("result//init.txt");
    layout<<dieW<<" "<<dieH<<" "<<rowHeight<<endl;
    for(auto &it : macros)
    {
        layout<<it.x<<" "<<it.y<<" "<<it.w<<" "<<it.h<<" "<<0<<endl;
    }
    for(auto &it : std_cells)
    {
        layout<<it.x<<" "<<it.y<<" "<<it.w<<" "<<it.h<<" "<<1<<endl;
    }
    layout.close();
}

