#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
#include <map>
#include <string>

using namespace std;

typedef pair <string,int> freq;
typedef pair <string,vector <int> > leaderlist;

//the functor class
class sorter {
    
    public:
    
    bool operator ()(const pair<string, int>& p1, const pair<string, int>& p2){
        
        return p1.second < p2.second;
    }
};

int main(){

	int no_of_sentences, top_words;

	scanf("%d %d\n", &no_of_sentences, &top_words);

    //we create two maps both with a word as the key and having it's frequency and speaker wise frequency vector respectively
	map <string,int> map_freq;
	map <string, vector <int> > map_leaders;

	vector <int> zerov(10000);

    //we take in every input and process it till we store it into the maps before the next input line is scanned
	for(int i = 0 ; i < no_of_sentences; i++)
	{
		int speak_no;
		string sentence_spoken;

		scanf("%d", &speak_no);

		getline(cin, sentence_spoken);

  // the below loop removes punctuation marks, if any. We use cctype header and ispunct function for this purpose
		for (int j = 0, len = sentence_spoken.size(); j< len; j++)
    	{

        	if (ispunct(sentence_spoken[j]))
        	{
           		 sentence_spoken.erase(j--, 1);
            	 len = sentence_spoken.size();
        	}
    	}
//the below instruction converts all capital letters to lowercase letters with a functor using tolower
    	transform(sentence_spoken.begin(), sentence_spoken.end(), sentence_spoken.begin(), ::tolower);
//now we consider word by word using stringstream and insert corresponding attributes into the map
		istringstream iss(sentence_spoken);
  	    string word;

  	    freq wordnfreq;
  	    leaderlist wordnleaders;

        while(iss >> word) {
//inserting into the frequency map if the key doesn't already exist. If it exists we just increment the frequency.
        	if(map_freq.find(word) == map_freq.end())
       		{	
       			wordnfreq.first = word;
       			wordnfreq.second = 1;

        		map_freq.insert(wordnfreq);
        	}
        	else map_freq[word]++;
//inserting into the leader wise frequency map if the key doesn't already exist. If it exists we just increment the frequency under that leader
        	if(map_leaders.find(word) == map_leaders.end()) 
        	{
        		wordnleaders.first = word;
        		wordnleaders.second = zerov;
        		map_leaders.insert(wordnleaders);         		 
    	   }
    	    map_leaders[word][speak_no]++;
	}
}

	for(int d = 0; d < top_words; d++){
    
        sorter s;
		string x;
//using the functor to find the maximum frequency among the keys in the frequency map
		auto a = max_element(map_freq.begin(), map_freq.end(),s);

		x = a->first; //that key that occurs most often in this case
        vector<int>::iterator leadersfreq;
//find the leader of that most frequent word        
	    leadersfreq = max_element(map_leaders[x].begin(), map_leaders[x].end());

        int b = *leadersfreq;
		int size = map_leaders[x].size();
		cout << x;
//in case multiple leaders exist we print them in descending order
		for(int i = size; i >= 1; i--)
		{
			if(map_leaders[x][i] == b) cout <<" "<< i;
		}
       cout<<endl;
		map_freq[x] = 0; //reset the frequency as we don't use that keyword again in next iterations
	}
	return 0;
}

