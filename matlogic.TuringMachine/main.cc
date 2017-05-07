#include <iostream>
#include "Machine.h"
#include <fstream>
#include <string>
#include <vector>
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

template <class Cont>
Cont split(const string& s, const char del) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	Cont elems;

	while (std::getline(ss, item, del)) {
		if(!item.empty())
			elems.push(item);
	}
	return elems;
}

int main() {
	ifstream rules_file("RULES");
	ifstream in_file("Input");
	Machine Turing;
	string tmp;
	const char q = 'q';
	const char terminal = '*';

	int state_beg_num, state_end_num;
	char init_sign, end_sign;
	char direct;
	
	while (getline(rules_file, tmp)) {
		auto tokens = split<queue<string>>(tmp, ' ');

		if (tokens.front()[0] != q)
			continue;
		else
			state_beg_num = stoi(tokens.front().substr(1));
		tokens.pop(); // - q0

		init_sign = tokens.front()[0];
		tokens.pop(); // - |
		tokens.pop(); // - ->

		if (tokens.front()[0] != q)
			continue;
		else if (tokens.front()[1] == terminal)
			state_end_num = -1;
		else
			state_end_num = stoi(tokens.front().substr(1));
		tokens.pop(); // - q1

		end_sign = tokens.front()[0];
		tokens.pop(); // - o

		if (tokens.empty())
			direct = static_cast<char>(Direction::inPlace);
		else {
			direct = tokens.front()[0];
			tokens.pop(); // - R
		}
		
		Turing.Add_Rule(state_beg_num, static_cast<Symbol>(init_sign),
		{ state_end_num, end_sign, direct });
	}

	Turing.GetInput(&in_file);
	cout << Turing.GO() << endl;

	rules_file.close();
	in_file.close();
	cin >> direct;
	return 0;
}