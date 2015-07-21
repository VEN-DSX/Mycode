class error
{
public:
	error();
	~error();

	public:
		static void msg(string str){
			cerr<<"error at:"<<_line<<":"<<_offset<<" message:"<<str<<endl;
		}
		static void NewLine(){
			_line++;
		}
	private:
		static int _line;
		static int _offset;
};