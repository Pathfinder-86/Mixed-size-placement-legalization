#include "b_tree.h"

void B_Tree :: solve(const int iterations)
{
    init();    
    packing(nodes_root);
    if(modules_N<2)
        return;
    // init solution
    double cost = getCost();
    best_sol.cost = cost;
    cur_sol.cost = cost;
    keep_best();
    keep_sol();
    // iterations
    for(int i=0;i<iterations;i++)
    {
        //cout<<"iterations "<<i<<endl;
        //cout<<"perturb"<<endl;
        perturb();
        // get new B_tree
        //cout<<"packing"<<endl;
        packing(nodes_root);
        //cout<<"getCost"<<endl;
        cost = getCost();
        if(cost < best_sol.cost)
            keep_best();
        if(cost < cur_sol.cost)
            keep_sol();
        else
            recover(cur_sol);        
    }
    recover(best_sol);
    packing(nodes_root);
    getCost();
    this->rx = this->lx + B_maxX;
    this->ry = this->ly + B_maxY;
}

void B_Tree :: init()
{
    modules_N = ids.size();
    contour.resize(modules_N);
    nodes.resize(modules_N);
    nodes_root = 0;
    for(int i=0;i<modules_N;i++)
    {        
        
        nodes[i].idx = i;
        // map
        idx_id[i] = ids[i];
        nodes[i].parent = (i+1)/2-1;
        nodes[i].left = (2*i+1 < modules_N)? 2*i+1 : -1;
        nodes[i].right = (2*i+2 < modules_N)? 2*i+2 : -1;        
    }
    nodes[0].parent = -1;
    this->lx = 0;
    this->ly = 0;
    this->B_maxX = INT_MIN;
    this->B_maxY = INT_MIN;
}

void B_Tree :: clear()
{
    contour_root = -1;
}

void B_Tree ::packing(int root)
{
    // preorder
    if(root == -1)
        return;
    bool is_left = (root==nodes_root)? true : (root == nodes[nodes[root].parent].left)? true : false;
    place_module(root,nodes[root].parent,is_left);
    packing(nodes[root].left);
    packing(nodes[root].right);
}

void B_Tree :: place_module(int node,int parent,bool is_left)
{
    int id = idx_id[node];
    int pid = (node == nodes_root)? -1 : idx_id[parent];
    int w = DB.macros[id].w , h = DB.macros[id].h;
    Gate &gate = DB.macros[id];
    if(nodes[node].parent == -1)
    {
        contour_root = node;
        contour[node].front = -1;
        contour[node].back = -1;
        gate.lx = 0;
        gate.ly = 0;
        gate.rx = w;
        gate.ry = h;
        return;
    }
    int contour_ptr;
    if(is_left)
    {
        gate.lx = DB.macros[pid].rx;
        gate.rx = gate.lx + w;

        contour_ptr = contour[parent].back;
        contour[node].front = parent;
        contour[parent].back = node;
        if(contour_ptr == -1) // no obstacle in x
        {
            gate.ly = 0;
            gate.ry = h;
            contour[node].back = -1;
            return;
        }
    }
    else
    {
        gate.lx = DB.macros[pid].lx;
        gate.rx = gate.lx + w;
        contour_ptr = parent;
        int front = contour[contour_ptr].front;
        if(front==-1)  // first of the contour
        {
            contour_root = node;
            contour[node].front = -1;
        }
        else
        {
            contour[front].back = node;
            contour[node].front = front;
        }
    }

    int min_y = INT_MIN,bx,by;

    for( ; contour_ptr != -1 ; contour_ptr = contour[contour_ptr].back)
    {
        int c_idx = idx_id[contour_ptr];
        bx = DB.macros[c_idx].rx;
        by = DB.macros[c_idx].ry;

        min_y = max(min_y,by);
        if( bx >= gate.rx)
        {
            gate.ly = min_y;
            gate.ry = gate.ly + h;
            if(bx > gate.rx)
            {
                contour[node].back = contour_ptr;
                contour[contour_ptr].front = node;
            }
            else
            {
                int back = contour[contour_ptr].back;
                contour[node].back = back;
                if(back!=-1)
                    contour[back].front = node;
            }
            break;
        }
    }
    // last 
    if(contour_ptr == -1)
    {
        gate.ly =  (min_y==INT_MIN)? 0 : min_y;
        gate.ry =  gate.ly + h;
        contour[node].back = -1;
    }

}

double B_Tree :: getCost()
{
    // find  maxX, maxY
    int maxX = INT_MIN,maxY = INT_MIN;
    double diffX,diffY;
    for(auto &it : nodes)
    {
        int id = idx_id[it.idx];
        maxX = max(DB.macros[id].rx,maxX);
        maxY = max(DB.macros[id].ry,maxY);
        diffX = abs(DB.init_macros[id].lx - DB.macros[id].lx);
        diffY = abs(DB.init_macros[id].ly - DB.macros[id].ly);
    }
    this->B_maxX = maxX;
    this->B_maxY = maxY;
    return (diffX+diffY) + double(maxX) * double(maxY) + pow(abs(maxX - maxY),2);
}

void B_Tree :: get_solution(Solution &sol)
{
    sol.nodes = nodes;
    sol.nodes_root = nodes_root;
    sol.cost = getCost();
}

void B_Tree ::keep_sol(){
    get_solution(cur_sol);
}

void B_Tree ::keep_best()
{
    get_solution(best_sol);
}

void B_Tree ::recover()
{
    recover(cur_sol);
}

void B_Tree ::recover_best()
{
    recover(best_sol);
}

void B_Tree :: recover(const Solution &sol)
{
    nodes = sol.nodes;
    nodes_root = sol.nodes_root;
}

double rand01()
{
    return double(rand()%10000) / 10000.0;
}

void B_Tree ::perturb()
{
    int p,n;
    double swap_rate = 0.5;    

    if( swap_rate > rand01())
    {        
        if(modules_N==2)
            return;
        do{
            n = rand()%modules_N;
        }while(n==nodes_root);
        
        do{
            p = rand()%modules_N;               
        }while(p==n ||nodes[n].parent==p||nodes[p].parent==n);
        //cout<<"swap:"<<n<<" "<<p<<endl;
        swap_node(nodes[p],nodes[n]);
    }
    else
    {
        n = rand()% modules_N;        
        do{
            p = rand()%modules_N;               
        }while(p==n);
        //cout<<"delete & insert:"<<n<<" "<<p<<endl;
        //cout<<"delete"<<endl;
        delete_node(nodes[n]);
        //cout<<"insert"<<endl;
        insert_node(nodes[p],nodes[n]);        
    }
}

void B_Tree :: swap_node(B_Node &n1,B_Node &n2)
{
    // update nodes' children
    //cout<<"swap_node"<<endl;
    if(n1.left != -1)    
        nodes[n1.left].parent = n2.idx;
    if(n1.right != -1)
        nodes[n1.right].parent = n2.idx;
    if(n2.left != -1)
        nodes[n2.left].parent = n1.idx;
    if(n2.right != -1)
        nodes[n2.right].parent = n1.idx;
    
    // update nodes' parents
    if(n1.parent != -1) // not root
    {
        if(nodes[n1.parent].left == n1.idx) // n1 is left child of its parent
            nodes[n1.parent].left = n2.idx;
        else
           nodes[n1.parent].right = n2.idx; 
    }
    else
        nodes_root = n2.idx;

    if(n2.parent != -1) // not root
    {
        if(nodes[n2.parent].left == n2.idx) // n1 is left child of its parent
            nodes[n2.parent].left = n1.idx;
        else
           nodes[n2.parent].right = n1.idx; 
    }
    else
        nodes_root = n1.idx;

    swap(n1.left,n2.left);
    swap(n1.right,n2.right);
    swap(n1.parent,n2.parent);
}

bool rand_bool()
{
    return (rand()%2==0);
}

void B_Tree :: insert_node(B_Node &parent, B_Node &node)
{
    //cout<<"insert_node"<<endl;
    node.parent = parent.idx;
    bool egde = rand_bool();
    if(egde)
    {
        node.left = parent.left;
        node.right = -1;
        if(parent.left != -1)
            nodes[parent.left].parent = node.idx;
        parent.left = node.idx;
    }
    else
    {
        node.left = -1;
        node.right = parent.right;
        if(parent.right != -1)
            nodes[parent.right].parent = node.idx;
        parent.right = node.idx;
    }
}

void B_Tree :: delete_node(B_Node &node)
{
    //cout<<"delete_node"<<endl;
    int child = -1;  // pull which child
    int subchild = -1;
    int subparent = -1;
    if(!node.isLeaf())   // update new node points to original node's child
    {
        bool left = rand_bool();
        if(node.left == -1) left = false;
        if(node.right == -1) left = true;

        if(left)
        {
            child = node.left;
            if(node.right != -1)
            {
                subchild  = nodes[child].right;
                subparent = node.right;                
                nodes[node.right].parent =child;
                nodes[child].right = node.right;
            }            
        }
        else
        {
            child = node.right;
            if(node.left!= -1)
            {
                subchild  = nodes[child].left; 
                subparent = node.left;                
                nodes[node.left].parent =child;
                nodes[child].left = node.left;
            }
        }     
        nodes[child].parent = node.parent;   
    }

    if(node.parent == -1) // root    update parent to new child
        nodes_root = child;
    else
    {
        if(node.idx == nodes[node.parent].left) // left child
            nodes[node.parent].left = child;
        else
            nodes[node.parent].right = child;
    }

    // subtree    
    if(subchild != -1)
    {
        B_Node &sc = nodes[subchild];
        int count = 1;
        while(1)
        {
            count++;
            B_Node &p = nodes[subparent];
            if(p.left == -1 || p.right == -1)
            {
                sc.parent = p.idx;
                if(p.left ==-1)
                    p.left = sc.idx;
                else
                    p.right = sc.idx;
                break;
            }
            else            
                subparent = (rand_bool())? p.left : p.right;        
        }       
    }
}

void B_Tree :: update(const int &xc,const int &yc)
{
    this->lx += xc,this->ly += yc;
    this->rx += xc,this->ry += yc;

    for(auto &it : nodes)
    {
        int id = idx_id[it.idx];
        DB.macros[id].lx += xc;
        DB.macros[id].ly += yc;
        DB.macros[id].rx += xc;
        DB.macros[id].ry += yc;    
    }
}

