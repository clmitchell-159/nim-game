// unbeatableNim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<string>
#include<ios>

using namespace std;

int main()
{
	string dummy;
	fstream fs;
	fs.open("rules.txt", ios::in);
	if (fs.is_open()) {
		string line;
		while(getline(fs, line)) {
			cout << line << endl;
		}
		fs.close();
	}
	getline(cin, dummy);
	return 0;
}

