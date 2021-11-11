#ifndef READ_HEADER
#define READ_HEADER
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<map>
using namespace std;

struct commands
{
	string command;
	int idCapacity;
	double quantity;
};

class Read
{
private:
	//Variables
	string inputFile;
	string outputFile;
	vector<commands> data;
	static Read* instance;
	Read();
public:
	//Functions
	Read* getInstance();
	vector<commands> getData();
	void readFile();
};
#endif
