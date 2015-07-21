#include <string>
using namespace std;
class Reader
{
public:
	Reader(){};
	Reader(string str){
		_str = str;
		_index = 0;
	}
	~Reader(){};
	void init(string str){
		_str = str;
		_index = 0;
	}

	char read(){
		return _str[_index++];
	}
	char current(){
		return _str[_index];
	}
	char next(){
		return _str[_index + 1];
	}
	string substr(){
		return _str.substr(_index);
	}
	bool isend(){
		if (_index + 1 == _str.length()){
			return 1;
		}
		return 0;
	}

private:
	string _str;
	int _index;

};