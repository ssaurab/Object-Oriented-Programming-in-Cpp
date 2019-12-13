/*
* CREATED BY S Srinivas Saurab CS16B039
*  IIT MADRAS 12-01-2018
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//few data types that are often used in the code
typedef pair <string, float> datapacket;
typedef pair <string, bool> boolpair;

//functor class
class sorter {    
    public:    
    bool operator ()(const pair<string, float>& p1, const pair<string, float>& p2)
    {   
    	//first sorting based on marks if possible
        if(p1.second > p2.second) return true;
        else if (p1.second < p2.second) return false;
        else //if the marks are levelled we check ascii sum of roll number
        {
        	string s1 = p1.first, s2 = p2.first;
        	int ascii_sum1 = 0, ascii_sum2 = 0;
        	for(int i = 0; i < s1.length(); i++)
        	{
        		ascii_sum1 += s1[i];
        	}
        	for(int i = 0; i < s2.length(); i++)
        	{
        		ascii_sum2 += s2[i];
        	}

        	if(ascii_sum1 < ascii_sum2) return true;
        	else if(ascii_sum2 < ascii_sum1) return false;
        	else //if even ascii sum could not help in a successful sorting we go by lexicological order of roll number
        	{
        		if(s1 <= s2) return true;
        		else return false;
        	}
        }
    }
};

//the major class that stores the data and processes the commands later
//has methods to insert into the list, make admissions and also show the list
class e_litmus{

	private:
		map <string, bool> m;
    //map has keys of all students who are currently in the list (as true) as well as admitted with bool value false
		vector <datapacket> list;
    //the main list that has the examination marks data

	public:
    //useful for the initial data storage as we do not intend to sort them
          void newInsert(string roll, float x)
		{
			datapacket temporary;

			temporary.first = roll;
			temporary.second = x;
			list.push_back(temporary);

			boolpair mapentry;
            if(m.find(roll) == m.end())
            {   
			 mapentry.first = roll;
			 mapentry.second = true;
			 m.insert(mapentry);
            }
		} 
//useful to insert data later 
		void INSERT(string roll, float x)
		{
			//checks if already present
			//inserts new datapacket if not present 
			//else update the marks according to the paradigm

			datapacket temporary;

			if(m.find(roll) == m.end())
			{
             //if entry is not already present   
				temporary.first = roll;
				temporary.second = x;
				list.push_back(temporary);

				sorter s;
				sort(list.begin(), list.end(), s);

				boolpair mapentry;
				mapentry.first = roll;
				mapentry.second = true;
				m.insert(mapentry);
			} 		
			else 
			{	
                if(!m[roll])
                {
                //if present and admitted
                cout << "ALREADY ADMITTED"<<endl;
                return;
                }
                //if the entry exists in the list already
				int position;
				for(int i = 0; i < list.size(); i++)
				{
					if(list[i].first == roll) 
					{
						position = i;
						break;
					}
				}
				list[position].second = (list[position].second + x) /2;
                sorter s;
				sort(list.begin(), list.end(), s);
			}
		}
    
//checks if there are perc_student percentage of people who obtained at least perc_marks percentage of the maximum marks
//if the conditions are satisfied it prints out the top 10% from the list and deletes their entries
		void IS_ADMIT(int perc_student, int perc_marks)
		{
			float max_marks = list[0].second;
			float treshold = max_marks * perc_marks / 100.0000;
			int total = 0;
			int passed = 0;
			for(int i = 0; i  < list.size(); i++)
			{
				if(list[i].second >= treshold) passed++;
				total++;
			}            
			if(passed >= (perc_student*total)/100 && total >= 10)
			{    
                cout << "YES" << endl;
                int k = floor(0.10 * list.size());
				PRINT(0, k-1);
                for(int i = 0; i < k-1; i++)
                {
                    m[list[i].first] = false;
                }
				list.erase(list.begin(), list.begin()+k);
			}            
            else cout << "NO" <<endl;
		}
    
//prints all the entries between indices x and y 
		void PRINT(int x, int y)
		{
			for(int i = x; i <= y; i++)
			{
				cout << setiosflags(ios::fixed) ;
				cout<< list[i].first<<" "<<setprecision(3)<<list[i].second<<endl;
			}
		}

//overwritten function that has no parameters that prints the whole list
		void PRINT()
		{
			for(int i = 0; i < list.size(); i++)
			{
				cout << setiosflags(ios::fixed) ;
				cout<< list[i].first<<" "<<setprecision(3)<<list[i].second<<endl;
			}
		}
};

int main(){

	e_litmus Mu_Sigma_Squared;
    //an object of class e_litmus in whose scope we wish to perform further operations

	int entries;
	string ROLLNUMBER;
	float marks;
	scanf("%d\n", &entries);


//taking in the initial list
	for(int i = 0; i < entries; i++)
	{
		cin >> ROLLNUMBER;
		cin >> marks;
		Mu_Sigma_Squared.newInsert(ROLLNUMBER, marks);
	}
    
	int no_of_queries;
	string query;
	int x, y;
	float z; //just a few temporary variables used in function calls
	string roll;
	scanf("%d\n", &no_of_queries);

//taking the next commands one by one and decoding them and calling respective functions
	for(int i = 0; i < no_of_queries; i++)
	{
		cin >> query;

		if(query == "INSERT")
		{	
			cin >> roll;
			cin >> z;
			Mu_Sigma_Squared.INSERT(roll,z);
		}
		else if(query == "IS_ADMIT") 
		{
			cin >> x>> y;
			Mu_Sigma_Squared.IS_ADMIT(x,y);
		}
		else if(query == "PRINT")
		{
		    string s;
            int x[2];

            getline(cin,s);
            istringstream iss(s);                     
     //dividing the line to see if the users intention is to print the whole list or only a part of it            
            int j=0;
            while(iss >> x[j])
            {
                j++; 
            }
            if(j==0){ 
                //if indices are not specified
                Mu_Sigma_Squared.PRINT();
            }else{ 
                //if indices are specified
                Mu_Sigma_Squared.PRINT(x[0]-1,x[1]-1);
            }	
	    }
    }
	return 0;
}
