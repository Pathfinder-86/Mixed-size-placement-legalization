#include "bits/stdc++.h"
#include "legal.h"
#include "database.h"
using namespace std;
int main(int argc, char** argv)
{
    string in_filename(argv[1]),out_filename(argv[2]);
    cout<<in_filename<<" "<<out_filename<<endl;
    DB.set(in_filename,out_filename);
    DB.init_layout();
    Legal legal;
    legal.solve();
    return 0;
}