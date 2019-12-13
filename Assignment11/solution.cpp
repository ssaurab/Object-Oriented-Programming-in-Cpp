/*
* CREATED BY S SRINIVAS SAURAB
* IIT MADRAS CS16B039 3RD APRIL 2018
*/
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Tree{

   public:
        bool isEnd;
        Tree *children[27];				
        int frequency;                                       
  

  Tree * setNode()
    {
       Tree *node = new Tree;
       node->frequency = 0;
       for(int i=0;i<26;i++)
         {
             node->children[i]=NULL;
         }
        return node;
     }
     void TrieInsert(Tree *head,string input)
     {
         Tree *node = head;
         for(int i = 0; i<input.length(); i++)			                                         
            {
                  if(!node->children[input[i]-'a'])
                  {
                      node->children[input[i]-'a'] = setNode();
                  }

                 node = node->children[input[i]-'a'];
            }
          node->isEnd = true;
     }
      void PrintProgeny(Tree *root,string l)			
      {
        Tree *temp = root;
        if(temp->isEnd)
        {
            cout << l << " ";
            //return;
        }  

        for(int i=0; i<26; i++)
          {
            if(temp->children[i] != NULL)
               {
                  string s = l + (char)(i + 'a');
                  PrintProgeny(temp->children[i],s);
               }
          } 
        return;
     }
     void TrieSearch(Tree *root,string s)                 
     {
        Tree *node = root;
        for(int i=0; i<s.length(); i++)			
          {
             int character = s[i]-'a';
             node = node->children[character];
          }
         if(node -> isEnd)				
          {
              cout << s <<" " << ++(node->frequency);
              return;
          }
        cout << s << " ";
        PrintProgeny(node,s);
  }
};


int main()
{
   int n,m;
   cin >> n;
   cin >> m;
   
   Tree T;
   Tree *root = T.setNode();

   string s;
   for(int i = 0; i < n; i++)
   {
        cin >> s;
        T.TrieInsert(root,s);
   }
   for(int j = 0; j < m; j++)
   {
       cin >> s;
       T.TrieSearch(root,s);
       cout << endl;
   }
    
   return 0;
}                
                


