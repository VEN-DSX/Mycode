#include <set>
#include<sstream>
using namespace std;
enum NodeType {
	nNORMAL = 0,
	nCAT,
	nOR,
	nREPEAT
};



class greater{
	bool operator()(char a,char b){
		return a > b;
	}
};



class Node{
	public:
		Node();

		~Node();

		void addValue(char c);
		void addLeft(Node*);
		void addRight(Node*);


		void setRange(int, int, bool);
		void setType(NodeType);		
		void setChild(Node*);
		bool isChildNull()		{
			if (_child == nullptr){
				return true;
			}
			else
			{
				return false;
			}
		}
		bool isLeftChildNull()	{
			if (_left_child == nullptr){
				return true;
			}
			else
			{
				return false;
			}
		}
		bool isRightChildNull()	{
			if (_right_child == nullptr){
				return true;
			}
			else
			{
				return false;
			}
		}
		Node* getChild(){ return _child; }
		Node* getLeft(){ return _left_child; }
		Node* getRight(){ return _right_child; }

		void printNode(stringstream &ss_type,stringstream &ss_child){
			ss_type << nodeType(_type) <<"\t";
			if (_left_child != nullptr) ss_child<<"/";
			if (_child != nullptr) ss_child << "|";
			if (_right_child != nullptr)ss_child << "\\";
			ss_child << "\t";
		}
		string nodeType(NodeType type){
			if (type == NodeType::nCAT)		return "nCAT";
			if (type == NodeType::nNORMAL)	return "nCAT";
			if (type == NodeType::nOR)		return "nOR";
			if (type == NodeType::nREPEAT)	return "nREPEAT";
		}
	private:
		Node* _parent;
		Node* _child;
		Node* _left_child;
		Node* _right_child;
		NodeType _type;
		int _min;
		int _max;
		bool _INF;

		set<char> _range;

};



Node::Node(){
	_parent = nullptr;
	_child = nullptr;
	_left_child = nullptr;
	_right_child = nullptr;
	_type = NodeType::nNORMAL;
	_min = 1;
	_max = 1;
	_INF = false;
}

void Node::addValue(char c){
	_range.insert(c);
}

void Node::setRange(int min, int max, bool is_INF){
	_min = min;
	_max = max;
	_INF = is_INF;
}

void Node::setType(NodeType type){
	_type = type;
}

void Node::addLeft(Node *node){
	_left_child = node;
}

void Node::addRight(Node *node){
	_right_child = node;
}

void Node::setChild(Node* node){
	_child = node;
}