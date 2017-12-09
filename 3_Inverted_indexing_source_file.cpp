//inverted indexer
//Author:Smart search Engine Group
//Works on Command line argument
//Enter hit_list path + directory to store inverted index files+ starting DOCID file number + final COCID file number 
//output: .csv files in given folder by name of wordID contain DOCIDs pointing to it


//Use map library
//Data_structure is vector
//Recommended to use in release mode
//Happy coding :)



#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<dirent.h>
#include<direct.h>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<map>
using namespace std;

class node{
public:
	string DID;
	string freq;
	node(string a, string b) :DID(a), freq(b){}
	~node(){}
};


class I_index{
	map<string, vector<node>> mappy;
	int it_counter;
	ifstream HIT;
	ofstream I_map;
	string hit_path, index_path;
public:
	I_index(string s,string m,string a,string b):hit_path(s),index_path(m){
		take_a_file(stoi(a), stoi(b));
	}
	~I_index(){}
	int hash_valu(string s){
		return (((int)s[0] + (int)s[s.size() - 1]) % 20) + 1;
	}
	void func_O(){
		string temp, s;
		while (getline(HIT, temp)){
			vector<string> y;
			stringstream hello(temp);
			while (getline(hello, s, ',')){
				y.push_back(s);
			}
			mappy[y[0]];
			mappy[y[0]].push_back(node(to_string(it_counter), (y[1])));
		}
		HIT.close();
	}
	void take_a_file(int first, int last){
		for (it_counter = first; it_counter <= last; it_counter++){
			cout << it_counter << endl;
			HIT.open(hit_path + to_string(it_counter) + ".csv");
			func_O();
		}
		map<string, vector<node>> ::iterator it_mapy = mappy.begin();
		while (it_mapy != mappy.end()){
			I_map.open(index_path + it_mapy->first + "_" + to_string(hash_valu(it_mapy->first))+".csv", ios::app);
			vector<node>::iterator itv = it_mapy->second.begin();
			while (itv != it_mapy->second.end()){
				I_map << itv->DID << "," << itv->freq<<endl;
				itv++;
			}
			I_map.close();
			it_mapy++;
		}
		mappy.clear();
	}
};

int main(int argc,char** argv){
	I_index(argv[1], argv[2],argv[3],argv[4]);
	system("pause");
	return 0;
}