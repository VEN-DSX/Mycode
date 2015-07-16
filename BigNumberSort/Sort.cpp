#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <queue>
#include <gmpxx.h>


using namespace std;

queue<mpz_class> q;
mpz_class sum;
int line=0;
pthread_mutex_t mut; 


void delay(){
	int k=0;
	for(int i =0;i<10000;i++){
		for (int j = 0; j < 10000; ++j)
		{
			k++;
		}
	}
}
void* tp1_readintoqueue(void* args){
	fstream ss;
	ss.open("..\\bignums.txt",ios::in);

	string temp;
	mpz_class tt;
	while(ss>>tt){
			
			if(q.size() > 500 ){
				delay();
			}
			q.push(tt);
			line++;
			// getline(ss,temp);
			// tt = temp;
			// pthread_mutex_lock(&mut);
			
			// pthread_mutex_unlock(&mut);
	}
	
}


void* tp2_popfromqueue(void* args){
	int temp;
	while(1){
		// delay();

		pthread_mutex_lock(&mut);
		if(!q.empty()){
			sum = sum + q.front();
		    q.pop();
		}
		pthread_mutex_unlock(&mut);
		  
	}
}
void* tp3_performence_watching(void* args){
	while(true){
		delay();
		pthread_mutex_lock(&mut);
		cout<<"q size:"<<q.size()<<" sum:"<<sum/line<<" line:"<<line<<endl;
		pthread_mutex_unlock(&mut);
	}
}
int main()
{
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	// pthread_t t4;

	pthread_mutex_init(&mut,NULL);
	pthread_create(&t1,NULL,tp1_readintoqueue,NULL); 
	pthread_create(&t2,NULL,tp2_popfromqueue,NULL); 
	pthread_create(&t3,NULL,tp3_performence_watching,NULL); 
	// pthread_create(&t4,NULL,tp2,NULL); 
	pthread_exit(NULL);
	cout<<"done!"<<endl;
	cout<<sum/line<<endl;
	system("pause");
	return 0;
}