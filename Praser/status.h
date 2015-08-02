#include<set>
#include"node.h"
#include<map>
using namespace std;

class Status
{
public:
	Status();
	~Status();

	
	void pushNode(Node* node){
		_nodes.insert(node);
		return;
	}
	void pushSet(set<Node*> node_set){
		_nodes.clear();
		_nodes = node_set;
		return;
	}
	bool empty(){
		return _nodes.empty();
	}
	bool same(Status* B){
		set<Node*>::iterator a = _nodes.begin(), b = B->_nodes.begin();
		while (*a == *b && (a != _nodes.end() && b != B->_nodes.end())){
			a++; b++;
		}
		return (a == _nodes.end() && b == B->_nodes.end());
	}


	bool operator==(Status);

	set<Node*> _nodes;

	map<char, Status*> _next_status;
	map<char, Status*> _last_status;

};

Status::Status()
{
}

Status::~Status()
{
}

bool operator==(Status A,Status B){
	set<Node*>::iterator a=A._nodes.begin(), b=B._nodes.begin();
	while (*a == *b && (a!=A._nodes.end() && b!= B._nodes.end())){
		a++; b++;
	}
	return (a == A._nodes.end() && b == B._nodes.end());
}