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

// #include <sstream>
using namespace std;

pthread_mutex_t mut;   

unsigned int intmax = 0xffffffff;
unsigned long long int i=0;
unsigned long long int MAX=0x7fffffffffffffff;

void* tp1_generate64random(void* args){

	fstream ss;
	stringstream buffer;
	independent_bits_engine<default_random_engine,64,unsigned long long int> engine;
	ss.open("bignums.txt",ios::out);
	int k=0;
	for(i=0;i<0xffffffffffffffff;){
		buffer<<engine()<<"\n";
		if(k++>100){
			k=0;
			ss<<buffer.str();
			buffer.str("");
		}
		pthread_mutex_lock(&mut);
		i++;
		pthread_mutex_unlock(&mut);
	}
	ss.close();
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
void* tp2(void* args){
	int temp = i;

	while(1)
	{
		temp = i;
		delay();
		// pthread_mutex_lock(&mut);
		cout<<"i:"<<i<<" diff:"<<i-temp<<endl;
		// pthread_mutex_unlock(&mut);
		
	}
		
}

int main()
{


	pthread_t t1;
	pthread_t t2;

	pthread_mutex_init(&mut,NULL);
	pthread_create(&t1,NULL,tp1_generate64random,NULL); 
	pthread_create(&t2,NULL,tp2,NULL); 
	pthread_exit(NULL);
	system("pause");
	return 0;
}