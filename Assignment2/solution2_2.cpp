/*..................................PROBLEM 2........................................*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define INF pow(55,2) //arbitrarily large number


//the auxiliary functions that help us in the operand overwriting
long int FindMaximum(long int prev_max, long int * B, long int columns);
char ThereIsMaximum(long int prev_max, long int * B, long int columns);
void rotate_array(long int * Arr, long int size);

//the ONLY class, it that has four overwritten operands within it
class Matrix{
   private:
    //we store the matrix as a 2D array
      long int m, n; 
      long int A[100][100]; 
      
   public:
      
      //the constructor function
      Matrix(long int a, long int b)
      {        
         m = a; n = b;

         for(long int i = 0; i<m ; i++)
         {
            for(long int j = 0; j<n; j++)
            {
               long long int element;
               cin >> element;
               A[i][j] = element;
            }
         }
      }

    //the printer function
      void printMatrix(){

         for(long int i  = 0; i < m; i++)
         {
            for( long int j = 0; j < n; j++)
            {
               cout << A[i][j]<< " ";
            }

            cout << endl;
         }
    }




      //the overwritten operator functions for the set {+, &, -, *}
      Matrix operator + (Matrix M) {

         //performs special addition (SPC)

        long int column_count;

         if(n < M.n) column_count = n;
         else column_count = M.n;                   //deciding the number of columns in the resultant matrix

         for(long int i = 0; i < m; i++)
         {
             
      // the loop that reads the corresponding row from matrix1 and gets the highest absolute valued number in it
            for(long int cc = 0; cc < column_count; cc++)
            {
                long int max_from, max_row, max_column;

                long int temp = 0;
              for(long int j = 0; j<n; j++)    
              {
                 if(abs(A[i][j])>temp)
               {
                  temp = abs(A[i][j]);
                  max_row = i;
                  max_column = j;
                  max_from = 0; 
               }

               //cout << "temp"<< temp;

               if(abs(A[i][j])==temp)
               {
                  if(A[i][j] > 0)
                  {
                     temp = A[i][j];
                     max_row = i;
                     max_column = j;
                     max_from = 0;
                  }
                }
              }

    //the loop that reads the Matrix2 to get the maximum absolute valued element and compares it with that obtained from Matrix1
            for(long int k = 0; k < M.n; k++)
            {
               if(abs(M.A[i][k])>temp)
               {
                  temp = abs(M.A[i][k]);

                  max_row = i;
                  max_column = k;
                  max_from = 1; 
               }

               if(abs(M.A[i][k])==temp)
               {
                  if(M.A[i][k] > 0)
                  {
                     temp = M.A[i][k];
                     max_row = i;
                     max_column = k;
                     max_from = 1;
                  }
               }
            }                                //by this point temp variable has the next maximum, ready to enter the resultant matrix

         if(max_from == 0 && A[max_row][max_column]<=0 || max_from == 1 && M.A[max_row][max_column] <= 0)
         cout << (-1)*temp<< " ";

         else cout << temp <<" " ;        //multiplying temp with -1 if needed as we only have absolute value in temp variable

         if(max_from == 0){
            A[max_row][max_column] = 0;
         }

         else
            M.A[max_row][max_column] = 0;

         
         }
         cout << "\n";
         }
          return M;
      }

      long int operator & () {


         //finds the maximum sum of the given matrix(MSM)
         //prints the value of such maximum sum 
         //if the conditionis not satisfied by any of the rows prints "NO" and returns -1

         long int prev_max = pow(2,56);
         //cout << prev_max ;
         long int sum = 0;
         long int current_max = 0;
         char h;
   
   //the loop that starts from the last row and detects if any element satisfies the condition and returns the maximum of such elements
         for(long int i = m-1; i >= 0; i--)
         {
            h = ThereIsMaximum(prev_max, &A[i][0], n);

            if(h == 'N' && i != m-1) {cout << "NO"<<endl; return 0;}

            current_max = FindMaximum(prev_max, &(A[i][0]), n);

            prev_max = current_max;

            sum += current_max;
         }

         cout<<sum<<endl;

         return 0;
      }

      Matrix operator - (Matrix M){
         //the algorithm that takes in the kernel matrix
         //does the convolution as needed and outputs the resultant matrix
         //returns the resultant matrix

 //we see four nested loops the first two of them help in navigating the base matrix whereas the inner two help in navigating kernel matrix
         for(long int main_row = 0; main_row < m-M.m+1; main_row++)
         {
            for(long int main_column = 0; main_column < n-M.n+1; main_column++)
            {
               long int sum = 0;
               for(long int small_row = 0; small_row < M.m; small_row++)
               {
                  for(long int small_column = 0; small_column <M.n; small_column ++)
                  {

                     sum += M.A[small_row][small_column]*A[main_row+small_row][main_column+small_column];
//multiplying and adding it into the sum and returning the sum with suitable spacing
                  }
               }
            
                  cout << sum << " "; 
            }
            cout << endl;
         }

          return M;
      }

      long int operator * (long int k){
      //takes in the main matrix and does the required number of rotations as needed

       //subject to corner cases with need to deal with column and row matrices seperately as we see in the below two if statements
      if( m == 1)
      {
         long int array[n];

         for(int i = 0; i < n; i++)
         {
            array[i] = A[0][i];
         }

         for(long int j = 0; j < k; j++)
         {
            rotate_array(array, n);
         }

         for(int l = 0 ; l< n ; l ++)
         {
            cout << array[l] <<" ";
         }
         cout << endl;
         return 0;
      }

      if( n == 1)
      {
         long int array[m];

         for(int i = 0; i < m; i++)
         {
            array[i] = A[i][0];
         }

         for(long int j = 0; j < k; j++)
         {
            rotate_array(array, m);
         }

         for(int l = 0 ; l < m ; l++)
         {
            cout << array[l] <<" "<<endl;
         }
         
         return 0;
      }

          //if the matrix is neither column nor row matrix it reaches this point
      long int array[2*(m+n) - 4];
//from here we store the perimeter elements into an array of corresponding size
      for(long int i = 0; i < n; i++){
         array[i] = A[0][i];
      }

      for(long int i = 1; i<m; i++){
         array[n+i-1] = A[i][n-1];
      }

      for(long int i = n-2; i >= 0 ; i--){
         array[2*n+m-3-i] = A[m-1][i];
      }

      for(long int i = m-2; i > 0; i--){
         array[2*n+2*m-4-i] = A[i][0];
      }

//we perform the needed number of rotations to the array using the function below
      for(long int i = 0; i < k; i ++)
      {
         rotate_array(array, 2*(m+n) - 4);
      }

      for(long int i = 0; i < n; i++){
         A[0][i] = array[i];
      }

      for(long int i = 1; i<m; i++){
          A[i][n-1] = array[n+i-1];
      }

      for(long int i = n-2; i >= 0 ; i--){
         A[m-1][i] = array[2*n+m-3-i] ;
      }

      for(long int i = m-2; i > 0; i--){
          A[i][0] = array[2*n+2*m-4-i];
      }

      printMatrix();
      return 0;
      }

};

//function that can find the maximum element in a row of a matrix that is lesser than the variable prev_max
long int FindMaximum(long int prev_max, long int *B, long int columns){
   
        long int temp = -INF;
        long int temp1 = *B;
        for(long int k = 1; k < columns; k++)
         {
            if((temp < *(++B))&& prev_max > *(B)) { 
            temp = *(B);
            } 
         } 
    
      if(temp1 > temp && temp1 < prev_max) temp = temp1;

      return temp;
}
//function to say if such number exists
char ThereIsMaximum(long int prev_max, long int * B, long int columns){
   
      long int temp = -INF;       
      char h = 'N';
    
    if(*B < prev_max) h = 'Y';
    
      for(long int k = 1; k < columns; k++)
      {
         if((temp < *(++B))&& prev_max > *(B)) {            
            h = 'Y';
            temp = *(B);
         } 
      }                    
      return h;
}

//to perform array shifting except that the last elements comes back to first (hence named rotate_array)
void rotate_array(long int * Arr, long int size){

   for(long int i = size-1; i >= 0 ; i--)
   {
      Arr[i+1] = Arr[i];
   }

   Arr[0] = Arr[size];
}

int main(){
  int n; 
  cin >> n;

//depending on the input string we catogerize which operand is being used in that subproblem
   for(int i = 0; i < n; i ++)
   {
      string s;
      cin >> s;

      if(s == "MSM")
      {
         long int n,m;

         cin >>m >>n;
         Matrix M1(m,n);

         &(M1);
      }

      if( s == "SPC")
      {
         long int m1, n1, m2, n2;

         cin >> m1 >> n1;
         Matrix M1 (m1, n1);

         cin >> m2 >> n2;
         Matrix M2(m2, n2);

         M1+M2;
      }

      if(s == "ROT")
      {
         long int n,m;

         cin >>m >>n;
         Matrix M1(m,n);

         long int k ;
         cin >> k;
          
          if(m > 1 && n > 1)
          k = k % (2*m+2*n-4);  //to save time because after 2m+2n-4 rotation the original matrix is restored

         M1 * k;
      }

      if(s == "CONV")
      {
         long int m1, n1, m2, n2;

         cin >> m1 >> n1;
         Matrix M1(m1, n1);

         cin >> m2 >> n2;
         Matrix M2(m2, n2);
  //sending the kernel as the second matrix and base as first owing to the method we wrote the operand overwriting    
         if(m2 > m1 || (m1 == m2 && n2 > n1))   
         {
             M2-M1;
         }
         else 
         {
             M1-M2; 
         }
      }
   }

   return 0;
}


