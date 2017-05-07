#include <iostream>
#include "Machine.h"
#include <fstream>

int main() {
	ifstream rules_file("RULES");
	ifstream in_file("Input");
	Machine Turing;
	char tmp;
	while (rules_file) {
		rules_file >> tmp;
		Turing.Add_Rule()
	}
	rules_file.close();
	in_file.close();
	return 0;
}