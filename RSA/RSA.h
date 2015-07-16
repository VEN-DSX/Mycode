#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>

namespace RSA {

using namespace std;

int n, e = 0, d;

//二进制转换
int BianaryTransform(int num, bitset<1024> &bin_num)
{

    int i = 0,  mod = 0;

    //转换为二进制，逆向暂存bin_num[]数组中
    while(num != 0)
    {
        mod = num%2;
        bin_num[i] = mod;
        num = num/2;
        i++;
    }

    //返回二进制数的位数
    return i;
}

//反复平方法快速求幂
long long Modular_Exonentiation(long long a, int b, int n)
{
    bitset<1024> bin_num;
    int k = BianaryTransform(b, bin_num)-1;
    long long d = 1;

    for(int i = k; i >= 0; i--)
    {
        d = (d*d)%n;
        if(bin_num[i] == true)
        {
            d = (d*a)%n;
        }
    }
    return d;
}
bool isPrime(int nr)
{
    for (int d = 2; (d * d) <= (nr + 1); ++d){
        if (!(nr % d)){
            return false;
        }
     }
    return true;
}


//欧几里得扩展算法
int Exgcd(int m,int n,int &x)
{
    int x1,y1,x0,y0, y;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    int r=m%n;
    int q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}

vector<int> GenerateTwoPrime()
{
    vector<int> res;
    srand((unsigned)time(NULL));
    int ranNum1 = rand();
    int ranNum2 = rand();

    while(!isPrime(ranNum1)) ranNum1++;
    while(!isPrime(ranNum2) || ranNum2==ranNum1) ranNum2++;


    res.push_back(ranNum1);
    res.push_back(ranNum2);
    return res;
}

//RSA初始化
void RSA_Initialize(int a=0,int b=0)
{

    vector<int> pri = GenerateTwoPrime();

    int p,q;
    if(a==0&&b==0)
        p = pri[0], q = pri[1];
    else
        p=a;q=b;

        n = p*q;

    int On = (p-1)*(q-1);


    //用欧几里德扩展算法求e,d
    for(int j = 3; j < On; j+=1331)
    {
        int gcd = Exgcd(j, On, d);
        if( gcd == 1 && d > 0)
        {
            e = j;
            break;
        }

    }

}

typedef union{
    unsigned int num;
    unsigned char  c[2]; // 0=>low_low 8-bit,1=>low_high 8-bit,3=>high_high 8-bit

}chars;


string RSA_Encrypt(string s){
    string res;
    stringstream ss;

    for (unsigned int i = 0; i < s.length(); i+=2)
    {
        chars num;num.num = 0;
        if(i+2 > s.length()){
            for(int j=0;j<s.length()-i;j++){
                num.c[j]=s[i+j];
            }
        }else{
            for(int j=0;j<2;j++){
                num.c[j]=s[i+j];
            }
        }
        ss << Modular_Exonentiation(num.num, e, n);


        res = res + ss.str() + "@";
        ss.str("");
    }

    return res.substr(0,res.size()-1);
}



string RSA_Decrypt(string s){
    string res;
    stringstream ss;

    chars num;

    string temp;
    int last=0;
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        if(s[i] == '@'){
            temp = s.substr(last,i - last);
            last = i+1;
            chars  c;
            c.num = Modular_Exonentiation(strtoul( temp.c_str(),0,10), d, n);
            for(int j=0;j<2;j++){
                if(c.c[j] != 0x00)
                {
                    res.push_back(c.c[j]);
                }

            }
            ss.str("");
        }
    }
    return res;
}

}
#endif // RSA_H

