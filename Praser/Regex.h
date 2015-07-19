

#include <cstdlib>
#include <stack>
#include "node.h"
#include "reader.h"

namespace Regex{
#define ALPHA 	1
#define DIGIT 	3
#define BRACK	4 //[]
#define BRACE	6 //{}
#define PAREN	8 //()
#define OR		10 //|
#define STAR	11 //*
#define DOT		12 //.
#define GREEDY	13 //?
#define BACKLASH 14 //\

class Regex;
};
/*
A Regex praser, supporting tokens include () [] + * . |

*/

class Regex
{
public:
	Regex();	
	Regex(string regex);
	~Regex();

	void compile(string regex);
	bool isMatch(string str);

private:
	int getType(char c);
	void handleAlpha(string str);
	void handleParen(string str);
	void handleBrack(string str);
	void handleBrace(string str);
	void handlePlus(string str);
	void handleStar(string str);
	void handleDot(string str);
	void handleOr(string str);

private:
	stack<Node*> _operator_stack;
};

Regex::Regex(string str){
	compile(str);
}
Regex::Regex(){
	_str.clear();
	_operator_stack.clear();
}


Regex::compile(string str){
	Reader reader(str);
	while(reader.next()){
		switch(getType(reader.read())){
			case ALPHA:
				handleAlpha(reader);
				break;
			case 
		}
	}
}

int getType(char c){
	if(isdigit(c)){
		return DIGIT;
	}
	else if(isalpha(c)){
		return ALPHA;
	}
	else if(c == '('||c == ')'){
		return PAREN;
	}
	else if(c == '['||c == ']'){
		return BRACK;
	}
	else if(c == '{'||c == '}'){
		return BRACE;
	}
	else if(c == '*'){
		return STAR;
	}
	else if(c == '|'){
		return OR;
	}
	else if(c == '+'){
		return PLUS;
	}
	else if(c == '.'){
		return DOT;
	}
}


