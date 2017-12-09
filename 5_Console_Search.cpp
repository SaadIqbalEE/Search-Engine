//Searching files
//Author:Smart search Engine Group
//Works on Command line argument
//Enter:  path of sorting folder and path of DOCID_.csv
//output: Console output contain path of file close to Query

//Use map library
//Data_structure is vector,string,map
//function of algorithm are intensively used
//Recommended to use in release mode
//Happy coding :)

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<map>
#include<algorithm>
#include<conio.h>
using namespace std;

class node{
public:
	string Idd;
	int Fac;
	node(string a, int b) :Idd(a), Fac(b){}
	~node(){}
	bool operator <(node a){ return this->Fac>a.Fac; }
};

class searchi{
	ifstream incoming;
	map<string, int> out;
	vector<string> words;
	FILE *next;
	long size;
	string a,b;
	vector<node> table;
public:
	vector<string>info;
	searchi(string s,string c):a(s),b(c){
		working();
	}
	~searchi(){}
	void working(){
		int fir = 0, len = 0;
		for (int i = 0; i < a.size(); i++){
			if (isdigit(a[i]) || isalpha(a[i])){
				len++;
			}
			else{
				if (len != 0)
					words.push_back(a.substr(fir, len));
				fir = i + 1;
				len = 0;
			}
		}
		if (len != 0)
			words.push_back(a.substr(fir, len));
		looper();
	}

	int size_checker(string s){
		next = fopen(&s[0], "rb");
		if (next == NULL){ return 0; }
		else
		{
			fseek(next, 0, SEEK_END);   // non-portable
			size = ftell(next);
			fclose(next);
			return size;
		}
	}

	int hash_valu(string s){
		return (((int)s[0] + (int)s[s.size() - 1]) % 20) + 1;
	}

	int damping_factor(long sizze){
		if (sizze < 124){return 10;}
		else{
			if (sizze<250){return 8;}
			else{
				if (sizze<500){ return 6; }
				else{
					if (sizze<1000){ return 4; }
					else{
						if (sizze<10000){ return 3; }
						else{
							if (sizze<100000){ return 2; }
							else{
								return 1;
							}
						}
					}
				}
			}
		}
	}


	void result(){
		map<string, int> ::iterator ioi = out.begin();
		while (ioi != out.end()){
			table.push_back(node(ioi->first,ioi->second));
			ioi++;
		}
		sort(table.begin(),table.end());
		if (!table.empty()){
			for (int i = 0; i < 50 && i < table.size() - 1; i++){
				info.push_back(table[i].Idd);
			}
		}
	}


	void looper(){
		vector<string>::iterator yal=words.begin();
		while (yal != words.end()){
			string t_path = b + *yal + "_" + to_string(hash_valu(*yal)) + ".csv";
			int g=damping_factor(size_checker(t_path));
			int num = 0;
			incoming.open(t_path);
			string data;
			while (getline(incoming, data) && num<5000){
				string main_c;
				stringstream tempp(data);
				vector<string>datas;
				while (getline(tempp, main_c, ',')){
					datas.push_back(main_c);
				}
				out[datas[0]] *= 100;
				out[datas[0]] += (stoi(datas[1])*g);
				num++;
			}
			incoming.close();
			yal++;
		}
		result();
	}
};

class alu{
	ifstream opene;
	string z;
public:
	alu(){}
	vector<string> iiso;
	alu(string s) :z(s){
		get_info();
	}
	void get_info(){
		opene.open(z);
		string a;
		while (getline(opene, a)){
			string temp;
			stringstream temp_all(a);
			vector<string> d;
			while (getline(temp_all, temp, ',')){
				d.push_back(temp);
			}
			iiso.push_back(d[1]);
		}
		opene.close();
	}
};

int main(int argc, char** argv){
	string inputt;
	cout << "Wait a moment" << endl;
	alu nasi(argv[2]);
	int y = 1;
	while (y)
	{
		cout << "Enter the String" << endl;
		cin >> inputt;
		searchi Oas(inputt, argv[1]);
		if (!Oas.info.empty()){
			for (int i = 0; i < 50 && i < Oas.info.size() - 1; i++){
				cout << nasi.iiso[stoi(Oas.info[i])] << endl;
			}
		}
		else
			cout << "No word in your quries matches in data set" << endl;
			_getch();
		system("CLS");
	}
	system("pause");
	return 0;
}