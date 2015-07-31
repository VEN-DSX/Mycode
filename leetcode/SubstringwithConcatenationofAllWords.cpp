/*
 *misunderstood at first,I build a Trie tree for 'words' then search form s.begin to s.end
 *and once we get a 'true' then 'push_back' its index to 'res'
 *that's apprently not a solution for this question considered 'hard' 
 *the code is used for memorying, hehe.
 */


#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef struct Node{
	bool end;
	Node* next[26];
	Node(){
		end = false;
		for (int i = 0; i<26; i++){
			next[i] = nullptr;
		}
	}
}Node;
vector<int> findSubstring(string s, vector<string>& words) {
	vector<int> res;
	map<string, bool> check;
	if (words.size() < 1) return res;
	if (words[0].length() > s.length()) return res;

	int words_len = words[0].length();
	Node* root = new Node;

	for (int i = 0; i<words.size(); i++){
		Node *p = root;
		for (int j = 0; j<words_len; j++){
			if (p->next[words[i][j] - 'a'] != nullptr){
				p = p->next[words[i][j] - 'a'];
			}
			else{
				p->next[words[i][j] - 'a'] = new Node;
				p = p->next[words[i][j] - 'a'];
			}
		}
		p->end = true;
	}


	for (int i = 0; i<s.length() - words_len + 1; i++){
		Node *p = root;
		for (int j = 0; j<words_len; j++){
			if (p->next[s[i + j] - 'a'] == nullptr){
				break;
			}
			else{
				p = p->next[s[i + j] - 'a'];
				if (p->end == true){
					if (check[s.substr(i, words_len)] == false){
						res.push_back(i);
						check[s.substr(i, words_len)] = true;
					}
				}
			}
		}
	}

	return res;
}

int main(){
	vector<string> a;
	a.push_back("foo");
	a.push_back("bar");
	findSubstring("barfoothefoobarman", a);


}