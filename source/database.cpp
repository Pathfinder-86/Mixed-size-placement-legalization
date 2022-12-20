#include "database.h"
Database DB;

void Database:: set(const string &in, const string &out)
{
    this->in_filename = in;
    this->out_filename = out;
    ifstream file(in);
    if(!file)
        cerr<<"file:"+in+" can't open"<<endl;
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    ss >> this->dieW;
    ss >> this->dieH;
    ss >> this->rowHeight;
    this->rowN = dieH / rowHeight;
    string temp;
    while(ss>>temp)
    {
        if(temp=="Macro")
        {
            ss>>this->macroN;
            for(int i=0;i<macroN;i++)
            {
                Gate macro;
                macro.id = i;
                macro.type = false;
                ss>>macro.lx;
                ss>>macro.ly;
                ss>>macro.w;
                ss>>macro.h;
                macro.rx = macro.lx + macro.w;
                macro.ry = macro.ly + macro.h;
                init_macros.push_back(macro);
            }   
        }
        if(temp=="std_cell")
        {
            ss>>this->cellN;
            for(int i=0;i<cellN;i++)
            {
                Gate cell;
                cell.id = i;
                cell.type = true;
                ss>>cell.lx;
                ss>>cell.ly;
                ss>>cell.w;
                ss>>cell.h;
                cell.rx = cell.lx + cell.w;
                cell.ry = cell.ly + cell.h;
                init_cells.push_back(cell);
            }
        }        
    }
    assert(cellN == init_cells.size());
    assert(macroN == init_macros.size());
    cells = init_cells;
    macros = init_macros;    
}

long long Database:: displacement_cal()
{
    return displacement(false) + displacement(true);
}

long long Database :: displacement(bool type)
{
    long long dis = 0;
    // type : false = Macro, true = cell
    int N = (type)? cellN : macroN;
    const vector<Gate> &gates = (type)? cells : macros;
    const vector<Gate> &init_gates = (type)? init_cells : init_macros;
    for(int i=0;i<N;i++)
    {
        int x = abs(init_gates[i].lx - gates[i].lx);
        int y = abs(init_gates[i].ly - gates[i].ly);
        dis += (x+y);
    }
    return dis;
}

bool Database:: out_of_range(bool type)
{
    const vector<Gate> &gates = (type)? cells : macros;
    for(auto &it : gates)
    {
        if(it.lx < 0 || it.ly <0 || it.rx > dieW || it.ry > dieH)
        {
            cout<<"out of range:";
            print_gate(it);
            return true;
        }
    }
    return false;
}

bool Database:: out_of_range_check()
{
    return out_of_range(true) || out_of_range(false);
}

bool Database:: overlap_check()
{
    return overlap(true) || overlap(false);
}

bool Database:: overlap(bool type)
{
    // will sort modify need to copy
    vector<Gate> gates = (type)? cells : macros;
    int N = (type)? cellN : macroN;

    // O(N*logN) sort
    sort(gates.begin(),gates.end(),[](auto &a,auto &b){
        return a.lx < b.lx;
    });
    // O(N) check
    for(int i = 0; i< N-1;i++)
    {
        if(gates[i].rx > gates[i+1].lx)
        {
            cout<<"overlap: ";
            print_gate(gates[i]);
            print_gate(gates[i+1]);
            return true;
        }
    }
    // O(N*logN) sort
    sort(gates.begin(),gates.end(),[](auto &a,auto &b){
        return a.ly < b.ly;
    });
    // O(N) check
    for(int i = 0; i< N-1;i++)
    {
        if(gates[i].ry > gates[i+1].ly)
        {
            cout<<"overlap: ";
            print_gate(gates[i]);
            print_gate(gates[i+1]);
            return true;
        }
    }

    return false;
}

void Database :: print_gate(const Gate &gate)
{
    cout<<"type: "<<gate.type<<" id: "<<gate.id<<endl;
    cout<<"lx:"<<gate.lx<<" ly:"<<gate.ly<<" rx:"<<gate.rx<<" ry:"<<gate.ry<<endl;
}

void Database :: result()
{
    /*ofstream infro("..//result//dis.txt");
    infro<<"total displacement:"<<displacement_cal()<<endl;
    infro<<"std displacement:"<<displacement(true)<<endl;
    infro<<"marco displacement:"<<displacement(false)<<endl;
    infro.close();*/
    ofstream ans("..//result//final_ans.txt");
    ans<<dieW<<" "<<dieH<<" "<<rowHeight<<endl;
    for(auto &it : macros)
        ans<<it.lx<<" "<<it.ly<<" "<<it.w<<" "<<it.h<<" "<<it.type<<" "<<it.group<<endl;
    for(auto &it : cells)
        ans<<it.lx<<" "<<it.ly<<" "<<it.w<<" "<<it.h<<" "<<it.type<<" "<<-1<<endl;
    ans.close();
}

void Database :: init_layout()
{
    ofstream file("..//result//init.txt");
    file<<DB.dieW<<" "<<DB.dieH<<" "<<DB.rowHeight<<" "<<DB.group<<endl;
    for(auto &it : init_macros)
        file<<it.lx<<" "<<it.ly<<" "<<it.w<<" "<<it.h<<" "<<it.type<<endl;

    for(auto &it : init_cells)
        file<<it.lx<<" "<<it.ly<<" "<<it.w<<" "<<it.h<<" "<<it.type<<endl;    
    file.close();
}


void Database :: layout(string str)
{
    ofstream ans("..//result//"+str);
    ans<<dieW<<" "<<dieH<<" "<<rowHeight<<" "<<group<<endl;
    for(auto &it : macros)
        ans<<it.lx<<" "<<it.ly<<" "<<it.w<<" "<<it.h<<" "<<it.type<<" "<<it.group<<endl;
    ans.close();
}