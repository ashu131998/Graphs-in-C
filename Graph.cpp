#include<iostream>
#include<bits/stdc++.h>
#include<list>
using namespace std;
class GraphPair_di{
    private:
    int V;
    list<pair<int,int>> *vertex;
    public:
    GraphPair_di(int V){
        this->V=V;
        vertex = new list<pair<int,int>>[V];
    }
    void addedge(int u,int v,int x){
        vertex[u].push_back(make_pair(v,x));
    }
    //Dijkstas for Directed graph. Bellman is not defined for undirected graph.
    void dikstras(int s){
        vector<int> dist(V,INT_MAX);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push(make_pair(0,s));
        dist[s]=0;
        while(pq.size()){
            pair<int,int> x=pq.top();
            pq.pop();
            int src=x.second;
            for(auto y:vertex[src])
            {
                int weight=y.second;
                int u=y.first;
                if(dist[u]>dist[src]+weight){
                    dist[u]=dist[src]+weight;
                     pq.push(make_pair(dist[u],y.first)); 
                }
            }
        }
        for(int i=0;i<V;i++){
            cout<<dist[i]<<" ";
        }
    }
};
class GraphPair_un{
    private:
    int V;
    list<pair<int,int>> *vertex;
    public:
    GraphPair_un(int V){
        this->V=V;
        vertex = new list<pair<int,int>>[V];
    }
    void addedge(int u,int v,int x){
        vertex[u].push_back(make_pair(v,x));
        vertex[v].push_back(make_pair(u,x));
    }
    //No bellman for Dijkstras
    void dikstras(int s){
        vector<int> dist(V,INT_MAX);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push(make_pair(0,s));
        dist[s]=0;
        while(pq.size()){
            pair<int,int> x=pq.top();
            pq.pop();
            int src=x.second;
            for(auto y:vertex[src])
            {
                int weight=y.second;
                int u=y.first;
                if(dist[u]>dist[src]+weight){
                    dist[u]=dist[src]+weight;
                     pq.push(make_pair(dist[u],y.first)); 
                }
            }
        }
        for(int i=0;i<V;i++){
            cout<<dist[i]<<" ";
        }
    }
    void prims(){
        vector<int> dist(V,INT_MAX);
        vector<bool> inMST(V,false);
        vector<int> parent(V,-1);
        inMST[0]=true;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;   //weight,node
        pq.push(make_pair(0,0));
        dist[0]=0;
        while(pq.size()){
            pair<int,int> x=pq.top();
            pq.pop();
            int src=x.second;
            inMST[src]=true;
            for(auto y:vertex[src])
            {
                int weight=y.second;
                int u=y.first;
                if(inMST[u]==false and  dist[u]>weight){
                    dist[u]=weight;
                    pq.push(make_pair(dist[u],y.first)); 
                    parent[u]=src;
                }
            }
        }
        for(int i=0;i<parent.size();i++){
            cout<<parent[i]<<" "<<i<<endl;
        }
    }
};
class Graph{
    private:
    int V;
    list<int> *vertex;
    bool *v_dfs;
    bool *visited;
    public:
    //making a graph
    Graph(int V){
        this->V=V;
        vertex = new list<int>[V];
        v_dfs=new bool(V);
        visited=new bool(V);
        for(int i=0;i<V;i++)
        v_dfs[i]=false;
    }
    //adding a edge
    void addedge(int u,int v){
        vertex[v].push_back(u);
        vertex[u].push_back(v);
    }
    //bfs
    void bfs(int s){
        bool *visited=new bool[V];
        for(int i=0;i<V;i++){
            visited[i]=false;
        }
        queue<int> q;
        q.push(s);
        visited[s]=true;
        while (q.size())
        {
            int x=q.front();
            cout<<x<<" ";
            q.pop();
            list<int>::iterator it;
            for(it=vertex[x].begin();it!=vertex[x].end();it++){
                if(visited[*it]==false)
                {q.push(*it);
                visited[*it]=true;}
            }
        }
    }
    //dfs
    void dfs(int s){
        v_dfs[s]=true;
        cout<<s<<" ";
        for(auto y:vertex[s]){
            if(v_dfs[y]==false){
                dfs(y);
            }
        }
    }
    //detecting a cycle
    bool dacloop(int s,int parent){
        visited[s]=true;
        for(auto x:vertex[s]){
            if(!visited[x])
            {
                if(dacloop(x,s)){
                return true;
                }
            }
            else if(x!=parent)
            {
                return true;
            }    
        }
        return false;
    }
    bool dac()
    {
        for(int i=0;i<V;i++){
            visited[i]=false;
        }
        for(int i=0;i<V;i++){
            if (!visited[i])
            if(dacloop(i,-1))return true;
        }
        return false;
    }
};
class Graph_DAC{
    public:
    int V;
    list<int>* vertex;
    bool* visited;
    Graph_DAC(int V){
        this->V=V;
        vertex=new list<int>[V];
        visited=new bool[V];
    }
    void addedge(int u,int v){
        vertex[u].push_back(v);
    }
    void topological_sort_util(int i,bool visited[],stack<int> &s){
        visited[i]=true;
        for(auto x:vertex[i]){
            if(visited[x]==false){
                topological_sort_util(x,visited,s);
            }
        }
        s.push(i);
    }
    void topological_sort(){
        stack<int> s;
        for(int i=0;i<V;i++){
            visited[i]=false;
        }
        for(int i=0;i<V;i++){
            if(visited[i]==false){
                topological_sort_util(i,visited,s);
            }
        }
        while (s.size()!=0) 
        { 
        cout << s.top() << " "; 
        s.pop(); 
        } 
    }
};
void floy_warshell(int g6[][4])
{
    int i,j,dist[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dist[i][j]=g6[i][j];
        }
    }
    for(int k=0;k<4;k++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
}

void topo(int s, vector<vector<int>> adj,bool visited[],stack<int> &st){
    visited[s]=true;
    for(auto x:adj[s]){
        if(visited[x]==false)
        topo(x,adj,visited,st);
    }
    st.push(s);
}
void transpose(vector<vector<int>> adj,vector<vector<int>> &trans){
    for(int i=0;i<adj.size();i++){
        for ( int j = 0; j < adj[i].size(); j++)
        {
            trans[adj[i][j]].push_back(i);
        }   
    }
}
void dfs_util(int s,vector<vector<int>> trans,bool visited[]){
    visited[s]=true;
    cout<<s<<" ";
    for(auto x: trans[s]){
        if(visited[x]==false){
            dfs_util(x,trans,visited);
        }
    }
}
void kosaraju(int V,vector<vector<int>> adj){
    bool* visited=new bool[V];
    stack<int> st;
    for(int i=0;i<V;i++){
        visited[i]=false;
    }
    for(int i=0;i<V;i++){
        if(visited[i]==false)
        topo(i,adj,visited,st);
    }
    vector<vector<int>> trans(V);
    transpose(adj, trans);
    for(int i=0;i<V;i++){
        visited[i]=false;
    }
    while(st.size()){
        int x=st.top();
        st.pop();
        if(visited[x]==false){
            dfs_util(x,trans,visited);
            cout<<endl;
        }
    }
}
bool detectACycle_util(int s,bool visited[],bool reStack[],vector<vector<int>> g9){
    visited[s]=true;
    reStack[s]=true;
    for(auto x:g9[s]){
        if(!visited[x] and detectACycle_util(x,visited,reStack,g9)){
            return true;
        }
        if(reStack[x]){
            return true;
        }
    }
    reStack[s]=false;
    return false;
}
bool detectACycle(vector<vector<int>> g9,int V){
    bool *visited=new bool[V];
    bool *reStack=new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i]=false;
        reStack[i]=false;
    }
    for (int i = 0; i < V; i++)
    {
        if(detectACycle_util(i,visited,reStack,g9)){
            return true;
        }
    }
    return false;
}

int main(){
    int V=5;
    Graph g(V);
    g.addedge(0,1);
    g.addedge(0,3);
    g.addedge(3,4);
    g.addedge(1,3);
    g.addedge(3,2);
    g.addedge(2,1);
    g.addedge(2,4);
    g.addedge(1,4);
    Graph g1(5); 
    g1.addedge(1, 0); 
    g1.addedge(0, 2); 
    g1.addedge(2, 1); 
    g1.addedge(0, 3); 
    Graph g2(3); 
    g2.addedge(0, 1); 
    g2.addedge(1, 2); 
    int s;
    cin>>s;
    g.bfs(s);cout<<endl;
    g.dfs(s);cout<<endl;
    cout<<g.dac();cout<<endl;
    cout<<g1.dac();cout<<endl;
    cout<<g2.dac();cout<<endl;
    //Undirected Dikstras
    GraphPair_un g3(9);
    g3.addedge(0, 1, 4); 
    g3.addedge(0, 7, 8); 
    g3.addedge(1, 2, 8); 
    g3.addedge(1, 7, 11); 
    g3.addedge(2, 3, 7); 
    g3.addedge(2, 8, 2); 
    g3.addedge(2, 5, 4); 
    g3.addedge(3, 4, 9); 
    g3.addedge(3, 5, 14); 
    g3.addedge(4, 5, 10); 
    g3.addedge(5, 6, 2); 
    g3.addedge(6, 7, 1); 
    g3.addedge(6, 8, 6); 
    g3.addedge(7, 8, 7);
    g3.dikstras(0);cout<<endl;
    g3.prims();cout<<endl;
    cout<<endl;
    //Directed Bellman--Same
    GraphPair_di g4(5);
    g4.addedge(0, 1, -1); 
    g4.addedge(0, 2, 4); 
    g4.addedge(1, 2, 3); 
    g4.addedge(1, 3, 2); 
    g4.addedge(1, 4, 2); 
    g4.addedge(3, 2, 5); 
    g4.addedge(3, 1, 1); 
    g4.addedge(4, 3, -3);
    g4.dikstras(0);cout<<endl;
    //Directed Dijstras--Same
    GraphPair_di g5(5);
    g5.addedge(0, 1, 10);
    g5.addedge(0, 4, 3);
	g5.addedge(1, 2, 2);
    g5.addedge(1, 4, 4);
	g5.addedge(2, 3, 9);
    g5.addedge(3, 2, 7);
	g5.addedge(4, 1, 1); 
    g5.addedge(4, 2, 8);
	g5.addedge(4, 3, 2);
    g5.dikstras(0);cout<<endl;
    int g6[4][4]={ {0, 5, 10000, 10},  
                        {10000, 0, 3, 10000},  
                        {10000, 10000, 0, 1},  
                        {10000, 10000, 10000, 0}  
                    };  
    floy_warshell(g6);
    // Create a graph given in the above diagram 
    Graph_DAC g7(6); 
    g7.addedge(5, 0); 
    g7.addedge(5, 2); 
    g7.addedge(2, 3); 
    g7.addedge(4, 1); 
    g7.addedge(4, 0); 
    g7.addedge(1, 3);
    g7.topological_sort();cout<<endl;
    vector<vector<int>> g8={{2,3},{0},{1},{4},{}}; //directed graph
    kosaraju(5, g8); //to find strongly connected component of graph
    vector<vector<int>> g9={{1,2},{2},{0,3},{3}};
    bool dac=detectACycle(g9,4);
    cout<<dac;
}
