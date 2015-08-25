#ifndef _SORT_
#define _SORT_ 

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
void Swap(T &a,T &b){
	T tmp = a;
	a = b;
	b = tmp;
}

//AVG:O(N2) BEST:O(N) WORST:O(N2) SPACE:O(1) STABLE
template <typename T>
void BubbleSort(std::vector<T> &_tar){
	for(int i = 0;i < _tar.size();i++){
		for (int j = 0; j < _tar.size()-1 - i; ++j)
		{
			if(_tar[j] > _tar[j+1]){
				swap(_tar[j],_tar[j+1]);
			}
		}
	}
}

template <typename T>
void BubbleSort(std::vector<T> &_tar, int start ,int end){
    for(int i = start;i < end;i++){
        for (int j = start; j < end-1 - i; ++j)
        {
            if(_tar[j] > _tar[j+1]){
                swap(_tar[j],_tar[j+1]);
            }
        }
    }
}

//AVG:O(N2) BEST:O(N2) WORST:O(N2) SPACE:O(1) UNSTABLE
//EG:5 8 5 2 9，the first element 5 will exchange with the fourth element 2
template <typename T>
void SelectSort(std::vector<T> &_tar){
	for (int i = 0; i < _tar.size(); ++i)
	{
		int index_min = i;
		for (int j = i+1; j < _tar.size(); ++j)
		{
			if(_tar[j] < _tar[index_min]){
				index_min = j;
			}
		}
		Swap(_tar[i],_tar[index_min]);
	}
}

template <typename T>
void SelectSort(std::vector<T> &_tar, int start ,int end){
    for (int i = start; i < end; ++i)
    {
        int index_min = i;
        for (int j = i+1; j < end; ++j)
        {
            if(_tar[j] < _tar[index_min]){
                index_min = j;
            }
        }
        Swap(_tar[i],_tar[index_min]);
    }
}


//AVG:O(N2) BEST:O(N) WORST:O(N2) SPACE:O(1) STABLE
template <typename T>
void InsertSort(std::vector<T> &_tar){
	for (int i = 1; i < _tar.size(); ++i)
	{
		if (_tar[i] < _tar[i-1]){
			int temp = _tar[i];
			int j ;
			for (j = i-1; j > 0 && _tar[j] > temp; j--){
				_tar[j+1] = _tar[j];
			}
			_tar[j] = temp;
		}
	}
}
template <typename T>
void InsertSort(std::vector<T> &_tar, int start, int end){
    for (int i = start+1; i < end; ++i)
    {
        if (_tar[i] < _tar[i-1]){
            int temp = _tar[i];
            int j ;
            for (j = i-1; j > 0 && _tar[j] > temp; j--){
                _tar[j+1] = _tar[j];
            }
            _tar[j] = temp;
        }
    }
}


//quick sort
//AVG:O(NLOG2N) BEST:O(NLOG2N) WORST:O(N2) SPACE:O(NLOG2N) UNSTABLE
template <typename T>
void qsort(std::vector<T> &a, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    int first = start;
    int last = end;
    int key = a[first];/*take the first value as the key*/
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
 
        a[first] = a[last];/*将比第一个小的移到低端*/
 
        while(first < last && a[first] <= key)
        {
            ++first;
        }
         
        a[last] = a[first];    
	/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    qsort(a, start, first-1);
    qsort(a, first+1, end);
}

template <typename T>
void Qsort(std::vector<T> &a)
{
    qsort(a,0,a.size()-1);
}

template <typename T>
void Qsort(std::vector<T> &a, int start, int end)
{
    qsort(a,start,end);
}


//improved quick sort
template <typename T>
void ImpQsortWithInsert(std::vector<T> &a, int start, int end, int step)
{
    if(start >= end)
    {
        return;
    }
    if(end - start < step){
        InsertSort(a,start,end);
        return;
    }
    int first = start;
    int last = end;
    int key = a[first];/*take the first value as the key*/
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
 
        a[first] = a[last];/*将比第一个小的移到低端*/
 
        while(first < last && a[first] <= key)
        {
            ++first;
        }
         
        a[last] = a[first];    
	/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    ImpQsortWithInsert(a, start, first-1 ,step);
    ImpQsortWithInsert(a, first+1, end   ,step);
}
template <typename T>
void ImpQsortWithSelect(std::vector<T> &a, int start, int end, int step)
{
    if(start >= end)
    {
        return;
    }
    if(end - start < step){
        SelectSort(a,start,end);
        return;
    }
    int first = start;
    int last = end;
    int key = a[first];/*take the first value as the key*/
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
 
        a[first] = a[last];/*将比第一个小的移到低端*/
 
        while(first < last && a[first] <= key)
        {
            ++first;
        }
         
        a[last] = a[first];    
    /*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    ImpQsortWithSelect(a, start, first-1 ,step);
    ImpQsortWithSelect(a, first+1, end   ,step);
}

template <typename T>
void ImpQsortWithBubble(std::vector<T> &a, int start, int end, int step)
{
    if(start >= end)
    {
        return;
    }
    if(end - start < step){
        BubbleSort(a,start,end);
        return;
    }
    int first = start;
    int last = end;
    int key = a[first];/*take the first value as the key*/
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
 
        a[first] = a[last];/*将比第一个小的移到低端*/
 
        while(first < last && a[first] <= key)
        {
            ++first;
        }
         
        a[last] = a[first];    
    /*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    ImpQsortWithBubble(a, start, first-1 ,step);
    ImpQsortWithBubble(a, first+1, end   ,step);
}

//Shell sort
template <typename T>
void ShellSort(std::vector<T> &arr)
{
    cout<<"shell\n";
    int i, j, k, temp;
    //i为增量
    for(i=arr.size()/2;i>0;i/=2)
    {
        for(j=i;j<arr.size();j+=i)
        {
            temp = arr[j];
            k = j;
            while(k-i>=0 && temp<arr[k-i])
            {
                arr[k] = arr[k-i];
                k -= i;
            }
            arr[k] = temp;
        }
    }
}



#endif