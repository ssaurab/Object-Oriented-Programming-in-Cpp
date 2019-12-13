/*
*	CREATED BY S SRINIVAS SAURAB
*	IIT MADRAS 12 Mar 2018
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> iPair;
typedef pair<float, int> ifPair;	
typedef pair<int, float> fPair;

class sorter {    
    public:    
    bool operator ()(const pair<int, int>& p1, const pair<int, int>& p2)
    {   
    	if(p1.second == p2.second)
             return p1.first < p2.first;
        else return(p1.second > p2.second);
    }
};
class Graph {
 private:
    int V;   //number of vertices
    vector <vector<fPair> > adj; //adjacency list for representing graph
    vector <vector<int> >category;//has a vector of vertex numbers corresponding to each category
    int n, r; //r represents the number of edges
    vector <vector< float> > distance;
    vector< vector< float> > next;
    bool need_to_update = true;
    //this boolean variable shows if there is an update function after the most recent apsp function
    //this enables us to reuse the matrices from apsp call i.e floyd warshall matrices
      
    public:
    //the constructor function that takes in the input too
        Graph(int V){
        	n = V;
        	adj.resize(V+1);
        	category.resize(V+1);	
        	scanf("%d\n", &r);
        	int categorytmp;
            vector <int> temp;
            
        	for(int j = 0; j < n; j++)
        	{
        		cin >> categorytmp;
        		category[categorytmp].push_back(j+1);
        	}
            
        	int v1,v2;
        	float w;
        	for(int i = 0; i < r; i++)
        	{
        		cin >> v1>> v2 >> w;
        		add_edge(v1, v2, w);	
        	}
        }
        void add_edge(int v1,int v2, float w){
            
            fPair f = make_pair(v2, w);//to store weights too
        	adj[v1].push_back(f);
        } 
    //print indicates if it is a sssp function or update function so that we can optimize code space
        void min_time(int src, float optimal, int print)
		{
		  //like a regular dijkstras algorithm  
		    vector<float> dist(n+1, pow(2,20));
		 	priority_queue< ifPair, vector <ifPair> , greater<ifPair> > pq;
		    pq.push(make_pair(0, src));
		    dist[src] = 0;
//uses a priority queue that automatically sorts the pairs
		    while (!pq.empty())
		    {
		        int u = pq.top().second;
		        pq.pop();
		        for (int i = 0; i != adj[u].size(); i++)
		        {
		            int v = adj[u][i].first;
		            float weight = adj[u][i].second;
		            if (dist[v] > dist[u] + weight)
		            {
		                dist[v] = dist[u] + weight;
		                pq.push(make_pair(dist[v], v));
		            }
		        }
		    }
      //indicates that the command corresponds to sssp call
            if(print == 1){
		    for (int i = 1; i <= n ; i++)
            {
                if(dist[i] < pow(2,20) && dist[i] != 0)
                {
                    printf("%0.3f ", dist[i]);    
                }
                else if(dist[i] == 0) {cout << "0.000 ";}
                else 
                {
                    cout << "-1.000 "; 
                }
            }
            }
        //indicates that the command corresponds to update call
            else{
                need_to_update = true;
                int j;int found = 0;
            //first check the adjacency list
                for(j = 0; j < adj[src].size(); j++)
                        {
                            if(adj[src][j].second > optimal)
                            {
                                adj[src][j].second = optimal;
                                dist[adj[src][j].first] = optimal;    
                            }
                        }
    //then check every vertex...this ordering of the two loops ensure O(V) algorithm unlike the obvious v^2 one
                for(int i = 1; i < n+1; i++)
                {
                    if(dist[i] > optimal)  
                    {
                        add_edge(src, i , optimal);
                    }
                }
            }
		}
	void top_k(int ctg, int k)
		{
			vector <iPair> reference;//index, freq of each vertex in the graph
			
			for(int p = 0; p < n+1; p++)
            {
                iPair zero_pair = make_pair(p,0);
				reference.push_back(zero_pair);
            }//initialise

			for(int i = 0; i < category[ctg].size(); i++){

				int curr_main = category[ctg][i];
				for(int j = 0; j < adj[curr_main].size(); j++)
				{                  
					int curr = adj[curr_main][j].first;
					reference[curr].second++;
				}
			}//increment the frequencies as needed

			sorter s;//sort using functor
			sort(reference.begin(), reference.end(), s);
            int siz;
            for(int l = 0; l < reference.size(); l++)
            {
                if(reference[l].second == 0){siz = l;break;}
            }
            k = min(k, siz);//print the correct number of articles as needed
			for(int i = 0; i < k; i++)
			{
				cout << reference[i].first;
               if(i != k-1)
                cout<<" ";	
			}
		}

	void pairwise_dist(int c1, int c2)
	{
        if(need_to_update == true)//if the previous data cannot be reused
        {
            distance = vector<vector<float> >(n+1,vector<float>(n+1, pow(2,20)));
            next = vector<vector<float> > (n+1,vector<float>(n+1, -1));
			for(int i = 1; i < n+1; i++)
			{
				for(int j = 0; j < adj[i].size(); j++)
				{
                    int v = adj[i][j].first;
					distance[i][v] = adj[i][j].second;
					next[i][v] = v;
				}
            }
        //regular V^3 Floyd Warshall algo
			for(int k=1;k<=n;k++)
			{
			     for(int i=1;i<=n;i++)
			     {
			         for(int j=1;j<=n;j++)
			         {
				             if(distance[i][k]+distance[k][j]<distance[i][j])
				             {
				                   distance[i][j]=distance[i][k]+distance[k][j];
				                   next[i][j] = next[i][k];
				             }
                         
                            else if(distance[i][k]+distance[k][j] == distance[i][j])   
                            {
                                if(next[i][j] > next[i][k])
                                next[i][j] = next[i][k];
                            }
				         }
				     }
			}
            need_to_update = false;//as the data is now up-to-date
        }        
    //print the path using the next matrix's invariant property
			vector <int> path;
			for(int j1  = 0; j1 < category[c1].size(); j1++)
			{
				for(int j2 = 0; j2 < category[c2].size(); j2++)
				{
					int i1 = category[c1][j1];
					int i2 = category[c2][j2];
					if(next[i1][i2] == -1) 
                    {
                        cout << i1<< " "<< i2;
                        printf("\t");
                        cout <<"-1";
                    }
                    else 
                    {                       
                        int u = i1;
                        cout << i1<< " "<<i2<<"\t"<<i1<<" ";
                        while(u != i2)
                        {
                            u = next[u][i2];
                            cout << u << " ";
                        }
                    }
                    cout << endl;
				}
			}
		}
};

  int main(){
  		int n;
  		cin >> n;
  		Graph G(n);
  		string s;
  		int temp1, temp2;
        float temp3;
      //the commands are read one by one and processed
  		while(cin >> s >> temp1)
  		{
  			if( s == "sssp")
  			{
  				G.min_time(temp1, 1, 1);
                cout << endl;
  			}
  			else if(s == "update")
  			{
  				cin >> temp3;
  				G.min_time(temp1,temp3,0);
  			}
  			else if(s == "top-k")
  			{
  				cin >> temp2;
  				G.top_k(temp1, temp2);
                cout << endl;
  			}
  			else if(s == "apsp")
  			{
  				cin >> temp2;
  				G.pairwise_dist(temp1, temp2);
  			}
  		}
  	return 0;
  }

