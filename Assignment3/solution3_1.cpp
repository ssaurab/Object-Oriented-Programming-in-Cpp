#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ArraySearch {

	public :

		int BinarySearch(vector <int> V, int x, int start, int end, bool &flag){

			//the function that performs the binary search and returns the index if found
			//as the flag is supposed to be "set" we declare it as a variable in main
			if(V[start] > x) return -1;

			int mid;
			while (start <= end) 
            {
                
       		   mid = (start + end) / 2;  
      		     if (x >= V[mid]) 
          		   start = mid+1 ;  
      		     else if (x < V[mid]) 
          		     end = mid - 1;  //the recursive loop will take care of any repeating elements (also in O(n) time)

 		      }
             if(x == V[start-1]) flag = true;
 		     return start-1; 
		}

		int LinearSearch(vector <int> V, int x, int start, int end, bool &flag){

			//the function that performs the linear search and returns the index if found
			//as the flag is supposed to be "set" we declare it as a variable in main

			for(int i = end; i >= 0; i--)
			{
				if(V[i] <= x) 
                {                    
                    if(V[i] == x){                        
                        flag = true;
                    }
 //we start the search from the end and move to start until we find a element less than the query element                       
                        return i;                        
                }
			}
			return -1;
		}		
};

class Client{

	public :

		int lower_bound(vector <int> V, int x, int start, int end, bool &flag){

		//the function that computes the lower bound by performing a binary search
		//we pass another flag to avoid passing a variable by reference which itself is passed by reference
			
			ArraySearch A1;
			bool flag1 = true;
                     
			int i = A1.BinarySearch(V, x, start, end, flag1);
		
            flag = flag1;   //updating back the original flag
		    return i; //no more branching as the definitions of lowerbound and binary search match mathematically
		}

		int upper_bound(vector <int> V, int x, int start, int end, bool &flag){

		//the function that computes the upper bound by performing a binary search
		//we pass another flag to avoid passing a variable by reference which itself is passed by reference

			ArraySearch A1;
			bool flag1 = true;
			int i = A1.BinarySearch(V, x, start, end, flag1);
			
            flag = flag1;       //updating back the original flag
            
            //branching out in case of corner cases
			if(i == -1) i = start-1;
			if(i == end) i = -2;
			
			return i+1;  //adding one to all outputs going by the difference in definitions of upperbound and binary search
		}
};

int main(){

	vector <int> vec;
	ArraySearch A1;
	Client C1;

	int n;
	cin >> n;

	for(int i = 0; i < n; i++)
	{		
		int temp;
		cin >> temp;
		vec.push_back(temp); //taking in the elements into the array
	}

	string s;
	int element, start, end;
	cin>>s>>element>>start>>end;   //first scan -- binary search
	bool flag = true;	
	int i = A1.BinarySearch(vec, element, start, end-1, flag);
	cout << i;
	
	cin >> s;
	cin >> element>>start>>end;  //second scan -- linear search
	flag = true;
	i = A1.LinearSearch(vec, element, start, end-1, flag);
	cout << endl<< i ;
    
	cin >> s;
	cin>>element>>start>>end;  //third scan -- lower bound    
    flag = true;
	i = C1.lower_bound(vec, element, start, end-1, flag);
	cout << endl << i;

	cin >> s;
	cin >> element>>start>>end;  //fourth scan -- upper bound
	flag = true;
	i = C1.upper_bound(vec, element, start, end-1, flag); 
	cout <<endl<< i;    //all the outputs are printed simultaneously after every operation
    
    return 0;	
}

