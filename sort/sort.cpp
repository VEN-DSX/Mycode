#include "sort.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdio>
#include <algorithm>

using namespace std;


void print(vector<int> v1){
	for (vector<int>::iterator i = v1.begin(); i != v1.end(); ++i)
	{
		cout<<*i<<endl;
	}
}

int main(int argc, char const *argv[])
{
	random_device r;

	cout<<"Init new array"<<endl;
	vector<int> v1;
	for(int i = 0;i < 10000000;i++){
		v1.push_back(r());
	}
	cout<<"Init new array finished"<<endl;





	for(int i = 2;i<100;i+=1){	
		cout<<"i="<<i<<endl;
		vector<int> vv = v1;
		clock_t start = clock();
		// BubbleSort(vv);
		// printf("BubbleSort:\t %d \n",	clock() - start);
		
		// vv = v1;
		// start = clock();
		// SelectSort(vv);
		// printf("SelectSort:\t %d \n",	clock() - start);

		// vv = v1;
		// start = clock();
		// InsertSort(vv);
		// printf("InsertSort:\t %d \n",	clock() - start);

		vv = v1;
		start = clock();
		sort(vv.begin(),vv.end());
		printf("std::sort:\t%d \n",	clock() - start);


		vv = v1;
		start = clock();
		Qsort(vv,0,vv.size()-1);
		printf("Qsort:   \t%d \n",	clock() - start);

		vv = v1;
		start = clock();
		ImpQsortWithInsert(vv,0,vv.size()-1,i);
		printf("ImpQsortWithInsert:\t%d \n",	clock() - start);

		vv = v1;
		start = clock();
		ImpQsortWithSelect(vv,0,vv.size()-1,i);
		printf("ImpQsortWithSelect:\t%d \n",	clock() - start);

		vv = v1;
		start = clock();
		ImpQsortWithBubble(vv,0,vv.size()-1,i);
		printf("ImpQsortWithBubble:\t%d \n",	clock() - start);
		


		printf("\n\n");
	}
	// print(v1);
	return 0;
}