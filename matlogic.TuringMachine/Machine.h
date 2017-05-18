#pragma once
#include "RuleStateData.h"
#include <map>
#include <fstream>

using namespace std;

using Rules = map<pair<State, Symbol>, Rule>;

class Machine {
public:
	static const unsigned int len_of_tape = 100;
private:
	char input[len_of_tape];

	unsigned int num_of_steps;
	Rules rls;
	State cur_state;
	Data *cur_data;

	void Add_Rule(const State st, const Symbol s, const Rule r) {
		rls.insert({ { st, s }, r });
	}
public:
	Machine() : cur_state(0), num_of_steps(0){
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
	void SetRules(const char* f_name = "RULES");
	char* GO(ofstream* out);
	unsigned int NumberOfSteps() {
		return num_of_steps;
	}
};

