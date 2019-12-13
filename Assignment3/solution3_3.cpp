#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

# define INT_MAX pow(33,2)
# define INT_MIN -1*pow(33,2) //defining extremes to values which array elements can't exceed

int BinarySearch(vector <int> V, int x, int start, int end){

			//the function that performs the binary search and returns the index if found

			if(V[start] > x) return -1;

			int mid;
			while (start <= end) {
			
       		   mid = (start + end) / 2;  
      		     if (x >= V[mid]) 
          		   start = mid+1 ;  
      		     else if (x < V[mid]) 
          		     end = mid - 1;  //the recursive loop will take care of any repeating elements (also in O(n) time)

 		      }

 		  return start-1; 
		}

class Matrix{	
	public:
    int r,c;
    vector < vector<int> > array2d;

//the constructor function that populates our main array named array2d
       Matrix(){
            int temp1;
            cin>>r>>c;
           array2d.resize(r);
           for ( int i = 0 ; i < r ; i++ )
               array2d[i].resize(c);

            for(int i = 0; i < r; i++)
            {
                  for(int j = 0; j < c; j++)
                  {
                     cin >> temp1; 
                     array2d[i][j] = temp1;
                  }
            }		    
        }   
};

class Client{ //the class that has functions to substitute STL functions

	public :

		int upper_bound(vector <int> V, long int &  x, int start, int &end){

		//the function that computes the upper bound by performing a binary search
	
			int i = BinarySearch(V, x, start, end);
			          
            //branching out in case of corner cases
			if(i == -1) i = start-1;
			if(i == end) i = -2;
			
			return i+1;  //adding one to all outputs going by the difference in definitions of upperbound and binary search
		}


};

class ROW_SORTED_ARRAY : public Matrix {
  
    public :
    
    // function to find median of the matrix
    int find_median()
   {
       Client C;
   
       long int min = INT_MAX, max = INT_MIN;
          
        for (int i=0; i<r; i++)
          {
    
             if (array2d[i][0] < min)
                min = array2d[i][0];    //find the minimum of the elements in first column
 
 
            if (array2d[i][c-1] > max)
                max = array2d[i][c-1]; //find maximum of elements in last column
          }  
 
          int d = (r * c + 1) / 2;
          while (min < max)     //the loop runs until the assumed median collides with the actual one
         {
             long int mid = min + (max - min) / 2; 
              //this is the assumed median that might change in further iterations
             long int place = 0;
 
           for (int i = 0; i < r; ++i)
             {   
               int k = C.upper_bound(array2d[i],mid,0,c);
               //estimating the number of elements less than the assumed median
               if( k != -1) //the corner case in definition of upper bound
               place += k;
               else place += c; //computing the number of elements that are less than assumed median
           }
              
        if (place < d)
            //recursively incrementing the value of median in case the assumed median lies to left of actual median
            min = mid + 1;
        else //otherwise decrementing
            max = mid;
        }
        return min;
    }    
};


int main(){
    
 
    Matrix M(); //creates and populates a 2D array
    
    ROW_SORTED_ARRAY array; //initiates an object in whose scope we can use the find_median function
    int median = array.find_median(); //finds median and returns it

    cout<<median;

    return 0;
}

//the function find_median has a loop that takes the most significant time, in this we run a binary search for every column, thus it will take O(r*log c) time to execute the algorithm


