#include "legal.h"
void Legal:: solve()
{
    solve_Macro();
    /*
    if(DB.out_of_range(false))
        cerr<<"Error: Out of range"<<endl;
    if(DB.overlap(false))
        cerr<<"Error: Overlap"<<endl;
    */    
    solve_std();
    /*
    if(DB.out_of_range(true))
        cerr<<"Error: Out of range"<<endl;
    if(DB.overlap(true))
        cerr<<"Error: Overlap"<<endl;    
    */
    DB.result();
}


void Legal:: solve_Macro()
{
    Cluster cluster;
    cluster.solve();
}



void Legal:: solve_std()
{
    Tetris tetris;
    tetris.solve();
}
