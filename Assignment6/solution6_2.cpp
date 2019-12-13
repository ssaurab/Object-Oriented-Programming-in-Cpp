/*
*	CREATED BY S SRINIVAS SAURAB
*	DATE : 21-02-2018 IIT MADRAS
*/
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 5;// an arbitrarily large number

struct Package{
private:
	string name;
	int cost;
	
public:
    long long best;
	int bestIndex;
//the constructor function
	Package(string _name , int _cost){
		name = _name , cost = _cost;
	}
//the auxiliary functions to access the private variables
    string get_name(){
        return name;
    }
    void put_name(string s){
        name = s;
    }
    int get_cost(){
        return cost;
    }
    void put_cost(int cost){
        cost = cost;
    }
};

struct Destination{
private:
	int tourism_quotient;
public:
    vector < Package > packages;
  //auxiliary function to access private variables
    int gettq (){
        return tourism_quotient;
    }
    void puttq(int tq){
        tourism_quotient = tq;
    }
};

int main(){

	int n;
	long long ans = LLONG_MAX;
	string buf;
//The array of the destinations that also holds all the input data
	Destination arr[N];

//The input intake starts here
	cin >> n;
	int temp;
	for(int i = 1 ; i <= n ; i++){
		cin >> temp;
		arr[i].puttq(temp);
	}

	getline(cin , buf);
	for(int i = 1 ; i <= n ; i++){
		string get_name;
		int cost1;
		getline(cin , buf);
		stringstream ss(buf);
		while(ss >> get_name){
			ss >> cost1;
			arr[i].packages.push_back(Package(get_name , cost1));
		}
	}
//The input intake ends here

//Processing the input begins here
	for(int i = 1 ; i <= n ; i++){
//The base subproblem is dealt with seperately
		if(i == 1){
//best denotes the best plausible cost that can come to that package in that destination
			for(int j = 0 ; j < arr[i].packages.size() ; j++){
				arr[i].packages[j].best = arr[i].packages[j].get_cost();
//bess index is the minimal index that can be matched to in the previous destination without violations
				arr[i].packages[j].bestIndex = j;
			}
		}
		else{
//in every new and bigger subproblem we check the incoming tou.quotient with the previous latest tou.quotient
//if the upcoming tourism quotient is lesser than the previous one
			if(arr[i].gettq() < arr[i - 1].gettq()){
				long long curBest = 1e15;
				int ptr = ((int) arr[i - 1].packages.size()) - 1;
				int bestIndex = ptr;
//for all the packages in the current destination,we set the best index of the previous destination
				for(int j = ((int) arr[i].packages.size()) - 1 ; j >= 0 ; j--){
					while(ptr >= 0 and arr[i].packages[j].get_cost() < arr[i - 1].packages[ptr].get_cost()){
						if(arr[i - 1].packages[ptr].best < curBest) bestIndex = ptr;
						curBest = min(curBest , arr[i - 1].packages[ptr].best);
						--ptr;
					}
//also for all the packages we update the best cost to reach there (if plausible)
					arr[i].packages[j].best = curBest + arr[i].packages[j].get_cost();
					arr[i].packages[j].bestIndex = bestIndex;
				}
			}

//if the upcoming tourism quotient is equal to the previous one	
			else if(arr[i].gettq() == arr[i - 1].gettq()){
				long long curBest = 1e15;
				int bestIndex;
				for(int j = 0 ; j < arr[i - 1].packages.size() ; j++){
					if(arr[i - 1].packages[j].best < curBest) bestIndex = j;
					curBest = min(curBest , arr[i - 1].packages[j].best);
				}
				for(int j = 0 ; j < arr[i].packages.size() ; j++){
//here the case is much simpler as the best index is always the least plausible package's index
//also updating the best cost to reach at each respective package
					arr[i].packages[j].best = curBest + arr[i].packages[j].get_cost();
					arr[i].packages[j].bestIndex = bestIndex;
				}
			}
			else{
//if the upcoming tourism quotient is greater than the previous one
				int ptr = 0;
				long long curBest = 1e15;
				int bestIndex = 0;
//for all the packages starting from the bottom we assign the best plausible path from the previous subproblem without violating the rules
				for(int j = 0 ; j < arr[i].packages.size() ; j++){
					while(ptr < arr[i - 1].packages.size() and arr[i].packages[j].get_cost() > arr[i - 1].packages[ptr].get_cost()){
						if(arr[i - 1].packages[ptr].best < curBest) bestIndex = ptr;
						curBest = min(curBest , arr[i - 1].packages[ptr].best);
						++ptr;
					}
//the while loop above gets such indec from previous destination and now we can add the destination's packages to the previous paths					
					arr[i].packages[j].best = curBest + arr[i].packages[j].get_cost();
					arr[i].packages[j].bestIndex = bestIndex;
				}
			}
		}
	}

	int idx = -1;
	for(int j = 0 ; j < arr[n].packages.size() ; j++){
		if(arr[n].packages[j].best < ans) idx = j;
		ans = min(ans , arr[n].packages[j].best);
	}
//in case all the costs shoot up- the case corresponding to non plausible path association between
//i.e we can't find a series of packages that obey the rules of the problem
	if(ans >= 1e15){
		cout << -1 ;
		return 0;
	}
	cout << ans << endl;
	stack < string > stk;
//using auxiliary stack to print out the packages and cost as needed
	for(int i = n ; i >= 1 ; i--){
		stk.push(arr[i].packages[idx].get_name());
		idx = arr[i].packages[idx].bestIndex;
	}

	while(!stk.empty()){
		cout << stk.top() << " ";
		stk.pop();
	}

}
