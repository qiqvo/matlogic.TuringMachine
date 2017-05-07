#pragma once
#include "RuleStateData.h"
#include <map>
#include <fstream>
using namespace std;

using Rules = map<pair<State, char>, Rule>; // state and char -> rule

class Machine {
private:
	static const unsigned int len_of_tape = 100;
	char input[len_of_tape];

	Rules rls;
	State cur_state;
	Data *cur_data;
public:
	Machine() : cur_state(0) {}
	void GetInput(ifstream* fin) {
		unsigned i = 0;
		for (i; i < len_of_tape; ++i) {
			input[i] = static_cast<char>(Symbol::Naught);
		}
		char tmp;
		i = 0;
		while (*fin && i < len_of_tape) {
			*fin >> tmp;
			input[i++] = tmp;
		}
		cur_data = new Data{ _strdup(input) };
	}

	void Add_Rule(const State s, char c, const Rule r) {
		rls.insert({ {s, c}, r });
	}
	char* GO() {
		while (cur_state != -1) {
			cur_state = (*rls.find({ cur_state, *(cur_data->_val) })).second(*cur_data);
		}
		return input;
	}
};

