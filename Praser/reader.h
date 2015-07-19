class reader
{
public:
	reader(string str){
		_str = str;
		_index = 0;
	}
	~reader();
	void init(string str){
		_str = str;
		_index = 0;
	}

	char read(){
		return _str[_index++];
	}
	int next(){
		if(_index+1 = _str.length()){
			return 0;
		}
		return _str[_index+1];
	}

private:
	string _str;
	int _index;

};