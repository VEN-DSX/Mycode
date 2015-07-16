#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <random>
#include <ctime>

#define _DSX_ 1



#ifdef _DSX_
#include <mingw.thread.h>
#else
#include <thread>
#endif

using namespace std;


class Movie{
public:
	Movie(){};
	Movie(int MovieID,string Title,vector<string> Genres){
		id = MovieID;
		title = Title;
		generes = Genres;
	};
	void setValue(int MovieID,string Title,vector<string> Genres){
		id = MovieID;
		title = Title;
		generes = Genres;
	};
	void addUser(int user_id,int score){
		users[user_id] = score;
	}

	void dump(){
		cout<<id<<" "<<title<<" ";
		for(int i=0;i<generes.size();i++){
			cout<<generes[i]<<" ";
		}
		cout<<endl;
	}


	int id;
	string title;
	vector<string> generes;
	map<int,int> users;
};



class User{
public:
	User(){};
	User(int id,int Gender,int Age,string Occupation,string Zipcode){
		this->id	= id;
		this->gender	= Gender;
		this->age	= Age;
		this->occupation	= Occupation;
		this->zipcode	= Zipcode;
	}
	void setValue(int id,int Gender,int Age,string Occupation,string Zipcode){
		this->id	= id;
		this->gender	= Gender;
		this->age	= Age;
		this->occupation	= Occupation;
		this->zipcode	= Zipcode;
	}
	void addMovie(int MovieID,int score){
		movies[MovieID] = score;
	}
	float getAvgSocre(){
		int sum = 0;
		for(auto i = movies.begin();i!=movies.end();i++){
			sum+=i->second;
		}
		return (float)sum/(float)movies.size();
	}
	void dump(){
		cout<<id<<" "<<gender<<" "<<age<<" "<<occupation<<" "<<zipcode<<endl;
		
		for(auto i=movies.begin();i!=movies.end();i++){
			cout<<"\t"<<i->first<<":"<<i->second<<endl;
		}
	}

	int id;
	int gender;
	int age;
	string occupation;
	string zipcode;
	map<int,int> movies;
};


vector<User> users(6041);
unordered_map<int,Movie> umap_movies;




void readuser(){
	fstream file;
	file.open("users.dat");
	string line;
	int line_count=0;
	while(file>>line){
		int tail=0;
		int head=0;
		int i=0;

		int id;
		int gender;
		int age;
		string occupation;
		string zipcode;

		while(tail<line.length()){
			string temp;
			if(tail+1==line.length()){
				temp = line.substr(head,tail-head+1);
				i++;
				zipcode = temp;
			}
			if(line[tail]==':'&&line[tail+1]==':'){
				temp = line.substr(head,tail-head);
				tail+=2;
				head = tail;
				i++;
				if(i==1){
				id = atoi(temp.c_str());
				}
				else if(i==2){
					gender = temp[0]=='M'?0:1;
				}
				else if(i==3){
					age = atoi(temp.c_str());
				}
				else if(i==4){
					occupation = temp;
				}
			}
			tail++;

		}
		
		users[id].setValue(id,gender,age,occupation,zipcode);
		line_count++;
	}
	cout<<"finished user"<<endl;
	return;
}

void readmovie(){

}

void readusermovie(){
	fstream file;
	file.open("ratings.dat",ios::in);
	string line;
	int line_count=0;
	while(file>>line){
		int head=0;
		int tail=0;
		int i=0;

		int user_id;
		int movie_id;
		int rate;
		int timestamp;


		string temp;
		while(tail!=line.length()){
			string temp;
			if(tail+1==line.length()){
				temp = line.substr(head,tail-head+1);
				i++;
				timestamp = atoi(temp.c_str());
			}
			if(line[tail]==':'&&line[tail+1]==':'){
				temp = line.substr(head,tail-head);
				tail+=2;
				head = tail;
				i++;
				if(i==1){
					user_id = atoi(temp.c_str());
				}
				else if(i==2){
					movie_id = atoi(temp.c_str());
				}
				else if(i==3){
					rate = atoi(temp.c_str());
				}
				
			}
			tail++;
		}
		// cout<<user_id<<" "<<movie_id<<" "<<rate<<endl;
		users[user_id].addMovie(movie_id,rate);
		umap_movies[movie_id].addUser(user_id,rate);
		line_count++;
		// if(line_count==900000)
		// 	break;
	}
	cout<<"finished user_movie"<<endl;
	return ;
}

//计算用户i,j之间的D值
float getD(int i,int j){
	int var=0;
	int count=0;
	auto m=users[i].movies.begin();
	auto n=users[j].movies.begin();
	while(m!=users[i].movies.end() && n!=users[j].movies.end()){

		if(m->first == n->first){
			var += (m->second - n->second)*(m->second - n->second);
			count+=1;
			m++;n++;

		}
		else if(m->first > n->first){
			n++;
		}
		else if(m->first < n->first){
			m++;
		}
	}
	float k = (float)count/(float)(users[i].movies.size() + users[j].movies.size() - count);
	if(count == 0) return -1.0;
	return (float)var/(float)count/k + 1.0/k;
}
float getAvgSocre(vector<int> exp_scores, int rate = 10){
	//排序取中间的80%作为统计
	sort(exp_scores.begin(),exp_scores.end());
	int erase_num = exp_scores.size()/rate;
	return accumulate(exp_scores.begin()+erase_num,exp_scores.end()-erase_num,0.0)/(exp_scores.size()-erase_num*2);
}





fstream roc_file;
default_random_engine random_engine(time(NULL));
void job(string filename,vector<User> vec_users,unordered_map<int,Movie> u_movies,float k){
	cout<<filename<<"\tk="<<k<<endl;	
	fstream file;
	file.open(filename,ios::out);
	file<<filename<<"\tk="<<k<<endl;

	float sum=0.0;//为求平均数而设
	int count=0;
	// float k = 15.0;//k为阀值

	float FPR=0.0;
	float SENSITIVITY=0.0;
	for(int jj=1;jj<101;jj++){	
		int i=random_engine()%6040+1;//取个随机用户
		// int i=1;//取个随机用户
		file<<"--------------------------------------"<<endl;	
		file<<"User "<<i<<endl;
		//第一步：找到与用户i相似的用户，并将所代表user_id的j放入数组user_similar中
		vector<int> user_similar;
		for(int j=1;j<6041;j++){
			if(j==i) continue;
			int var=0;
			int count=0;
			auto m=vec_users[i].movies.begin();
			auto n=vec_users[j].movies.begin();
			while(m!=vec_users[i].movies.end() && n!=vec_users[j].movies.end()){

				if(m->first == n->first){
					var += (m->second - n->second)*(m->second - n->second);
					count+=1;
					m++;n++;

				}
				else if(m->first > n->first){
					n++;
				}
				else if(m->first < n->first){
					m++;
				}
			}
			float kk = (float)count/(float)(vec_users[i].movies.size() + vec_users[j].movies.size() - count);
			float f ;
			if(count == 0) f = -1.0;
			f = (float)var/(float)count/kk + 1.0/kk;
			
			// float f = getD(i,j);
			//若f小于k则
			if(f!=-1.0 && f < k)
			{
				user_similar.push_back(j);//放入数组
			}
			
		}
		//如果不幸没找到相似的用户，则输出no similar users
		if(user_similar.size()==0){
			file<<"User "<<i<<":No similar users."<<endl;
			continue;
		}
		file<<user_similar.size()<<" similar users."<<endl;

		//根据他评过分的电影,从相似的用户里计算预测评分
		vector<int> true_scores;
		vector<int> exp_scores;
		for(auto movie = vec_users[i].movies.begin();movie != vec_users[i].movies.end();movie++){

			// file<<"movie "<<movie->first;
			//统计相似用户给这个电影的平均分
			vector<int> tmp_exp_scores;			
			for (std::vector<int>::iterator u = user_similar.begin(); u != user_similar.end(); ++u)
			{
				Movie mov = u_movies[movie->first];
				if(mov.users.find(*u)!=mov.users.end()){
					tmp_exp_scores.push_back(u_movies[movie->first].users[*u]);					
				}				
			}
			
			//排序取中间的80%作为统计			
			float exp_avg_score = getAvgSocre(tmp_exp_scores,10);
			// file<<"\ttrue tmp_exp_scores:"<<movie->second<<" exp_score:"<<exp_avg_score<<endl;
			if(!tmp_exp_scores.empty()){
				true_scores.push_back(movie->second);
				exp_scores.push_back(exp_avg_score);
			} 
			
		}
		//输出
		float exp_avg_score = accumulate(exp_scores.begin(),exp_scores.end(),0.0)/(float)exp_scores.size();
		float true_avg_score = vec_users[i].getAvgSocre();
		int TP=0;
		int FP=0;
		int TN=0;
		int FN=0;	
		for(int ii=0;ii<exp_scores.size();ii++){
			//预测喜欢 实际喜欢
			if(exp_scores[ii] > exp_avg_score && true_scores[ii] > true_avg_score){
				TP++;
			}
			//预测喜欢 实际不喜欢
			if(exp_scores[ii] > exp_avg_score && true_scores[ii] < true_avg_score){
				FP++;
			}
			//预测不喜欢 实际喜欢
			if(exp_scores[ii] < exp_avg_score && true_scores[ii] > true_avg_score){
				FN++;
			}
			//预测不喜欢 实际不喜欢
			if(exp_scores[ii] < exp_avg_score && true_scores[ii] < true_avg_score){
				TN++;
			}
		}
		float tmp_FPR = (float)FP/(float)(FP+TN);
		float tmp_SENSITIVITY = (float)TP/(float)(TP + FN);
		FPR += tmp_FPR;
		SENSITIVITY += tmp_SENSITIVITY;
		file<<"exp_avg_score:"<<exp_avg_score<<"\ttrue_avg_score"<<true_avg_score<<endl;
		file<<"TP:"<<TP<<"\tFN:"<<FN<<endl;
		file<<"FP:"<<FP<<"\tTN:"<<TN<<endl;
		file<<"SEN:"<<tmp_SENSITIVITY<<"\tFPR:"<<tmp_FPR<<endl;

		cout<<filename<<" round:"<<jj<<"\tuser:"<<i<<endl;


		
	}
	file<<"--------------end--------------"<<endl;
	file<<"SEN:"<<SENSITIVITY<<"\tFPR:"<<FPR<<endl;
	roc_file<<filename<<"\tk="<<k<<"\tSEN:"<<SENSITIVITY/100.0<<"\tFPR:"<<FPR/100.0<<endl;
	// for(int i=1;i<150;i++){
	// 	for(int j=i+1;j<users.size();j++){
	// 		float f = getD(i,j);
	// 		//若小于k则输出到一个文件中
	// 		if(f!=-1.0 && f<20.0)
	// 			ss<<"i:"<<i<<"\tj:"<<j<<"\tf:"<<f<<endl;
	// 		sum += f;
	// 		count++;

	// 	}
	// 	cout<<i;
	// 	file<<ss.str();
	// 	ss.str("");
	// 	//查看D平均数
	// 	cout<<" avg:"<<sum/(float)count<<endl;		

	// }
	// cout<<"sum of variance:"<<sum<<" avg:"<<sum/(float)users.size()<<endl;
	file.close();
	
	return;
}


int main(int argc, char const *argv[])
{
	readuser();	
	// readmovie();
	readusermovie();

	roc_file.open("roc_data2.txt",ios::out);

	vector<thread*> th_vec;
	string filename="job";
	//i就是k值，8-15，开8个线程，计算k值为8-15的结果
	for(int i=8;i<15;i++){
		char c=i+'0';
		filename.push_back(c);
		//线程执行job任务，后面是job的参数
		th_vec.push_back(new thread(job,filename+".txt",users,umap_movies,(float)(i)));
		filename.erase(filename.end()-1);
	}

	for(int i =0;i<th_vec.size();i++){
		th_vec[i]->join();
	}

	roc_file.close();
	
	return 0;
}


