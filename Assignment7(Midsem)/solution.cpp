#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>
#include <ctype.h>

using namespace std;

  map <string, int> assign_map;
bool is_number(string word);

class Token {
private:
   // DO NOT change this.
   string name;
   int type;     // 0 for variable; 1 for constant; 2 for operator.
   int value;
    char operate;
   // Feel free to add any other variables you may require.

public:
   // Enter your code here.
   
//all the get,set functions are to acess the private variables
    int get_type(){
        return type;
    }
    void set_type(int b){
     type = b;   
    }
    bool is_initialized(); // for variable
    bool is_valid(); // for operator
        //Token T;
//the operators + and - are overloaded for different types of parameters
    int operator + (Token b){
      
        int x =
         value+ b.get_value();
//T.set_value(x);
        return x;
        
    }
    int operator - (Token b){
        
        int x =
         value - b.get_value();
       // T.set_value(x);
        return x;
    }
    
    int operator + (int b){
      
//Token T;
        int x =
         value+ b;
        //T.set_value(x);
        return x;
        //return value + b;
    }
    int operator - (int b){
      
       // Token T;
        int x = value - b;
        //T.set_value(x);
        return x;
    }
    void set_value(int a){
        
        value = a;
    }
    int get_value(){
        return value;
    }
    void set_name(string a){
        
        name = a;
    }
    string get_name(){
        return name;
    }
    void set_operate(char a){
        operate = a;
    }
    char get_operate(){
        return operate;
    }
   // Write operator overloading functions for = operators.
};

  

class Expression {
private:
   vector<Token> exp_tok;
    int size = 0;
   // Feel free to add any other variables you may require.

public:
   // Enter your code here.
    void push_back(Token a)
    {
        exp_tok.push_back(a);
        size ++;
    }
    Token get_token(int i)
    {
        return exp_tok[i];
    }
    //this checks if the LHS is a single variable by detecting the position of "="
    int check_expression(){
        
        for(int i = 0; i < exp_tok.size(); i++)
        if(exp_tok[i].get_type() == 2 && exp_tok[i].get_operate() == '=' && i != 1)
        {
            cout << "invalid l-value";
            return 0;
        }
        return 1;
    }
//this does the rest of the checking and assigning and printing
    void rest_check(){
//firstly if it is an assignment statement
    if(exp_tok[1].get_operate() == '=')
      {
        //if the assignment is to a constant then it assigns directly
         if((exp_tok.size() == 3)){
         pair <string, int> assign;
         
         assign.first = exp_tok[0].get_name();
         assign.second = exp_tok[2].get_value();
         assign_map.insert(assign);
         }
        else{
    //the code reaches here is the RHS is an expression, it evaluates the expression and assigns it
            int x = exp_tok[2].get_value();
            int y = exp_tok[2].get_value();
            Token T;
            T.set_value(x);
            int plus_count = 0;
            int minus_count = 0;
             for(int i = 3; i < size; i = i+2)
             {
                
                if(exp_tok[i].get_operate() == '+') 
                {
                    x += T + exp_tok[i+1];
                    plus_count ++;
                }    
                 else{
                     T- exp_tok[i+1];
                     minus_count++;
                 }
                 
                 x = x -(plus_count+minus_count -1)*y;
             }
            
          // int temp = T.get_value();
            exp_tok[0] .set_value(x); 
            pair <string, int> assign;
            assign.first = exp_tok[0].get_name();
             assign.second = x;
             assign_map.insert(assign);
        }
         
     }
        
    else if(exp_tok[0].get_type() == 3)
    {
        //the code reaches here for print statements
        for(int i = 1; i < size; i++)
        {
            if(exp_tok[i].get_type() != 0) cout << "expression is not allowed for print";
            //if(assign_map.find(exp_tok[i].get_name()) == assign_map.end())
             //   cout << exp_tok[i].get_name()<< " is uninitialized";
            
                else cout << exp_tok[i].get_value() <<" "; 
        }
        cout << endl;
    }
        
    // else cout << "invalid command";   
    }
};


int main() {
   /* Sigh of relief! You dont have to read and parse on your own this time.
      We provide you with the code for reading and parsing the input.
   */
   string line;
   while(getline(cin, line)) {
      // Reading the input statement into vector of strings.
      istringstream iss(line);
      vector<string> tks{istream_iterator<string>{iss}, istream_iterator<string>{}};
    
        //cout<<tks[0]<<tks[1];
      // Enter your code here.
       
       Expression E;
       
    for(int i = 0; i < tks.size(); i++){
           
         Token T;
       if(is_number(tks[i]))
       {           
           T.set_type (1);
           int x = stoi(tks[i]);
//cout << x<<"dbug";
           T.set_value (x);
       }
        else if(tks[i] == "43" ||tks[i] == "45"||tks[i] =="61"){
            T.set_type (2);
            char x = tks[i][0];
            T.set_operate(x);
        }
        else{
            if(tks[i] != "print")
            {
                T.set_type(0);
                T.set_name (tks[i]);
            }
            else{
                T.set_type(3);
            }
        }
          E.push_back(T); 
    }
    //checks if the expression is correct 
     if(E.check_expression() == 0)return 0;       
     //does most of the checking and operations  
     E.rest_check();

      // HINT: You might find it useful to use unordered_map from STL.
   }

   return 0;
}
bool is_number(string w){

bool isNumber = true;
int k;    
for(k = 0; k != w.size(); ++k)
    isNumber *= isdigit(w[k]);
    
return isNumber;
}
