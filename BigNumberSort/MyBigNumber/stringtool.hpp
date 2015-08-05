#ifndef _STRINGTOOL_
#define _STRINGTOOL_ 

#include <string>
#include <vector>

using namespace std;

class BigNumber{
public:
    static string add(string a,string b);
    static string sub(string a,string b);
    static string mul(string a,string b);
    static string div(string a,string b);

private:
	string number;
};

#endif