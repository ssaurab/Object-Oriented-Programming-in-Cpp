/*
* CREATED BY S SRINIVAS SAURAB
* IIT MADRAS CS16B039 05-03-2018
*/
#include <iostream>
#include <bits/stdc++.h>
#include <stack>

using namespace std;

class Employee {

private:
	int sup_id; // unique obj_id of the supervisor
	int obj_id; // a unique id for the object, that helps maintain and identify
	//the hierarchy (it won’t change)
	int obj_val; // the employee id needs to be stored here (it’s the data value
	//of the object, that may change). This is required to be printed/operated
	//on.
	Employee *left_subordinate;
	Employee *right_subordinate;
		
	int height; //0 for the CEO and so on, will be used only if one of the steps requires it 
public:
	// your functions go here ..
	//constructor method
	/*Employee (int id, int sup_id,int level){
		sup_id = sup_id;
		obj_id = id;
		level  = level;
	}*/

	void put_sup_id(int n){
		sup_id = n;
	}
	int get_sub_id(){
		return sup_id;
	}
	void put_height(int n){
		height = n;
	}
	int get_height(){
		return height;
	}
	void put_obj_id(int n){
		obj_id = n;
	}
	int get_obj_id(){
		return obj_id;
	}
	void put_obj_val(int n){
		obj_val = n; 
	}
	int get_obj_val(){
		return obj_val;
	}
	Employee * get_right(){
		return right_subordinate;
	}
	Employee * get_left(){
		return left_subordinate;
	}
	void set_left(Employee* parent){
		left_subordinate = parent;
	}
	void set_right(Employee * parent){
		right_subordinate = parent;
	}

};

//The main class that has all the private data of the organisation and the methods to perform the required computations
class Organisation{
 
    private:
        int root_index;
        vector <int> list;
        vector <Employee> org; // has all the data about the tree formation
        int n; //no of employees
        int tempint;
public:
//the constructor function that takes in the input and forms a tree and also inititates the heights  
Organisation(int no)
{     
    n = no;
	for(int i = 0; i < n; i++)
    {
		cin >> tempint;
		list.push_back(tempint);
	}
    Employee temp;
    //initiating the objects in the employees present in the array
	for(int i = 0; i < n; i ++)
	{
		temp.put_sup_id(list[i]);
		temp.put_obj_val(i);
		temp.put_obj_id(i);
		temp.set_right(NULL);
		temp.set_left(NULL);
        org.push_back(temp);
	}
    //loading the left, right and parent pointers
	for(int i = 0; i < n; i++)
	{
		if(org[i].get_sub_id() >= 0)
		{
			if(org[org[i].get_sub_id()].get_left() == NULL)
			{
				org[org[i].get_sub_id()].set_left(&org[i]);
			}
			else
			{
				org[org[i].get_sub_id()].set_right(&org[i]);	
			}
		}
		else root_index = i;
	}
    //initating heights
    for(int i = 0; i < n; i++)
	{
		org[i].put_height(maxDepth(&org[i]));
	}
    }
    
    int get_root_index(){
        return root_index;
    }
    Employee* get_head(){
        return &org[root_index];
    }
/*......................................THE PRINTING FUNCTIONS.....................................*/
//PRE ORDER PRINTER USING A STACK (STEP 3)
 void iterativePreorder(Employee *root)
 {   
    if (root == NULL)
       return;

    stack<Employee *> EmployeeStack;
    EmployeeStack.push(root);
 
    while (EmployeeStack.empty() == false)
    {
        Employee *Employee = EmployeeStack.top();
        EmployeeStack.pop();
        cout << Employee->get_obj_id()<<" ";
 
        //recursively print the element, push it's right followed by left
        if (Employee->get_right())
            EmployeeStack.push(Employee->get_right());
        if (Employee->get_left())
            EmployeeStack.push(Employee->get_left());
    }
}
//IN ORDER PRINTING USING A STACK (STEP 5)
 void inorderIterative(Employee *root)
 {
	stack<Employee*> EmployeeStack;
	Employee *curr = root;
  
	while (!EmployeeStack.empty() || curr != NULL)
	{	   
		if (curr != NULL)
		{
			EmployeeStack.push(curr);
			curr = curr->get_left();
		}
		else
		{
            curr = EmployeeStack.top();
			EmployeeStack.pop();
			cout << curr->get_obj_val() << " ";
			curr = curr->get_right();
		}
	}
}

void printLevelOrder(Employee *root)
{
    if (root == NULL)  return;
 
    //current denotes the queue number, it can be 1 or 2
 	int current = 1;
 	int level = 0;
 	int level_product[100];
    queue<Employee *> q1;
    queue<Employee *> q2;

 //we use two queues filled alternatively such that if one queue is empty we get to know that one level is complete
    q1.push(root);
    level_product[0] = 1;
 //we also simultaniously store the level product of ids in the array as we know when the level is complete i.e next level is reached
    //this is the advantage of using two queues
    while (q1.empty() == false  || q2.empty() == false)
    {
      if(current == 1)
      {
      	if(q1.empty() == true) {
      		current++;
      		level++;
      		level_product[level] = 1;
     	}
     else{
      		Employee *node = q1.front();  
      		level_product[level] *= node->get_obj_id();
    	    cout << node->get_obj_id() << " ";
	        q1.pop();
 
        	if (node->get_left() != NULL)
        	{
           	 q2.push(node->get_left());
 	       }
 
        	if (node->get_right() != NULL)
        	    q2.push(node->get_right());
      		}
  		}	
       else if(current == 2)
       {
    //in case the queue is emptied use the other queue
       	if(q2.empty() == true) {
      		current--;
      		level++;
      		level_product[level] = 1;     		
     	}
     	else{
       	Employee *node = q2.front();
       	level_product[level] *= node->get_obj_id();  
        cout << node->get_obj_id() << " ";
        q2.pop();
 
        if (node->get_left() != NULL)
        {
            q1.push(node->get_left());
        }
        if (node->get_right() != NULL)
            q1.push(node->get_right());
       }
       }
    }  
//printing the level wise products
    cout << endl;
    for(int i = 0; i <= level; i ++)
   	{
   		cout<<i+1<<" "<< level_product[i]<< " ";
   	} 
}

int maxDepth(Employee* Emp) 
{
   if (Emp == NULL) 
       return 0;
   else
   {
       int leftDepth = maxDepth(Emp->get_left());
       int rightDepth = maxDepth(Emp->get_right());
 
       if (leftDepth > rightDepth) 
           return(leftDepth+1);
       else 
       		return(rightDepth+1);
   }
}  

int find_diameter()
{
	//finding the diameter by maximising lheight+ rheight among all the nodes of the tree
	//the algo for the same iterating in the same order as given in the list
	int temp_max = 0;
	for(int i = 0; i < n; i++)
	{
        Employee * root = &(org[i]);
		if(root->get_left() != NULL && root->get_right() != NULL)
			temp_max = max(temp_max, root->get_left()->get_height()+root->get_right()->get_height()+1);
		else if(root->get_left()!= NULL)
			temp_max = max(temp_max, root->get_left()->get_height()+1);
		else if(root->get_right()!=NULL)
			temp_max = max(temp_max, root->get_right()->get_height()+1);
		else 
			temp_max = max(temp_max, 0);
	}
	return temp_max;
}

int modify(Employee * root){

	int temp,templeft,tempright;

//base case
	if(root->get_right() == NULL && root->get_left() == NULL)
	{
		return root->get_obj_val();
	}

	else if(root->get_right() == NULL)
	{
		 temp = modify(root->get_left());
	}
	else
	{
		//recurse down
		 templeft = modify(root->get_left());
		 tempright = modify(root->get_right());
		 temp = templeft + tempright;
	}
//in case the rule that no id has to decrease is violated above
	if(temp < root->get_obj_id())
	{
		//iterate down and increase the left most progenys value as needed
		int diff = root->get_obj_id() - temp;
		Employee * iterator = root->get_left() ;
		while(iterator != NULL)
		{
			iterator->put_obj_val(diff+iterator->get_obj_val());
			iterator = iterator -> get_left();
		}
		return root->get_obj_val();
	}
	else //otherwise just = lvalue+rvalue
	{
		root->put_obj_val(temp);
		return temp;
	}
	return temp;
}
    
};

int main(){
	int n;
	
	scanf("%d\n",&n);

    Organisation O(n);
    //calling the method and printing the values as needed
    int root_index = O.get_root_index();
    Employee * root = O.get_head();
	cout << O.maxDepth(root);
	cout << endl;
	O.printLevelOrder(root);
	cout << endl;
	O.iterativePreorder(root);
	cout<< endl;
	int p = O.modify(root);
	O.inorderIterative(root);
	cout <<endl;
	
	cout << O.find_diameter();
	cout << endl;

	return 0;
}



