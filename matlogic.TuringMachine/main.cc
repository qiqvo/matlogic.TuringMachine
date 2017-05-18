#include "Machine.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

/*
Rule is read in such an order:
q0 1 -> q1 0 R
stands for:
q0 -- init state
1  -- sign 
-> 
q1 -- end state
0  -- change sign
R  -- move head in Right Direction
*/

int main() {
	// std::ios::sync_with_stdio(false);
	ifstream in_file("Input");
	ofstream out_file1("Output.MacOld");
	ofstream out_file2("Output.MacNew");

	Machine Test_old, Test_new;
	Test_old.SetRules("RULES.standartMult");
	Test_new.SetRules("RULES.NewMult");

	Test_old.GetInput(&in_file);
	in_file.clear();
	in_file.seekg(0, in_file.beg);
	Test_new.GetInput(&in_file);

	Test_old.GO(&out_file1);
	Test_new.GO(&out_file2);

	in_file.close();
	out_file1.close();
	out_file2.close();
	
	int tmp;
	cin >> tmp;
	return 0;
}