

#include <cstdlib>
#include <queue>
#include <stack>
#include "node.h"
#include "reader.h"
#include <cassert>
// #include "error.h"


#define ALPHA 	1
#define DIGIT 	3
#define LBRACK	4 //[]
#define RBRACK	5 //[]
#define LBRACE	6 //{}
#define RBRACE	7 //{}
#define LPAREN	8 //()
#define RPAREN	9 //()
#define OR		10 //|
#define STAR	11 //*
#define DOT		12 //.
#define GREEDY	13 //?
#define BACKLASH 14 
#define PLUS	15

using namespace std;

/*
A Regex praser, supporting tokens include () [] + * | and 0-9 a-z A-Z
*/

class Regex
{
public:
	Regex(){};
	Regex(string regex);
	~Regex();

	void compile(string regex);
	bool isMatch(string str);
	void print();
private:
	int getType(char c);
	Node* constructTree	(Reader &reader);
	Node* handleParen(char c, Reader&);
	Node* handleChar	(char c, Reader&, stack<Node*>&);	
	Node* handleBrack	(char c, Reader&, stack<Node*>&);
	Node* handleBrace	(char c, Reader&, stack<Node*>&);
	Node* handleRepeat	(char c, Reader&, stack<Node*>&);
	Node* handleDot		(char c, Reader&, stack<Node*>&);
	Node* handleOr		(char c, Reader&, stack<Node*>&);

private:
	stack<char> _operator_stack;
	Node* _root;
};

Regex::Regex(string str){
	_root = nullptr;	
	compile(str);
}
Regex::~Regex(){
}


//not finished
void Regex::print(){
	queue<Node*> queue;
	queue.push(_root);
	stringstream ss_type;
	stringstream ss_child;
	
	while (!queue.empty()){
		int n = queue.size();
		for (int i = 0; i < n; i++){
			Node *node = queue.front();
			queue.pop();

			node->printNode(ss_type,ss_child); 
			
			if (!node->isLeftChildNull())
				queue.push(node->getLeft());
			if (!node->isChildNull())
				queue.push(node->getChild());
			if (!node->isRightChildNull())
				queue.push(node->getRight());
		}
		cout << ss_type.str() << endl;
		cout << ss_child.str() << endl;
		ss_type.str("");
		ss_child.str("");
		cout << endl;
	}
	
}

void Regex::compile(string str){
	Reader reader;
	reader.init(str + "\0");
	_root = constructTree(reader);
}
Node* Regex::constructTree(Reader &reader){
	stack<Node*> _node_stack;
	while (reader.current() != '\0'){
		
		char tmp_char = reader.read();
		Node *tmp_node;
		
		switch (getType(tmp_char)){
			case ALPHA:case DIGIT:
				tmp_node = handleChar(tmp_char, reader, _node_stack);
				break;
			case LPAREN:
				_operator_stack.push('(');
				tmp_node = constructTree(reader);
				_node_stack.push(tmp_node);
				break;
			case RPAREN:
				if (_operator_stack.top() != '(')
					cout << "illegal operator:" << _operator_stack.top() << " expect ')'" << endl;
				assert(_operator_stack.top() == '(');
				_operator_stack.pop();
				tmp_node = _node_stack.top(); _node_stack.pop();
				return tmp_node;
				break;
			case LBRACK:
				tmp_node = handleBrack(tmp_char, reader, _node_stack);
			case LBRACE:// not supported
				tmp_node = handleBrace(tmp_char, reader, _node_stack);
				break;
			case STAR:case PLUS:
				tmp_node = handleRepeat(tmp_char, reader, _node_stack);
				break;
			case OR:
				tmp_node = handleOr(tmp_char, reader, _node_stack);
				break;
			case BACKLASH:
				tmp_node = handleChar(reader.read(), reader, _node_stack);
				break;
			case DOT://not supported
				tmp_node = handleDot(reader.read(), reader, _node_stack);
				break;
			default:
				cout << "illegal char" << endl;// error::msg("illegal char");
				return nullptr;
		}
		if (_node_stack.size() == 2){
			_node_stack.pop();

			Node *node = new Node;
			node->setType(NodeType::nCAT);
			
			node->addLeft(_node_stack.top()); _node_stack.pop(); 
			node->addRight(tmp_node);
			_node_stack.push(node);
		}

	}
	Node *node = _node_stack.top(); _node_stack.pop();
	return node;

}

int Regex::getType(char c){
	if (isalpha(c)){
		return ALPHA;
	}
	else if (isdigit(c)){
		return DIGIT;
	}
	else{
		switch (c){
		case '(':
			return LPAREN;
			break;
		case ')':
			return RPAREN;
			break;
		case '[':
			return LBRACK;
			break;
		case ']':
			return RBRACK;
			break;
		case '{':
			return LBRACE;
			break;
		case '}':
			return RBRACE;
			break;
		case '*':
			return STAR;
			break;
		case '|':
			return OR;
			break;
		case '.':
			return DOT;
			break;
		case '+':
			return PLUS;
			break;
		default:
			return -1;
		}
	}

}


Node* Regex::handleChar(char c, Reader &reader, stack<Node*>& _node_stack){
	Node *node = new Node;
	node->addValue(c);	


	
	if (reader.current() == '+'){
		reader.read();
		Node *tmp_node = new Node;
		tmp_node->setType(NodeType::nREPEAT);
		tmp_node->setRange(1, -1, true);
		tmp_node->setChild(node);
		_node_stack.push(tmp_node);
		return tmp_node;
	}
	else if (reader.current() == '*'){
		reader.read();
		Node *tmp_node = new Node;
		tmp_node->setType(NodeType::nREPEAT);
		tmp_node->setRange(0, -1, true);
		tmp_node->setChild(node); 
		_node_stack.push(tmp_node);
		return tmp_node;
	}
	else{
		_node_stack.push(node);
		return node;
	}



	
}

// not used
Node* Regex::handleParen(char c, Reader &reader){
	stack<Node*> _node_stack;
	while (reader.current() != ')'){
		char tmp_char = reader.read();
		Node *tmp_node;

		switch (getType(tmp_char)){
		case ALPHA:case DIGIT:
			tmp_node = handleChar(tmp_char, reader, _node_stack);
			break;
		case LPAREN:
			tmp_node = handleParen(tmp_char, reader);
			break;
		case LBRACK:
			tmp_node = handleBrack(tmp_char, reader, _node_stack);
		case LBRACE:// not supported
			tmp_node = handleBrace(tmp_char, reader, _node_stack);
			break;
		case STAR:case PLUS:
			tmp_node = handleRepeat(tmp_char, reader, _node_stack);
			break;
		case OR:
			tmp_node = handleOr(tmp_char, reader, _node_stack);
			break;
		case BACKLASH:
			tmp_node = handleChar(reader.read(), reader, _node_stack);
		case DOT://not supported
			tmp_node = handleDot(reader.read(), reader, _node_stack);
		default:
			cout << "illegal char" << endl;// error::msg("illegal char");
			return nullptr;
		}
		if (_node_stack.size() == 2){
			_node_stack.pop();

			Node *node = new Node;
			node->setType(NodeType::nCAT);

			node->addLeft(_node_stack.top()); _node_stack.pop();
			node->addRight(tmp_node);
			_node_stack.push(node);
		}
	}
	reader.read();
	Node *node = _node_stack.top(); _node_stack.pop();
	return node;

}

Node* Regex::handleBrack(char c, Reader &reader, stack<Node*>& _node_stack){ return nullptr; }

Node* Regex::handleBrace(char c, Reader &reader, stack<Node*>& _node_stack){ return nullptr; }

Node* Regex::handleRepeat(char c, Reader &reader, stack<Node*>& _node_stack){
	Node *node = new Node;
	node->setType(NodeType::nREPEAT);
	if (c == '+')
		node->setRange(1, -1, true);
	else if (c == '*')
		node->setRange(0, -1, true);
	else {
		cout << "error:ilegal char in handleRepeat"<<endl;
	}
	node->setChild(_node_stack.top()); _node_stack.pop();
	_node_stack.push(node);
	return node;
}

Node* Regex::handleDot(char c, Reader &reader, stack<Node*>& _node_stack){ return nullptr; }

Node* Regex::handleOr(char c, Reader &reader, stack<Node*>& _node_stack){
	Node* right_node = constructTree(reader);
	Node* left_node = _node_stack.top();
	_node_stack.pop();
	Node* node = new Node;
	node->setType(NodeType::nOR);
	node->addLeft(left_node);
	node->addRight(right_node);
	_node_stack.push(node);
	return node;
}

