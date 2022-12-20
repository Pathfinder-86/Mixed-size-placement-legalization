#include "bits/stdc++.h"
#include "data.h"
using namespace std;
// format : [dieWidth]  [dieHeight] [Macro area percentage] [standard cells percentage] [file name]
// data type : dieWidth,dieHeight  long long(int) ,  percentage : double
int main(int argc, char** argv)
{
    vector<string> strs = {argv[1],argv[2],argv[3],argv[4],argv[5]};
    Data data;
    data.generate(strs);
    data.output();
    return 0;
}