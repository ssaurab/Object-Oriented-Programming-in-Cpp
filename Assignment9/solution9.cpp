/*
*	CREATED BY S SRINIVAS SAURAB
*	IIT MADRAS 12 Mar 2018
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;
//functor class
class sorter {    
    public:    
    bool operator ()(pair<int, int>& p1, pair<int, int>& p2)
    {   
        if(p1.first < p2.first) return true;
        else return false;
    }
};

class Graph {
    private:
        int V;   //number of vertices
        vector <vector<int> > adj; //adjacency list for representing graph
        int n, r, k; //r represents the number of edges
       vector <vector<int> > roots;
    // vector of component vectors, has all the information about the componenets 

    public:
    //the constructor function that takes in the input too
        Graph(int V){
        	n = V;
        	adj.resize(V+1);	
        	scanf("%d %d\n", &r, &k);
        	int v1,v2;
        	for(int i = 0; i < r; i++)
        	{
        		cin >> v1>> v2;
        		add_edge(v1, v2);
        		add_edge(v2, v1);
        	}
        }
        void add_edge(int v, int w){
            
        	adj[v].push_back(w);
        } 
//applies DFS iteraing on the list of vertices and demarcates the components and stores every component in a vector
        int countTrees()
		{
		    vector<bool> visited(n+1, false);
		    int res = 0;
		    for (int u=1; u<=n; u++)
		    {
		        if (visited[u] == false)
		        {
		        	vector <int> temp;
		        	temp.push_back(u);//the vector to be filled by the next component's members
		            DFS(u, visited, temp);
		            roots.push_back(temp);// push it in
		            temp.clear();// clear it so that the next component can get a new empty vector temp
		            res++;
		        }
		    }
		    return res;
		}
    //the DFS algorithm that demarcates the component
        void DFS(int u, vector<bool> &visited, vector <int> &temp){
	        visited[u] = true; 
	   		for (int i=0; i<adj[u].size(); i++)
	   		{
	           if (visited[adj[u][i]] == false)
	           	 {
	           	 	temp.push_back(adj[u][i]);
	           	 	DFS(adj[u][i], visited, temp);
	           	 }
	   		}
        }

//Djikstra's like algorithm 
//identifies and prints all the vertices reachable in k edges from the source as described in Q
        void shortestPaths(int src)
		{
		    
		    vector<int> dist(n+1, pow(2,23));
		 	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
		    pq.push(make_pair(0, src));
		    dist[src] = 0;
//uses a priority queue that automatically sorts the pairs
		    while (!pq.empty())
		    {
		        int u = pq.top().second;
		        pq.pop();
		        for (int i = 0; i != adj[u].size(); i++)
		        {
		            int v = adj[u][i];
		            if (dist[v] > dist[u] + 1)
		            {
		                dist[v] = dist[u] + 1;
		                pq.push(make_pair(dist[v], v));
		            }
		        }
		    }
            int flag = 0;
		    for (int i = 1; i <= n ; i++)
            {
                if(dist[i] <= k && dist[i] != 0)
                {
                    printf("%d ", i);
                    flag++;
                }
            }
            if(flag == 0) cout << "-1";
		}
//identifies the biggest island and it's root, also calls the shortest paths function
//it also returns the root of the smallest island
    
        int print_bfs_biggest_island_andGetSmallestSrc(){
        	int maximum = 0, max_root_index = 0;
        	int count1 = 0, count2 = 0;
        	for(int i = 0; i < roots.size(); i++)
        	{

        		int p = roots[i].size();
        		
        		if(maximum == p) 
        		{
        			
        				if(*max_element(roots[i].begin(), roots[i].end()) > *max_element(roots[max_root_index].begin(),roots[max_root_index].end()))	
        				{
        					max_root_index = i;
        				}
        			count1++;

        		}
               else {maximum = max(maximum, p);if(maximum == p)max_root_index = i;}
        	}
        	//cout << maximum;
        	int minimum = pow(2,20);
        	for(int i = 0; i < roots[max_root_index].size(); i++)
        	{
        		minimum = min(minimum,roots[max_root_index][i]);
        	}
        	shortestPaths(minimum);
        	int mini = pow(2,20); int min_root_index = 0;
        	for(int i = 0; i < roots.size(); i++)
        	{
        		int p = roots[i].size();
        		if(mini == p) 
        		{
    //if there is a clash to decide the smallest island then compare the maximum elements in the two
        			if(*min_element(roots[i].begin(),roots[i].end()) < *min_element(roots[min_root_index].begin(),                                    roots[min_root_index].end()))
        				{
        					min_root_index = i;
        				}
        		}
                else {mini = min(mini, p); if(mini == p)min_root_index = i;}
        	}
            
        	int maxx = -1;
        	for(int i = 0; i < roots[min_root_index].size(); i++)
        	{
        		maxx = max(maxx,roots[min_root_index][i]);
        	}
//return the root of the smallest island
        	return maxx;
        }
//function that initiates few auxiliary vectors and calls the DFS function to find pre and post values of the vertices
//also prints those timestamps
        void callmodDFS(int src){

        	vector<bool> visited(n+1, false);
        	vector <pair<int, int> > found;
        	vector <pair<int, int> > finished;
        	int time = 0; int count = 0;
        	modDFS(src, visited,time, found, finished, count);
        	sorter s;
			sort(found.begin(), found.end(), s);
			sort(finished.begin(), finished.end(), s);
			for(int i = 0; i < count; i++)
			cout<<found[i].first<<" "<<found[i].second<<" "<< finished[i].second<< endl;
        }
//finds the found and finished times of the nodes and puts them into vectors sent by reference
        void modDFS(int u, vector<bool> &visited, int &time, vector<pair<int, int> > &found ,vector<pair<int,int> >&finished, int& count){

            count ++;      
	        visited[u] = true; 
	        found.push_back(make_pair(u, time));
            time+=2;//because she spends two hours in a city
	        int flag = 1;
		   sort(adj[u].begin(), adj[u].end());
	   		for (int i=0; i<adj[u].size(); i++)
	   		{
	           if (visited[adj[u][i]] == false)
	           	 {      
	           	 	flag *= 0;
	           	 	time += 1;//every time we encounter a new road the timestamp increases by one
	           	 	modDFS(adj[u][i], visited, time, found, finished, count);
	           	 }  
	   		}
	   		finished.push_back(make_pair(u, time));
            time++;
        }
//using the theorem that if there are lesser edges than nodes-components then there are no cycles in the graph
//this finds if there is any cycle in the graphs i.e presence of a cyclic island 
    void cyclic()
    {
        if(r>(n-countTrees()))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }					  
};

int main(){

	int n;
	scanf("%d", &n);

	Graph G(n);
//counts the number of components and also creates a vector for each component 
	cout << G.countTrees()<< " ";
//checks for any cyclic islands
    G.cyclic();
//prints the nodes reachable in the biggest island within k distance, also src gets the source of the smallest island
    int src =  G.print_bfs_biggest_island_andGetSmallestSrc();
    cout<<endl;
	G.callmodDFS(src);

	return 0;
}
