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
	ofstream out_file("Output");
	
	Machine Test;
	Test.SetRules("RULES");
	Test.GetInput(&in_file);

	Test.GO(&out_file);

	in_file.close();
	out_file.close();
	
	int tmp;
	cin >> tmp;
	return 0;
}