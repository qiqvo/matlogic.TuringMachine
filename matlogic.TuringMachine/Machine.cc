#include <sstream>
#include <fstream>
#include "Machine.h"
#include <queue>

// #define Debug
#ifdef Debug
#include <iostream>
#endif // Debug

using namespace std;

const char* _comment = "//";

template <class Cont>
Cont split(const string& s, const char del, const char* _comment) {
	std::stringstream ss;
	ss.str(s.substr(0, s.find_first_of(_comment)));
	std::string item;
	Cont elems;
	while (std::getline(ss, item, del)) {
		if (!item.empty())
			elems.push(item);
	}
	return elems;
}

void Machine::SetRules(const char* f_name) {
	ifstream rules_file(f_name);
	string tmp;
	static const char q = 'q';
	static const char terminal = '*';

	int state_beg_num, state_end_num;
	char init_sign, end_sign;
	char direct;

	while (getline(rules_file, tmp)) {
		if (tmp.empty())
			continue;
		auto tokens = split<queue<string>>(tmp, ' ', _comment);

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

		Add_Rule(
			state_beg_num,
			static_cast<Symbol>(init_sign),
			{ state_end_num, end_sign, direct }
		);
	}

	rules_file.close();
}

char* Machine::GO(ofstream* out) {
	while (cur_state != -1) {
		++num_of_steps;
#ifdef Debug
		std::cout << "Step: " << num_of_steps << "'" << input << "'" << std::endl;
		std::cout << "from state " << cur_state << ' ';
#else
		*out << num_of_steps << "\t'" << input << "'" << std::endl;
#endif // Debug	
		cur_state =
			(*rls.find({ cur_state, cur_data->_symb }))
			.second(*cur_data);
		input[len_of_tape - 1] = '\0';
	}
	return input;
}