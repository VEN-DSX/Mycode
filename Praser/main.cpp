#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "regex.h"

using namespace std;


int main()
{
	Regex praser;
	string s;
	while (cin >> s)
	{
		praser.compile(s);
		praser.print();
	}
	system("pause");

	//cout << "Consequence:" << PraseText(Regex, Text) << endl;
	return 0;
}