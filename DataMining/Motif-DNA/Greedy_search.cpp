#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;
string DNA[30]={
"CATGTCTCCAACCACAGTCTTTTGTTTCCTTACAAAAGGCAGATCCAATGTCCTCTTTGTTTAGCACCTGAAACAAAGCACCTGAAAAGCAGGTCCATAATTGGGATTTGGGGCACTGGACCCAGAAACAATACATCAGGGTAGTTCTTTATGGTGGAATTTTGCTAAAAGGTTCTGTTTCATCTTTATATGAGTATGGTAGACTAATTTGTGAGATAATATTTTGGCCGTAAGCACATTTTCTGCAAGTAAATAAGAAATCAGGTATTACACAAGTGAC",

"TTTGAAGCTACTGCTCTGTGTTCTCTTTGCTATCAGTTTTAATAACTGTTTTTAAGACACCATGTTTTGAAAAGAGCTTTGTTTTTCTCAGCTCTTTCTCTCATCTGCTACATTTTGTAAGAAAGCCATAATCTCATGTTTATGATATTAATTATTGTGGATGTTATGTTATGTTATCAATGCTGTACTGAGACAGTACGGGTCAATAAAAGGATTTGAAATATGAGTATTAAACTACAGTAAGCATTTTTAAAAAGTAAAACGTCTCATAAATAGAATC",

"AGTTTTAGAATTAATACATACTCACCTTTGTACTCACTTATTGTTTAGCTGTAGGTACATTTTAAAGAATTAGGCCAAAGCAAACTCTATTTGAAAACACCTATTATTTGGAAAATGAAATTATATACAAATGATAAGATTATTATATTTTAAAGTAACCTCCCTTGCATGTCTCAGCATAAAGTATTTTTTTATGAAAGTAATTGACCTCTCTTCCTCCTCAGAATACTAGATAAGTACCACAGGTTGTGGGGGTGTGTGTGTGTTTAATTAATATGAG",

"AGGAAAGACAGAGCCCTTTAATAGAAGACTCTTCTGCCTTAAATAATAATTTTCTTAAAGCCTTTTATTCCTGCCACTTGAATGAAAGGAAAGAATGCCTTTCTTTCTTATCATCTCCTTGCTTTCCTGGTTCCTCAATTACCAGCTCCCAGCTCCTACTTCTTCTGCCATAGCAGACTATATTGACATGGCTCCATTACCAGCAGACCACTCCCTCCCACAATGCACCACAGTGCTTTCAACCCACTGGATTTCCCACAGGTCAAATTAGAAAGGACTT",

"GGATCAGAGAAGGGCACTTCTCATGGGCCATAATGTGAATTTTGACTAATGGTAAATGAAGGATGAAACTAGTTTGAGAAGAAACATGTCAGACAAGTTTTCCTCAGATGGCAAGCTAATGTTTTTACAGCATTTTTTCCATCATTACAGTTCTCTCATTCCTGTTTTGATACCACCAACTTGACTTATTGCCTGATTCTTGTCCCTGGTTTTGCCTCTTTGTTGCTCTTTTTCACTCTGTCCTCTCAGTCATCAAAGGAGAGGGAAAAGCAGTCTATTT",

"ATTTGAGAGATTTCACCTAGATTATTCAGCAAATGCTTTCATTAGGCTGTATTTGTCAGTCCACTCTCTTATCTTATTTTCCTCAGTGAGCTCCTTGAAGTTCCCTCAGTGAGCTCCTTGAAGGAAACTCCTATTTTTCAACATATGACTGGCTGTAATTTTTCAACATTACAGGCTGGCACTTAGCATATCATCAGTGCTTAATAAATTTTTTTTTTTTGGTCATACAAACTTAATTAATAGGATGTGTAATGTGTCCTGGCCTCTGAAAAAACTGTGT",

"CATCATTGGGCTATTGTCAGCTGGGAGAAGTTGAGAAGTCCTATGGACTCTGAGGCAAAGGCACCTCCCACTTGCTTGGGAATGATGGGTTGGAGGTGGTGAAATTATCAGTGATCAAAGACATGTCTATTGCTTCCCATTTGCCCATCAAAAATAAGCCAAGGCCAGCAAGAATGAAGAGTTGCATGAGTCATCAGACGCTGGTGAAAATGATAGAATTTGAAGCTTCAAAGTAATCCATAAGCTTAATCAACAAAATACTAAATTTTGCTAGTGATAA",

"TGCTAAAATTTAGCTTTTTGCTATTATTATTAAGAAAAATAATAGTATTTTGAAATGAGGCACTTGATTGCACCTAGGTCTTTGTTTTCTTTGTAAGATTGCCTAAAACCTATCTGCTGCCTGTATTTAAAGGAGTAGTTACAACGTCCCTCCAGCCTCTCTGTAGGAGACAGAGACAGGAAATCTGCCCCAGGTCTGTGTGTGGGCTCCACAGACACTGCCAATACAGGAGTGCTGAACTCACAGCTGAGTCACATTGCTGTCCACACTACATAAATTA",

"TTTAAGACTTCAAAGGGAGAATATGATAGTGTAATGAATTTAAAATTCACAATGTACAACTGAAGTGAGAAGAAATGTATTTTAGTTTACTTCTCCATAGTGGAATTCAATTTAACTTTAAAGTTTCCATTTTCAACGACAGAGGTAAACTCAGCCTTGTCACTCTCAAGGTAACTGTGTCATTGCAGTTTCAAGGTTAGTCTCTTGGAGTAAATATTCAGTCAAATTAAAGATTTAAGCTCAGTAAGTTGGAGCTCAAATTCAATACATGAGCTGCAAT",

"CCACTCTCAAGGATTCTCGTCTTCTCTTTCCCCTCAGGATATATCTGTGTACAGGGGTTCGTCTGGCTGTGCCCCAGATGCTTGTGTCCTTGCTGCAGCTGAAGGTTTTACAGCTGGTAACTTGTAGCCTGTTGTCTAAATGTGATAAAGGCCCACTATGGCCACCCCCATTCAGCCCCTTCTGGCTCAAATGAAGCTTGGAGACTCAACCTCACATTGATCTTTTCGGCTTCCCACCCTAGAGCCTGGGCTATAGGTCACCATGCTCCAAGGTGAGATG",

"GCCCCTGTCATGCCTATTGCTGGACCTATTGGAAAGCTCAGTGTGCTTCCGCCATGTTCAGGCTGTGGGCACTGTGTCCAGCCTTCTCTCTACTTAACCTTCCATTTCTACTCAGTTTGGCAAGGAGCACGCTGTCGGGTGATTTCCTCCCAGGGTTCCAGAGAAGAGAGTCAAATGTTCCCCCTGCTCTAGGCTTTCCAAGTTCATCTAGGGGTATCTATCTCCTACAGCGAGGCTGCGGAAAGGTTGTAACTACTTCAAATACAGACAGCAGATAGGT",

"TTTAGTGCAATCTTACACAGAAAGCAAAGATCTAGGTGCAATCAAGTCTTTTATTTTAAAATACTACTCTTTTTCTTAATAACAGCAAAAAATCTAAATTTTGGCATTATTCCTGGCAAAATTTAGTATTTTCTTGATTGAGATTATAGATTACTTTGGAGCTTCAAATTCTGTCATTTTCATCAGCATCTGATGACTCATGCAATGCTTCGCTCTTACTGGCCTCAGCTTATTTTCAATGAACAAAAAGGCAGCAATAGAATCTCTTTGATCACTGATA",

"ATTTTATCACCTCTAAGCCATCATTCCCAAGCAAGTGGGAGGTGCTCCTGAAAGAAAGTTGTGACTGGGAACTAGGCCAGGACGCTTTGGAAATGGGGTGGTTGTAGGGGGATGGTAGGGCACATTGAGGCCAGAAAGATACTTTTTCCTCAACAGTGAATGAATTGGCTACATTGTCTGGAAGACCCTCAAGTGTCACCAGGAGCTGTGTTTCTTGAGAGCAGTGTCCTGAGGCAGCCAGCCTGAGTCAACTTGAAATTCTATGGAGACCTGGAAGTAT",

"CTTTGGTTTCCATGGCCAGAGGCACAGAACACCTGGAGCTTCCCCCTTCTCCACTTCCTGCCTCCTAATCCCCACCCCCTGTGCTGACAGTCTGCTTTACACTGGTTCACTACCACTGTCATGTTTGTAGTGTTCGGCATCATGAGACATGCCTGAAAGAGATTATTATGGCAAAGATAAGGACAGGCAGCAGACTACTACATGTGTAGTTCCAAAGTGAAATCATCAACCTCCATCTGACTGACCAAGTTCGTTACATACAAGGAGAACTAGAGTGGTT",

"GCCTACCTCTAACCAGACACAGAAGACTTTGGTCTGCAGATGGCAACAGAGTCCACACCAGAATCCAACTTCCACCCAAAGCCTGGGCAACATCTAGTGATGCTGCTGCTGCTCTCCTGGTTTTAGCAGGAGGATTTTCTTTGTTGTCCCCAGTCCCATGACACAGCTCCCCTGTGTCTTGGAGCAGGGGTCTCCTGCAGTGTGTACCCCACAATGGGGCTTGGAGCTTAAAAAGTCCCCATCTCCAGGCAGATTGACTTCAGATGAGAATGAGAAGGAA",

"GCCTAAACATTTCAGGCATGAGATGCTGTGCCAATTATCAATTTATTACCTGTCCATTCTGAACTCACCCTTCACTGCCTGCTCTGCAATAATGGAGTTAGACTCAGTATTTCTCTTCTGCTAGTTAGCATGATGTTCGTCGGTAGAGGGTGCTAGAAGGTCACTGGAGGAAGAAGGGATTTCTTGTCCTTTTCTGGTGTGCACCTCTCAGCAAGCTCCTACAGTACCCACTGGCTTACACAGCATCAGCTCCTCCAGTGCACAGGGGATAGCAGTGTCC",

"AGCAGCCAGCAGTAAGTGCTACCTCCCCAGGGGCATCGTTCCCTATCACCTTCTCAGGCTGCTTTGCAATGGAGTACCCTAAGCTCAGCACTTCCCCAGAAATGTCTCCCCAAAAATCCTCTCACAGAGCTTTGCAATGAGATCCAAGGCATGGCACCTCCCCATGGGGAGCTTCCCCTGGTAATCTAGAGGGTGGATTCCCAGGTAGTCCCACCAGCAGAGGACCTCAGCAAACCTCTTCTCCATCCAGTGAGCCATGGTTGCACCCTCTACCAATGAG",

"GTCTGGATCTGGATCTCAGCCCAGGATGGAGGAGTCTCTTCCTTGGATGCTCTAGCTCAGCCCTGAGTTGTAGCTGCTCTCCATTAGGTTGCTTTCGGCCTTAAAGTTATTTTTACCTTTGACTAGCTAATCTCCTCTTACTCTAATCTTTTGTTAAAGTTAATAGTTCTCTATTTCAATTTCTGATGTTCAAATTACTATGTGGTGTCTGTCTTCTGATTGAACTCCGAACTAACACCAATGCCAAAATGCAAACATACACAGCTACACCTGCTCCTAA",

"GCCCCCTGAAGATAAACACACACACACACACACACTTTGAAATAGGGCAGAAGAGACTTAGGAGACTCATGTGAGCTCAGCTTTACTAACAAAAGATATTTTCCAAAAGGAAGTGAAAAGCACCTAAGAAGGCAGAGTGAAACTTAGACCACACACACACACACACACACACACAAAAAAAAAAAGAAACTGCCCAGCCCTCTTCAGGAACATAGAGATAGGCACTAAGTTGCCATCCATGGAGACATAAATGAAGAGCTACTCACTCACTGCTTTGCAC",

"TTTATAAGGATGTTGGAAGGTCTTCAAGTCAGAGGGCAGAAATAAAGCCCAGGACTCACCAGTGAGCCCTCAAAATATGAGTTCTATTCTACTGATGGGGAATATTGGTTAGCCCCTTAATCCTGAATCCAGTTCTGCCTCATTAGACAAGGAGGAAACCCCGGGTCCCTGGTGTCTAGGACCCCAGACTACCATCACCCTGCTGCCAATAGTGCTTCACCCAACTCCCACTGCCCACTCTCTTGACCCACAAGGCATACCTGGGAGTTGACCCAACCCT",

"TTTATCAATCCGGCCTTCCCATTTTTCTTTGGCACCATCCCTGTGCTTTGGGTTTTAGGGGTTTTAGTGCCTTCCTTTCCTCTTTTCTCTTATCTCATCCTCCTTGATGGGGGGACTGGAAGAGGCACAATACAATTTCTAAATATATTTGTTTTAAAAAAACACTATAAATAATTATGAGGTAGAAATCATAAAAGCATGGGTTCAAAATGAATAAAAATGCCAACTCCCATAATGTTATGTAAATAGGTACTTGTAGCTTATGATAAAATTGCTGAAG",

"ACAGCTTCTTGCTGGGATTCAAAAAGTGCTGTATTTCAAATAACAGATCGAATGAAACAAAGCTGATGTGCTTGGAAAAAACCGGGGTAAGATGACACCAGCGTGGTTCTAGTGTTGGCAAAGATTATAATGCTGAAGATACATGCAAGGAACTTAAGTAAAACTAGGTCATAATATGTGAGACAGAAAAACTCTAGAACATTCTTAAATGCACATGTCATTTTATATGATATGGGATTTTAATAAATAATAGTTAATTATAACAAAGTTTTTAGAAACA",

"GACATTTGACTGTTTTGACTATATCCTTAGAAGTGTGTATTGTTTCCAAGTTGGCCTATCATTTTTTAGTCGCTTTTTTGGAAAAAAAAAAAAAAGGAAGGTCTCCTCATATTCAGGATTGCCTAGTGTTCAGGCACATGAGGACTACCATGAGCCTGGTAGCTAGTAGTCAGACAATAACCTGTCTCTTTCAGTTCAAGGTAAAGCAAGCCTATGCTTGAGCCTCCCTCAAAGCTTCCTGCTTTAGGAATTTACTCATCTCTCAGAACTGGTGAGAACA",

"GTGTCTGGCTCTCTGAGATACTAGCTTTCCTCCCTAGAAAAGTAGTTGGTAGCCCCTAGCATTGAAGTCTCTTTTAAAAATTCGAACACAACCCATATACATACATACGGTTAATTGGCTTTCAACAAAGGTGCAAAATCAACTCAATGGAGAAAGAAGATTCTTAAATGATAATCACAAATGATTATGGAACAATTGGACATCTATATACTAAAAAAGAGAGAACCTTAGCCCTTATCTTGTACCACACACAAAAATTAAGGTAAAAATAGATCATTAA",

"CCTAAATGTACAACATGTAACATGTCTAGAAAAAGTCACAGGAGAAAAATTTTGTGACCTTGGGTTAGGCAAAGATTCATTAGATACAACACCTATAACATGATCCACAAAAGAAATAAAAGCTGATAACCTGGACTTCATTAAAACTTAAAACTTCTACTCTTGAAAAGACACTGTTAAAAATATAAGCTACAGACTGTGAGAAAATATTTATAAAATACATATTCATTAAAAGACATATTTCCAAAATACATAAAGAGCTCTCTCAACTCAGTAGGTT",

"TTTAAAATCCCATTTAGAAATAGGCAAAAATTTGAACAGACACTTCAACAAATTAAATACATAGATGGCAAATAAGTACATGAAAAGATGCTCATCATTTAAGATATGTGATTGGCAGTTTCTTATAAAGTTAAATATACACTTACCGTATGACCCAAAAATCCCATTCCAAGGTATTTACTCAAGAGAAATGAAGACATATACCCACTCAAAAAACTGTACACAAATATTTATAATGGATTTATTAATAATCACCCCAAACTGAAAACACCCAAATATT",

"TTTCAACCAGTGAATGGGTAACAAACAATCGTACATCCGTATAATGCAGTAAATAGACAGGAAATACTAAACATGCAACAACACGGGGGAATCTCCAATACATTATGCTAAGTGAAAGAAGCTGGACTCATAAGGTATAGGACAGTCTGCAAAAAAACAAAATAAGAGGGATAGAGAAGTAATCAGTGGTTGCCAGCAGCTGGAAATGGGGAGGGGTTGACCACGAATAGGCTCAAGTGAACATTTGGGTATGACAAAAAAGTTCTATATCTTGATTGTG",

"GTGGTGGTTACATGACTGTCTGCATTTGTCAAAGCTTATTAAACTATACTTTTAAATGGTGAATTTTGCTGTGTATAAATTACAGCTCAATTTAAAAAAACAAAAACAAAAACAAAAAACTCTGACCCAGATCACTGTGGTCATTGTTGGTGGAGACTGCTGGCCTCTTAGCTCTCTTATGAGTGGGGTTACCAGCTAATCCCTGACATATTTGTGGTTCCAGGACTCCTAAAGGGTTGTGCAATGGTTTGTCTCCTTTCTCAAAGACAGCTGCTGGCTG",

"ATGGTAAAAGATAAAGAGAAAGAAAGATGTACACAGGCAAGTCAGGGAGAAATTTATCTTTCTTTTCCTTCCTGTCTTTCTTTTATATTCTTCCTCCCTCTTCTATTTCCTGCAGCCCTTATTTTTCTTTCACTTACTTTTCCTATTTATTCATCAGCTGAAACCTTGCTGAAAGGGATTAGCTGGGGGCTAAGTCGAGTAGGGCAAAAGGAAGCATTTGCTTCTAATCAGTAGTACACTGGTAAATGATTAGTAACCAGCTCTCTGAAACACCCACACA",

"CACACACAAACACACACACACACAAACACACACACACACAAACTAAAGTTTCTTTTAAATTTTACTGATATGAAGAGTATATAGCACAGGCTGGGTGCAGTGGCTCACGCCTATAATTCCCAGCAATTTGAGAGGCTGAGGCAGGTAGATCACTTGAAGTCAGGAGTTCAAGACCAGCCAAGGCAACATGGCAAAACCCCATCTCTAATAAAAAAAAAAAAATACAAAAATTAACTGGGCATGGTGGCACACGCCTGTAATCCCAGCTACTCAGGAGGCT",

};
map<char,vector<int>> create_profile(vector<int> start,int len){
	map<char,vector<int>> map;
	std::vector<int> a(30,0);
	map['A']=a;
	map['T']=a;
	map['G']=a;
	map['C']=a;
	for(int i=0;i<len;i++){
		for (int j = 0; j < 30; ++j)
		{
			map[DNA[j][i+start[j]]][i]++;
		}	
	}	
	return map;
}

int Score(vector<int> start,int len,string &s){
	s.clear();
	map<char,vector<int>> map;
	std::vector<int> a(30,0);
	map['A']=a;
	map['T']=a;
	map['G']=a;
	map['C']=a;
	int score=0;
	for(int i=0;i<len;i++){
		for (int j = 0; j < 30; ++j)
		{
			map[DNA[j][i+start[j]]][i]++;
		}
		int max = 0;
		char max_char;
		for (auto k = map.begin(); k != map.end(); ++k)
		{
			if(k->second[i] > max){
				max = k->second[i];
				max_char = k->first;
				
			}			
		}
		s.push_back(max_char);
		score += max;
	}
	return score;

}


int main()
{
	default_random_engine random_engine(time(NULL));
	clock_t t;
	

	//---------------------Greedy search 计算consensus------------------START
	//获得随机的30个起始点
	vector<int> start_position(30);
	for(int i=0;i<30;i++){
		start_position[i] =  random_engine()%250;	
	}
	int best_score = 0;
	int round=1;
	t = clock();
	string motif;
	while(Score(start_position,30,motif) > best_score){
		//生成profile矩阵
		map<char,vector<int>> profile = create_profile(start_position,30);
		best_score = Score(start_position,30,motif);

		string P_most_w_mer[30];
		vector<int> P_most_w_mer_start_pos(30,0);//每条序列中最贴近与profile的起始点
		vector<int> P_most_w_mer_score(30,0);//每条序列自己的得分

		// for i <- 1 to 30 Find a P-most probable w-mer a from the ith sequence
		for(int i=0;i<30;i++){			
			for (int j = 0; j < 251; ++j)
			{
				int tmp_score = 0;
				for(int k=0;k<30;k++){
					tmp_score += profile[DNA[i][j+k]][k];
				}
				if(tmp_score > P_most_w_mer_score[i]){
					P_most_w_mer[i] = DNA[i].substr(j,30);
					P_most_w_mer_start_pos[i] = j;
					P_most_w_mer_score[i] = tmp_score;
				}				
			}			
		}
		start_position = P_most_w_mer_start_pos;

		//打印每轮的结果
		cout<<"Round "<<round++<<endl;
		for(int i=0;i<30;i++){
			cout<<"start pos:"<<P_most_w_mer_start_pos[i]<<"\tP_most_w_mer:"<<P_most_w_mer[i]<<"\tit's score:"<<P_most_w_mer_score[i]<<endl;
		}
		cout<<"------------"<<endl;
		cout<<"best_score:"<<best_score<<" motif:"<<motif<<endl;
		

	}


	t = clock() - t;
	printf ("totally %f seconds.\n",((float)t)/CLOCKS_PER_SEC);
	//---------------------Greedy search 计算consensus------------------END



	return 0;
}	