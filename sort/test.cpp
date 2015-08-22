#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int printf(const char* format, ...);

int global_init_var = 84; //已初始化的全局变量
int global_uninit_var;    //未初始化的全局变量
char *str1 = "hello world!"; //字符串常量

void func1(int i)
{
  printf("%d\n", i);
}

class A{
public:
	A(){
		_int32 = 1;
	}

	int add(int i){
		_int32 +=i;
	}

private:
	int _int32;
};

int main(void)
{
  A x;
  x.add(1);
  static int static_var = 85; //已初始化的静态局部变量
  static int static_var2;     //未初始化的静态局部变量 
  char *str2 = "22222";       //字符串常量

  int a = 1;
  int b;

  func1(static_var+static_var2+a+b);

  return a;
}