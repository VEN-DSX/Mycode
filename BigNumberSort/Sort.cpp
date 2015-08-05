#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
// #include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <queue>
#include <gmpxx.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <mingw.thread.h>
#include <ctime>

#define KTH 100

using namespace std;

queue<string> que_string_filename;
mpz_class sum=0;
int int32_line_total=0;
bool readfile_finished = false;
sem_t availablefile;



void delay();


class NumCount{
public:
	string num;
	int count;
	NumCount(){};
	NumCount(string x,int y){
		num = x;
		count = y;
	};
	bool operator<(NumCount &x){
		if(this->count > x.count)
			return true;
		else
			return false;
	}
	int set_val(string x,int y){
		num = x;
		count = y;
		return 1;
	}
};
/*
	找到前K个出现频次最大的数据，并输出至文件中
*/
void findKth(unordered_map<string,int> umap_string_int_count,int k){
	cout<<"findKth\t"<<umap_string_int_count.size()<<endl;
	vector<NumCount> min_heap(k);
	NumCount temp;
	int c=0;
	//最小堆
	for (unordered_map<string,int>::iterator i = umap_string_int_count.begin(); i != umap_string_int_count.end(); ++i)
	{		
		temp.set_val(i->first,i->second);
		if(c<k){
			min_heap[c]=temp;
			c++;
		}else if(temp.count > min_heap.front().count){
			swap(min_heap[0],temp);
			make_heap(min_heap.begin(),min_heap.end()); // where can be optimized
		}
	}
	sort_heap(min_heap.begin(),min_heap.end());
	
	//write
	fstream fs_out;
	fs_out.open("umap_string_int_count.txt",ios::out);
	stringstream s_s;
	int asdf=0;
	for(auto i = min_heap.begin();i!=min_heap.end();i++){
		s_s<<i->num<<"\t"<<i->count<<"\n";
		// cout<<i->num<<"\t"<<i->count<<endl;
		while(++asdf>100){
			fs_out<<s_s.str();
			s_s.str("");
			asdf=0;
		}
	}
	fs_out<<s_s.str();
	s_s.str("");
	fs_out.close();
	return;

}

/*
	将读入的数据排序，并写入文件
*/
void sort_write_file(vector<mpz_class> vec_numbers,int int32_line_temp,int int32_line_total){
	clock_t start,end;
	cout<<"sort numbers under "<<int32_line_total<<endl;
	start = clock();
	sort(vec_numbers.begin(),vec_numbers.end());
	end = clock();
	cout<<"sort end! using:"<<end-start<<"MS"<<endl;			
	int32_line_temp = 0;
	//文件处理
	stringstream s_s;
	fstream fs_out;
	//获得文件名
	s_s<<int32_line_total<<".txt";
	string temp_filename = s_s.str();
	fs_out.open(temp_filename,ios::out); 
	s_s.str("");
	int temp_line=0;
	for (std::vector<mpz_class>::iterator i = vec_numbers.begin(); i != vec_numbers.end(); ++i)
	{
		s_s<<*i<<endl;
		if(++temp_line > 1000){ //缓存1000条再存到文件里
			temp_line = 0;
			fs_out<<s_s.str();//写入文件
			s_s.str("");
		}
	}
	fs_out<<s_s.str();
	s_s.str("");
	fs_out.close();
	que_string_filename.push(temp_filename);
	sem_post(&availablefile);
	cout<<"Thread end!"<<endl;
	return;
}




/*
*/
void tp_mergesort(){
	
}



/*
	读入数据的线程，
	负责，统计最大，最小，平均数，hashtable的生成，读完文件分列数据
*/
void tp1_readintoqueue(){
	fstream fs_in;
	fs_in.open("bignums.txt",ios::in);

	mpz_class tt;
	mpz_class min;
	mpz_class max;

	//read the first line as min and max
	fs_in>>tt;
	min = tt;
	max = tt;
	
	//to find the k repeated most numbers;
	unordered_map<string,int> umap_string_int_count;

	queue<string> queue_string;

	vector<thread*> vec_thread;

	int int32_line_limit = 2000000;
	int int32_line_temp = 1;
	
	vector<mpz_class> vec_numbers(int32_line_limit);
	vec_numbers.clear();
	vec_numbers.push_back(tt);
	while(fs_in>>tt){
		
			int32_line_temp++;
			vec_numbers.push_back(tt);
			sum+=tt;
			int32_line_total++;
			if(tt > max) max = tt;
			if(tt < min) min = tt;

			//hash to get frequence
			umap_string_int_count[tt.get_str()]++;


			// SORT and write

			if(int32_line_temp >= int32_line_limit){
				cout<<"Init a thread to sort"<<endl;
				vec_thread.push_back(new thread(sort_write_file,vec_numbers,int32_line_temp,int32_line_total));
				vec_numbers.clear();
				int32_line_temp = 0;
			}
			if(int32_line_temp == 0) cout<<"   continue!"<<endl;

			
				
	}
	vec_thread.push_back(new thread(findKth,umap_string_int_count,KTH));

	sort_write_file(vec_numbers,int32_line_temp,int32_line_total);
	for (std::vector<thread*>::iterator i = vec_thread.begin(); i != vec_thread.end(); ++i)
	{
		(*i)->join();
		cout<<&i<<" OK!"<<endl;
	}
	cout<<"sum:"<<sum<<endl;
	cout<<"max:"<<max<<endl;
	cout<<"min:"<<min<<endl;
	cout<<"avg:"<<sum/int32_line_total<<endl;
	fs_in.close();
	
	
}



void init(){
	sem_init(&availablefile, 0, 0);
	thread  t[4];
	t[0] = thread(tp1_readintoqueue);
	t[0].join();
	sem_destroy(&availablefile);
	return;
}


// 超大数据排序：
// 1.读入M条数据，排序，写入临时文件tf_n,直到完毕
// 2.两两文件归并排序，结果写入临时文件MS_tf_n,删除文件，直到结束
// 3
int main()
{		
	init();

	system("pause");
	return 0;
}


void delay(){
	int k=0;
	for(int i =0;i<10000;i++){
		for (int j = 0; j < 10000; ++j)
		{
			k++;
		}
	}
}