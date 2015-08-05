#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "regex.h"

using namespace std;


int main()
{
	Regex praser;
	string s; string ss;
	cout << "input regex s:";
	while (cin >> s)
	{
		praser.compile(s);
		cout << "input text ss:";
		while (cin >> ss)
		{			
			if (ss == "##") break;
			cout << praser.isMatch(ss) << endl;
			cout << "input text ss:";
		}
		cout << "input regex s:";
		
	}
	system("pause");

	//cout << "Consequence:" << PraseText(Regex, Text) << endl;
	return 0;
}