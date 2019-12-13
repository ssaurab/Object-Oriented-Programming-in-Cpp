/*
*  created by S Srinivas Saurab 06-02-2018
*  IIT Madras CS16B039 
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main(){

	int old,newi;

	scanf("%d %d\n", &old, &newi);

	string s;
	vector <string> v;

	int oldi = old;
    
//first we scan in the old lines
	for(int i = 0; i < old; i++)
	{
		getline(cin,s);
		v.push_back(s);
	}
	
	int inputs = 0;

//the iterations to take and insert the new lines come inside this loop
	while(newi-inputs)
	{
		getline(cin,s);
		int flag = 0;
//similar to insertion sort we run the old list until we reach a string which comes later in the lexicological ordering
		for(int i = 0; i < oldi + inputs; i++)
		{
			if(s < v[i]) 
            {
                v.insert(v.begin()+i, s);
                flag = 1; 
//if we meet a string that comes after the string under consideration in lexicological order we note it in a flag and we insert it
                break;
            }		
		}
//if all the strings already present occur early to the string under consideration in lexicological order we insert it in the end        
		if(flag == 0)v.push_back(s);

		for(int j = 0; j < oldi+inputs+1; j++)
		{
			cout << v[j] <<endl ;
		}
		inputs++;
	}
 return 0;
}


