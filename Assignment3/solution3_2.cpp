#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{	
	public:
    int r,c;
    vector < vector<int> > array2d;

//the constructor function that populates our main array named array2d
       Matrix(){

            cin >> r >> c; 
            int temp1;
            
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

class SORTED_ARRAY : public Matrix {
    
    public :
    
    //the query search function that does it in O(m+n) time and O(1) auxiliary space
    pair<int,int> sorted_search(){
        
        long int element;
         cin >> element;
        
        int i ;
        i = 0;
        int j = c-1;
    //the algorithm runs a iteration starting from one of the diagonal elements and navigating upto the query element(if it exists)
         while(i != r && j != -1)
         {
             if(array2d[i][j] == element) {return make_pair(i, j);}  //if found return the coordinate pair

              if(array2d[i][j] > element) {j--;} //if the query element is smaller then traverse to left

              if(array2d[i][j] < element) {i++;} //if the query element is bigger then traverse down
          }
//note that the iteration traverses utmost from one corner to diagonally opposite corner thus taking a maximum of m+n steps thus yielding O(m+n)
        return make_pair(-1, -1); //the iterations will exit the above loop only if the query element is absent in the loop
    }
  
    
};


int main(){
    
    Matrix array2d(); //creates and populates the array array2d
 
    SORTED_ARRAY A1; //initialises a object in whose scope we perform the sorted search operation
    pair<int,int> p = A1.sorted_search();
    cout << p.first << " "<< p.second<< endl;

   return 0;
}

