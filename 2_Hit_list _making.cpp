//create hit list 
//Author:Smart search Engine Group
//Works on Command line argument
//user must give path to DOCID.csv and path of directory where to store hitlist in command line
//output: .csv files in given folder containing hitlist of files


//Use map library
//Data_structure is vector
//Recommended to use in release mode
//Happy coding :)

#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include<stdio.h>
#include<unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

class hitlist{
	string D_index_file,H_path,DOC_ID,O_path;
	ifstream index,pather;
	ofstream Hit;
	unordered_map<string, unsigned short> rude;
public:
	hitlist(string file,string path){
		D_index_file = file;
		H_path = path;
		index.open(file);
		O_path = "begin";
		hit_list();
	}
	~hitlist(){}

void DocID_func(){
	string temp_;
	if (getline(index, temp_)){
		stringstream c_temp(temp_);
		string next;
		vector<string> line;
		while (getline(c_temp, next, ',')){
			line.push_back(next);
		}
		DOC_ID = H_path+ line[0]+".csv";
		O_path = line[1];
	}
	else{
		index.close();
		O_path.clear();
		DOC_ID.clear();
	}
}

void hit_list(){
	while (!O_path.empty()){
		DocID_func();
		if (!O_path.empty() && !DOC_ID.empty()){
			pather.open(O_path);
			Hit.open(DOC_ID);
			string z;
			while (getline(pather, z)){
				stringstream lmnop(z);
				string BigO;
				while (getline(lmnop, BigO, ' ')){
					vector<string> pure;
					int fir=0, len=0;
					for (int i = 0; i < BigO.size(); i++){
						if (isdigit(BigO[i]) || isalpha(BigO[i])){
							len++;
						}
						else{
							if (len != 0)
							pure.push_back(BigO.substr(fir, len));
							fir = i + 1;
							len = 0;
						}
					}
					if (len != 0)
						pure.push_back(BigO.substr(fir, len));
					for (int i = 0; i < pure.size();i++){
						if (rude[pure[i]] == 0){
							rude[pure[i]] = 1;
						}
						else{
							rude[pure[i]]++;
						}
					}
				}
			}
			unordered_map<string, unsigned short>::iterator it_map=rude.begin();
			while (it_map != rude.end()){
				Hit << it_map->first << "," << it_map->second<<endl;
				it_map++;
			}
			rude.clear();
			pather.close();
			Hit.close();
		}
	}
}
};


int main(int argc,char** argv){
	hitlist(string(argv[1]), string(argv[2]));
	system("pause");
	return 0;
}
