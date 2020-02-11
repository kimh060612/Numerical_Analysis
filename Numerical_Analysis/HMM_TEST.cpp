#include "HMM.h"
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

Theta TEST;


int main()
{
	fin.open("input.txt");
	fout.open("output.txt");

	int num_state, Time;
	fin >> num_state >> Time;
	


	fin.close();
	fout.close();
	return 0;
}