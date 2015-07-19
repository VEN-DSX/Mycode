#include <iostream>
#include <vector>
#include <string>

using namesapce std;

vector<vector<char>> InitDFA(string Regex){
	int i=0;
	while(i!=Regex.length()){
		
	}
}

string InputRegex(){
	string s;
	cout<<"Input Regex:";
	cin>>s;
	return s;
}
string InputText(){
	string s;
	cout<<"Input Text:";
	cin>>s;
	return s;
}

int main()
{
	string Regex = InputRegex();
	string Text  = InputText();
	
	InitDFA(Regex);	
	
	cout<<"Consequence:"<<PraseText(Regex,Text)<<endl;
	return 0;
}