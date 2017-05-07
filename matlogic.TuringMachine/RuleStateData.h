#pragma once
#include <cstdint>
#include <memory>
#include <functional>
using namespace std;

#define FuncStylePoly // Functional style of Polymorthism
                      // otherwise child classes needed and 
                      // Rules would be a map of 
                      // <pair{...} and Pointer to Rule>

struct Data;  // ptr_char, symb under char
class Rule;   
using State = int; // q* == -1


enum class Direction : char {
	Left = 'L', Right = 'R', inPlace = 'P'
};
enum class Symbol : char /*
						 One -- |
						 lambda
						 Naught -- E (nothing)
						 */
{
	One = '1', Lambda = '0', Naught = 'E'
};

struct Data {
	char* _val;    // pointer to currently using char 
	Symbol _symb;

	Data(Symbol s) : _symb(s) {
		*_val = static_cast<char>(_symb);
	}
	Data(char* c) : _val(c) {
		_symb = static_cast<Symbol>(*c);
	}
};

class Rule {
protected:

#ifdef FuncStylePoly
	// moves the pointer
	function<void(Data&)> placer;
	// changes the val inside the pointer 
	function<void(Data&)> changer_prev; 
#else
	virtual void placer(Data& dt) const = 0;
#endif // FuncStylePoly

	void change(Data& dt) const {
		changer_prev(dt);
		placer(dt);
		dt._symb = static_cast<Symbol>(*dt._val);
	}
public:
	const State next;
	const Symbol _change;
	const Direction _to;

	Rule(int st, char s, char to)
		: Rule(static_cast<State>(st), static_cast<Symbol>(s), 
			static_cast<Direction>(to)) {}

	Rule(State st, Symbol s, Direction to)
		: _to(to), _change(s), next(st) 
	{ 
#ifdef FuncStylePoly
		if(_to == Direction::Right)
			placer = [](Data& dt) -> void {
			++dt._val;
		};
		else if (_to == Direction::Left)
			placer = [](Data& dt) -> void {
			--dt._val;
		};
		else // if (_to == Direction::inPlace)
			placer = [](Data& dt) -> void { return;	};

		if (_change == Symbol::Naught)
			changer_prev = [](Data& dt) -> void { return; };
		else 
			changer_prev = [s](Data& dt) -> void { 
				*dt._val = static_cast<char>(s);
			};
#endif
	}

	const State operator()(Data& dt) const {
		change(dt);
		return next;
	}
};

#ifndef FuncStylePoly
class RuleRight : public Rule {
protected:
	void placer(Data& dt) const {
		++dt._val;
	}
public:
	RuleRight(Symbol s, State st)
		: Rule(s, st, Direction::Right) {}
};
class RuleLeft : public Rule {
protected:
	void placer(Data& dt) const {
		--dt._val;
	}
public:
	RuleLeft(Symbol s, State st)
		: Rule(s, st, Direction::Left) {}
};
class RuleInPlace : public Rule {
protected:
	void placer(Data& dt) const {
		return;
	}
public:
	RuleInPlace(Symbol s, State st)
		: Rule(s, st, Direction::inPlace) {}
};
#endif