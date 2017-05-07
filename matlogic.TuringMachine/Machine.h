#pragma once
#include "RuleStateData.h"
#include <map>
#include <fstream>
using namespace std;

using Rules = map<pair<State, Symbol>, Rule>;

class Machine {
private:
	static const unsigned int len_of_tape = 100;
	char input[len_of_tape];

	Rules rls;
	State cur_state;
	Data *cur_data;
public:
	Machine() : cur_state(0) {
		unsigned i = 0;
		for (i; i < len_of_tape - 1; ++i) {
			input[i] = static_cast<char>(Symbol::Lambda);
		}
		input[len_of_tape - 1] = '\0';
	}
	void GetInput(ifstream* fin) {
		unsigned i = 0;
		char tmp;
		while (*fin >> tmp && i < len_of_tape -1 ) {
			input[i++] = tmp;
		}
		cur_data = new Data(input);
	}

	void Add_Rule(const State st, const Symbol s, const Rule r) {
		rls.insert({ {st, s}, r });
	}
	char* GO() {
		while (cur_state != -1) {
			cur_state = 
				(*rls.find({ cur_state, cur_data->_symb }))
				.second(*cur_data);
		}
		input[len_of_tape - 1] = '\0';
		return input;
	}
};

