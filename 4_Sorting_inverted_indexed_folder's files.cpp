//sorting inverted indexed files
//Author:Smart search Engine Group
//Works on Command line argument
//Enter:  path of inverted index file and path of created sorted index file 
//output: .csv files in given folder by name of wordID contain DOCIDs pointing to it sorted by frequency of occuring in respective DOCID

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
#include<map>
#include<dirent.h>
#include<algorithm>

using namespace std;

class node{
public:
	string ID;
	int fre;
	node(string a, int b) :ID(a), fre(b){}
	~node(){}
	bool operator <(node a){ return this->fre > a.fre; }
};

class sorter{
	ifstream inputing;
	ofstream outputing;
	string old, neew, name;
	map<string, vector<node>> sorting;
public:
	sorter(string a, string b) :old(a), neew(b){
		mover();
	}
	~sorter(){}

	void sortia(){
		map<string, vector<node>>::iterator it = sorting.begin();
		while (it != sorting.end()){
			sort(it->second.begin(), it->second.end());
			it++;
		}
	}
	void writer(){
		sortia();
		map<string, vector<node>>::iterator m_it = sorting.begin();
		while (m_it != sorting.end()){
			outputing.open(neew+m_it->first);
			vector<node>::iterator n_it = m_it->second.begin();
			while (n_it != m_it->second.end()){
				outputing << n_it->ID<<","<<n_it->fre<<endl;
				n_it++;
			}
			outputing.close();
			m_it++;
		}
		sorting.clear();
	}


	void reader(){
		string temp;
		string s;
		vector<string> y;
		while (getline(inputing, temp)){
			stringstream hello(temp);
			while (getline(hello, s, ',')){
				y.push_back(s);
			}
			sorting[name].push_back(node(y[0],stoi(y[1])));
			y.clear();
		}
		inputing.close();
	}


	int mover(){
		int x = 0;
		int number = 0;
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(&old[0])) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				if (x <= 1){
					x++;
					continue;
				}
				switch (ent->d_type) {
				case DT_REG:
					cout << number << endl;
					inputing.open(old+ent->d_name);
					name = ent->d_name;
					number++;		
					reader();
					if (number % 500000 == 0)
						writer();
					// Regular file
					break;
				case DT_DIR:
					cout << "containing folder ???";
					// Directory
					break;
				default:
					// Unhandled by this example
					break;
				}
			}
			closedir(dir);
			writer();
		}
		else {
			/* could not open directory */
			perror("");
			return EXIT_FAILURE;
		}
	}
};


using namespace std;

int main(int argc,char** argv){
	sorter(argv[1],argv[2]);
	system("pause");
	return 0;
}