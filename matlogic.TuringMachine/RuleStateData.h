#pragma once
#include <cstdint>
#include <memory>
#include <functional>
using namespace std;

#define FuncStylePoly

struct Data;  // ptr_char, symb under char
class Rule;  // { func: direction, next_state, cur_state, change_of_ }
using State = int; // q* == -1


enum class Direction : char16_t {
	Left, Right, inPlace
};
enum class Symbol : char /*
						 One -- |
						 Naught -- lambda
						 Null -- E (nothing)
						 */
{
	One = '1', Naught = '|', Null = 0
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
	const Direction _to;
	const Symbol _change;
	const State next;

#ifdef FuncStylePoly
	function<void(Data&)> placer;
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
	Rule(Symbol s, State st, Direction to)
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

		if (_change == Symbol::Null)
			changer_prev = [](Data& dt) -> void { return;	};
		else 
			changer_prev = [&](Data& dt) -> void { 
				*dt._val = static_cast<char>(_change);
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