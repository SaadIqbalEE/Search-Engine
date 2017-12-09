//indexing documents
//Author:Smart search Engine Group
//Works on Command line argument
//Enter path of maildir folder in command line 
//output: DOCID_.CSV file in .exe folder


//Use dirent.h library and make works by calling it recursivelly
//Data_structure is vector of queue
//Recommended to use in release mode
//Happy coding :)

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<dirent.h>
#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;

class index_dire{
	int sat;
	char* s;
	vector<queue<string>> a;
	ofstream file;
public:

	index_dire(char* s){
		this->s = s;
		file.open("DOCID_.csv");
		check_f_F(s);
		sat = 0;
	}
	int deep(){
		if (!a.empty()){
			while (a[a.size() - 1].empty()){
				a.pop_back();
				if (a.size() == 1 && a[0].size()==1){
					return 0;
				}
				a[a.size() - 1].pop();
			}
			string temp = s;
		/*	temp = temp.substr(0, temp.size());*/
			for (int i = 0; i < a.size(); i++){
				temp += a[i].front()+ "\\";
			}
			if (temp != s)
				check_f_F(&temp[0]);
		}
		else{
			file.close();
			return 0;
		}
		return 0;
	}

	int check_f_F(char* s){
		int j = 1;
		string w(s);
		a.push_back(queue<string>());
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(s)) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				if (j < 3){
					j++;
					continue;
				}
				switch (ent->d_type) {
				case DT_REG:
					file << sat << "," << w + ent->d_name + "\\\\" << endl;
					sat++;
					// Regular file
					break;
				case DT_DIR:
					a[a.size() - 1].push(string(ent->d_name));
					// Directory
					break;
				default:
					// Unhandled by this example
					break;
				}
			}
			deep();
			closedir(dir);
		}
		else {
			/* could not open directory */
			perror("");
			return EXIT_FAILURE;
		}
	}
};

int main(int argc, char** argv){
	index_dire a(argv[1]);
	system("pause");
	return 0;
}