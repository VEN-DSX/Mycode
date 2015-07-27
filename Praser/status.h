#include<set>
#include"node.h"
using namespace std;

class Status
{
public:
	Status();
	~Status();

	bool operator==(Status);

	set<Node*> _nodes;
};

Status::Status()
{
}

Status::~Status()
{
}

bool operator==(Status A,Status B){
	set<Node*>::iterator a=A._nodes.begin(), b=B._nodes.begin();
	while (*a == *b){
		a++; b++;
	}
	return (a == A._nodes.end() && b == B._nodes.end());
}