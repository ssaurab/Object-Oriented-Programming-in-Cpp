#include<iostream>
#include<climits>
#include<stack>
#include<queue>
using namespace std;
 
// A C++ class to represent k stacks in a single array of size n
class kStacks
{
    int *arr;   // Array of size n to store actual content to be stored in stacks
    int *top;   // Array of size k to store indexes of top elements of stacks
    int *next;  // Array of size n to store next entry in all stacks
                // and free list
    int n, k;
    int free; // To store beginning index of free list
public:
    //constructor to create k stacks in an array of size n
    kStacks(int k, int n);
 
    // A utility function to check if there is space available
    bool isFull()   {  return (free == -1);  }
 
    // To push an item in stack number 'sn' where sn is from 0 to k-1
    void push(int item, int sn);
 
    // To pop an from stack number 'sn' where sn is from 0 to k-1
    int pop(int sn);
 
    // To check whether stack number 'sn' is empty or not
    bool isEmpty(int sn)  {  return (top[sn] == -1); }
};
 
//constructor to create k stacks in an array of size n
kStacks::kStacks(int k1, int n1)
{
    // Initialize n and k, and allocate memory for all arrays
    k = k1, n = n1;
    arr = new int[n];
    top = new int[k];
    next = new int[n];
 
    // Initialize all stacks as empty
    for (int i = 0; i < k; i++)
        top[i] = -1;
 
    // Initialize all spaces as free
    free = 0;
    for (int i=0; i<n-1; i++)
        next[i] = i+1;
    next[n-1] = -1;  // -1 is used to indicate end of free list
}
 
// To push an item in stack number 'sn' where sn is from 0 to k-1
void kStacks::push(int item, int sn)
{
    // Overflow check
    if (isFull())
    {
        cout << "\nStack Overflow\n";
        return;
    }
 
    int i = free;      // Store index of first free slot
 
    // Update index of free slot to index of next slot in free list
    free = next[i];
 
    // Update next of top and then top for stack number 'sn'
    next[i] = top[sn];
    top[sn] = i;
 
    // Put the item in array
    arr[i] = item;
}
 
// To pop an from stack number 'sn' where sn is from 0 to k-1
int kStacks::pop(int sn)
{
    // Underflow check
    if (isEmpty(sn))
    {
         //cout << "\nStack Underflow\n";
         return INT_MAX;
    }
 
 
    // Find index of top item in stack number 'sn'
    int i = top[sn];
 
    top[sn] = next[i];  // Change top to store next of previous top
 
    // Attach the previous top to the beginning of free list
    next[i] = free;
    free = i;
 
    // Return the previous top item
    return arr[i];
}
 
int main()
{
    // Let us create 3 stacks in an array of size 10
    int k; int n = 200;

    cin >> k;

    kStacks ks(k, n);
 
    int inpu;
    cin >> inpu;
    int start = inpu;
    ks.push(inpu, 0);
    int d = 0;

    while(!(cin.eof()))
    {
	   	cin >> inpu;
	   	if(inpu == start) d++;
    	ks.push(inpu, d);
    }
     

 	stack <int> s1, s2;
 	int size_of_stack[k];
 	int size_of_strings[k];
 	int tempo[k];

 	for(int i = 1; i < k; i++)
 	{
 		
 		while(!(ks.isEmpty(0))) //pop into temp stacks ad measure their branch length
 		{
 			int pop_main = ks.pop(0);
 			s1.push(pop_main);
 		}

 		while(!(ks.isEmpty(i)))
 		{
 			int pop_side = ks.pop(i);
 			s2.push(pop_side);
 		}

 		int size_of_string = s2.size();
 		size_of_strings[i] = size_of_string;
 		int count = 0;

 		while(!(s1.empty()) || !(s2.empty()))
 		{
 			
 			int temp1,temp2;
 			if(!(s1.empty())){
 			temp1 = s1.top();
 			s1.pop();
 			ks.push(temp1, 0);}

 			if(!(s2.empty())){
 			temp2 = s2.top();
 			s2.pop();
 			ks.push(temp2, i);}

 			if(temp1 == temp2) count++; //to count the index where the strings merge
 		}
 		tempo[i] = size_of_string - count;
 		size_of_stack[i] = size_of_string - count;
 	}

 	queue <int> Que;


 	int temp_prev = 0;
 	int temp_now;

stack <int> s01;

 	while(!(ks.isEmpty(0))) 
 	{
 		int pop_main = ks.pop(0);
 		s01.push(pop_main);
 		//Que.push(pop_main);
 	}

 	while(!(s01.empty())) //pushing the main stack into the queue before branches are pushed
 	{
 		int temporary = s01.top();
 		s01.pop();

 		Que.push(temporary);

 	}


for(int s = 1; s < k; s++)
{
	temp_now = 101;
	int p;

 	for(int i = 1; i < k; i++)
 	{
 		if(tempo[i]<temp_now)
 		{ 
 			temp_now = tempo[i];
 			p = i;
 		}
 		  
 	}
	tempo[p] = 102;//putting number such that it is > 100
	

	stack <int> s11; //queing the elements

 		for(int q = 0; q < size_of_stack[p]; q++)
 		{
 			
 			int trash = ks.pop(p); 

 			s11.push(trash);
 		}

 		for(int g = 0; g < size_of_stack[p]; g++)
 		{
 			
 			int tempa = s11.top();
 			s11.pop();
 			Que.push(tempa);
 		}

 }

  while (!Que.empty()) //the loop that prints the final queue as needed
  {
    cout << Que.front() << " ";
    Que.pop();
  }

    return 0;
}
