#include "bits/stdc++.h"
using namespace std;
int main()
{
    vector<int> vec;
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
    vec = {0,1,2};
    pq.push(vec);
    vec = {3,-1,-2};
    pq.push(vec);
    while(!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        cout<<it[0]<<endl;
    }
    return 0;
}