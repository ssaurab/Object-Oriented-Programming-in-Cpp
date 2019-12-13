/*
   "Help will always be given at OOAIA Lab to those who ask for it." - Professor RN.
*/


#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class sorter {
    
    public:
    
    bool operator ()(const pair<int, int>& p1, const pair<int, int>& p2){
        
        return p1.first < p2.first;
    }
};
class sorter1 {
    
    public:
    
    bool operator ()(int p1,int p2){
        
        return p1 < p2;
    }
};

class Graph {
   // declare appropriate data structures to implement your class
    int size, edges;
    vector<vector <pair <int, int>> >adj;
    vector<int>id;
    map <int, int> idmap;
    map <int, int> idmapreverse;
public:
   // write your operator overloaded functions for binary +/-, unary - and []
   // write your functions to implement queries WEIGHT, DEGSEQ, DFS, NCOMP

   Graph() {
      ;
   }

   Graph(int V, int E) {
       size = V;edges = E;
       adj.resize(V);
      ;
   }
    void add_vertex(int a,int v){
        id.push_back(v);
        idmap.insert(pair <int, int>(a,v));
        idmapreverse.insert(pair <int, int>(v,a));
    }
    void add_edge(int u,int v,int w){
        
        adj[idmapreverse[u]].push_back(make_pair(v,w));
    }
    Graph operator + (Graph G2)
    {
        int k1 = 0;
        Graph G3(size+G2.size, edges+G2.edges);
        sort(id.begin(), id.end());
        sort(G2.id.begin(), G2.id.end());
        for(int i = 0; i < id.size(); i++)
        {
            G3.add_vertex(i, id[i]);
            for(int j = 0; j < adj[idmapreverse[id[i]]].size(); j++)
            {
                G3.add_edge(id[i],adj[idmapreverse[id[i]]][j].first, adj[idmapreverse[id[i]]][j].second);
            }
            
        }
        for(int j = 0; j < G2.id.size();j++)
        {
            if(binary_search(G3.id.begin(), G3.id.end(),G2.id[j]))
            for(int k = 0; k < G2.adj[G2.idmapreverse[G2.id[j]]].size(); k++)
            {
                vector <pair <int,int>> :: iterator it;
                it = find(adj[idmapreverse[G2.id[j]]].begin(),adj[idmapreverse[G2.id[j]]].end(),G2.adj[G2.idmapreverse[G2.id[j]]][k]);
                if(it == adj[idmapreverse[G2.id[j]]].end())
                G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second);
                else
                    G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second + (*it).second);
            }
            else
            {
                G3.add_vertex(id.size()+k1, G2.id[j]);
                k1++;
             for(int k = 0; k < G2.adj[idmapreverse[G2.id[j]]].size(); k++)
                 {
                G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second);
                }
            }
            
        }
        return G3;
    }
    Graph operator - (Graph G2)
    {
        int k1 = 0;
        Graph G3(size+G2.size, edges+G2.edges);
        sort(id.begin(), id.end());
        sort(G2.id.begin(), G2.id.end());
        for(int i = 0; i < id.size(); i++)
        {
            G3.add_vertex(i, id[i]);
            for(int j = 0; j < adj[idmapreverse[id[i]]].size(); j++)
            {
                G3.add_edge(id[i],adj[idmapreverse[id[i]]][j].first, adj[idmapreverse[id[i]]][j].second);
            }
            
        }
        for(int j = 0; j < G2.id.size();j++)
        {
            if(binary_search(G3.id.begin(), G3.id.end(),G2.id[j]))
            for(int k = 0; k < G2.adj[G2.idmapreverse[G2.id[j]]].size(); k++)
            {
                vector <pair<int,int>> :: iterator it;
                it = find(adj[idmapreverse[G2.id[j]]].begin(),adj[idmapreverse[G2.id[j]]].end(),G2.adj[G2.idmapreverse[G2.id[j]]][k]);
                if(it == adj[idmapreverse[G2.id[j]]].end())
                G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second);
                else
                    G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second - (*it).second);
            }
            else
            {
                G3.add_vertex(id.size()+k1, G2.id[j]);
                k1++;
             for(int k = 0; k < G2.adj[idmapreverse[G2.id[j]]].size(); k++)
                 {
                G3.add_edge(G2.id[j],G2.adj[G2.idmapreverse[G2.id[j]]][k].first, adj[idmapreverse[G2.id[j]]][k].second);
                }
            }
            
        }
        return G3;
        
    }
    void weight(int u, int v)
    {
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          if(adj[idmapreverse[u]][i].first == v) cout <<  adj[idmapreverse[u]][i].second<<endl;
        }
    }
    void adjout(int u)
    {
        sorter s;
        sort(adj[idmapreverse[u]].begin(), adj[idmapreverse[u]].end(), s);
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          cout << adj[idmapreverse[u]][i].first<<" ";
        }
        cout << endl;
    }
    void degseq(int u)
    {
        //cout << "hi";
        sorter s;
        sort(adj[idmapreverse[u]].begin(), adj[idmapreverse[u]].end(), s);
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          cout << adj[idmapreverse[adj[idmapreverse[u]][i].first]].size()<<" ";
        }
        cout << endl;
    }
    
    void DFS(int u)
    {
        {
            bool *visited = new bool[size];
            for (int i = 0; i < size; i++)
                visited[i] = false;
            DFSUtil(u, visited);
        }
    }
    
   void DFSUtil(int v, bool visited[])  
        {
           
            visited[idmapreverse[v]] = true;
            cout << v << " ";

            vector <pair <int, int>>::iterator i;
            sorter s;
            sort(adj[idmapreverse[v]].begin(), adj[idmapreverse[v]].end(), s);
            for (i = adj[idmapreverse[v]].begin(); i != adj[idmapreverse[v]].end(); ++i)
                if (!visited[idmapreverse[(*i).first]])
                    DFSUtil((*i).first, visited);
        }
       void DFSUtildash(int v, bool visited[])  
        {
           
            visited[idmapreverse[v]] = true;
           // cout << v << " ";

            vector <pair <int, int>>::iterator i;
            sorter s;
            sort(adj[idmapreverse[v]].begin(), adj[idmapreverse[v]].end(), s);
            for (i = adj[idmapreverse[v]].begin(); i != adj[idmapreverse[v]].end(); ++i)
                if (!visited[idmapreverse[(*i).first]])
                    DFSUtildash((*i).first, visited);
        }
    void ncomp()
    {
int count = 0;
    bool *visited = new bool[size];
    for(int v = 0; v < size; v++)
        visited[v] = false;
 
    for (int v=0; v<size; v++)
    {
        if (visited[v] == false)
        {
            // print all reachable vertices
            // from v
            DFSUtildash(v, visited);
 
           count ++;
        }
      
    }  cout << count <<endl;}
};


// COMPULSORY: Derive BooleanGraph class from Graph class
class BooleanGraph : public Graph {
    int size;
    vector<vector <int> >adj;
    vector<int>id;
    map <int, int> idmap;
    map <int, int> idmapreverse;
   
public:
   BooleanGraph() {
      ;
   }

   BooleanGraph(int V, int E) {
       size = V;//edges = E;
       adj.resize(V);
      ;
   }

   void add_vertex(int a,int v){
        idmap.insert(pair <int, int>(a,v));
        idmapreverse.insert(pair <int, int>(v,a));
    }
    void add_edge(int u,int v){
        
        adj[idmapreverse[u]].push_back(v);
    }
    void weight(int u, int v)
    {
        int count = 0;
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          if(adj[idmapreverse[u]][i] == v) {cout << 1<<endl;count ++;}
            
        }
        if(count == 0) cout << "0"<< endl;
    }
    void adjout(int u)
    {
        //cout <<"hii";
        sorter1 s;
        sort(adj[idmapreverse[u]].begin(), adj[idmapreverse[u]].end(), s);
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          cout << adj[idmapreverse[u]][i]<<" ";
        }
        cout << endl;
    }
    void degseq(int u)
    {
        //cout << "hi";
        sorter1 s;
        sort(adj[idmapreverse[u]].begin(), adj[idmapreverse[u]].end(), s);
        for(int i = 0; i < adj[idmapreverse[u]].size(); i++)
        {  
          cout << adj[idmapreverse[adj[idmapreverse[u]][i]]].size()<<" ";
        }
        cout << endl;
    }
    
    void DFS(int u)
    {
        {
            bool *visited = new bool[size];
            for (int i = 0; i < size; i++)
                visited[i] = false;
            DFSUtil(u, visited);
        }
    }
    
   void DFSUtil(int v, bool visited[])  
        {
           
            visited[idmapreverse[v]] = true;
            cout << v << " ";

            vector <int>::iterator i;
            sorter1 s;
            sort(adj[idmapreverse[v]].begin(), adj[idmapreverse[v]].end(), s);
            for (i = adj[idmapreverse[v]].begin(); i != adj[idmapreverse[v]].end(); ++i)
                if (!visited[idmapreverse[(*i)]])
                    DFSUtil((*i), visited);
        }
};


int main(int argc, char const *argv[])
{
   map<int, Graph> graphs;
   map<int, BooleanGraph> boolean_graphs;

   int K, Q;
   cin >> K >> Q;

   for(int k=0; k<K; k++) {
      int V, E, t;
      cin >> V >> E >> t;

      if(t == 0) {
         Graph G(V,E);
         // read all node id's of current graph
         for(int i=0; i<V; i++) {
            int v;
            cin >> v;
            // Uncomment this part after you have implemented add_vertex() function
             G.add_vertex(i,v);
         }
         // read all edges of current graph
         for(int i=0; i<E; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            // Uncomment this part after you have implemented add_edge() function
             G.add_edge(u, v, w);
         }
         // add graph to your container data structure
         graphs[k] = G;
      }
      else {
         BooleanGraph G(V,E);
         // read all node id's of current graph
         for(int i=0; i<V; i++) {
            int v;
            cin >> v;
            // Uncomment this part after you have implemented add_vertex() function
            G.add_vertex(i,v);
         }
         // read all edges of current graph
         for(int i=0; i<E; i++) {
            int u, v, w;
            cin >> u >> v;
            // Uncomment this part after you have implemented add_edge() function
             G.add_edge(u, v);
         }
         // add graph to your container data structure
         boolean_graphs[k] = G;
      }

   }

   // Debugging checkpoint: Print all the graphs to verify correctness of input

   // Read queries one by one
   for(int q=0; q<Q; q++) 
   {      
      string query;
      cin >> query;

      if(query == "WEIGHT")
      {
         int u, v, i;
         cin >> u >> v >> i;
         if(graphs.find(i) != graphs.end()) {
            // write your code to print weight of (u,v) edge in graph i
             graphs[i].weight(u,v);
         }
         else {
            // write your code to print weight of (u,v) edge in boolean graph i
             boolean_graphs[i].weight(u,v);
         }
      }

      else if(query == "ADJOUT")
      {
          //cout << "HI";
         int u, i;
         cin >> u >> i;
         if(graphs.find(i) != graphs.end()) {
            // write your code to print weight of (u,v) edge in graph i
            // adj should be the adjacency list of node u (in sorted order) in graph i
            // Uncomment this part after you have implement operator overloading for []
            // vector<int> adj = graphs[i][u];
             graphs[i].adjout(u);
         }
         else {
            // write your code to print weight of (u,v) edge in boolean graph i
            // adj should be the adjacency list of node u (in sorted order) in graph i
            // Uncomment this part after you have implement operator overloading for []
            // vector<int> adj = graphs[i][u];
             //cout << "hi";
             boolean_graphs[i].adjout(u);
         }
      }

      else if(query == "DEGSEQ")
      {
         int v, i;
         cin >> v >> i;
         if(graphs.find(i) != graphs.end()) {
            // write your code to print degree sequence of node u in graph i
             graphs[i].degseq(v);
         }
         else {
            // cout << "hi";
             boolean_graphs[i].degseq(v);
            // write your code to print degree sequence of node u in boolean graph i
         }
      }

      else if(query == "DFS")
      {
         int u, i;
         cin >> u >> i;
         if(graphs.find(i) != graphs.end()) {
            graphs[i].DFS(u);
             cout << endl;
         }
         else {
             //cout << "hi";
             boolean_graphs[i].DFS(u);
             cout << endl;
            // write your code to print dfs traversal tree from node u in boolean graph i
         }
      }

      else if(query == "ADD") {
         int i, j, k;
         cin >> i >> j >> k;
         // checking whether the graphs i,j,k are of Graph class
         // checking just for i because in the input format all i,j,k are of same type
         if(graphs.find(i) != graphs.end()) {
            // add graphs i and j, store in k
            // Uncomment this part after you have implemented operator overloading for binary +
             graphs[k] = graphs[i] + graphs[j];
         }
         else {
            // add boolean graphs i and j, store in k
            // Uncomment this part after you have implemented operator overloading for binary +
            // boolean_graphs[k] = boolean_graphs[i] + boolean_graphs[j];
         }

         // graphs[9].adjout(5);
         // Debugging checkpoint: Print and verify that graph k is overwritten
      }

      else if(query == "SUB") {
         int i, j, k;
         cin >> i >> j >> k;
         // checking whether the graphs i,j,k are of Graph class
         // checking just for i because in the input format all i,j,k are of same type
         if(graphs.find(i) != graphs.end()) {
            // subtract graphs i and j, store in k
            // Uncomment this part after you have implemented operator overloading for binary -
             graphs[k] = graphs[i] - graphs[j];
         }
         else {
            // subtract boolean graphs i and j, store in k
            // Uncomment this part after you have implemented operator overloading for binary -
            // boolean_graphs[k] = boolean_graphs[i] - boolean_graphs[j];
         }

         // Debugging checkpoint: Print and verify that graph k is overwritten
      }

      else if(query == "NEG")
      {
         int i, k;
         cin >> i >> k;
         if(graphs.find(i) != graphs.end()) {
            // negate a graph
            // Uncomment this part after you have implemented operator overloading for unary -
            // graphs[k] = -graphs[i];
         }
         else {
            // negate a graph
            // Uncomment this part after you have implemented operator overloading for unary -
            // boolean_graphs[k] = -boolean_graphs[i];
         }
      }

      else if(query == "NCOMP")
      {
         int i;
         cin >> i;
         if(graphs.find(i) != graphs.end()) {
            // write your code to print number of components in graph i
             graphs[i].ncomp();
         }
         else {
            // write your code to print number of components in boolean graph i
         }
      }
   }

   return 0;
}

