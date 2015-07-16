#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>

typedef struct 
{
    double number[MAXSIZE];
    int top;//头地址
    int base;//基地址
    int length;//长度
}StackN;

typedef struct 
{
    char data[MAXSIZE];
    int top;//头地址
    int base;//基地址
    int length;//长度
}StackO;

void initN(StackN *S)//初始化栈
{
	S->number[0]=0.0;
    S->base=0;
    S->top=1;
    S->length=1;
}

void initO(StackO *S)//初始化栈
{
    S->base=0;
    S->top=0;
    S->length=0;
}

int isEmptyN(StackN *S)//判断栈是否为空
{
    int n=0,top,base;
    top =S->top;
    base =S->base;
    if(top==base)
    {
        return 1;
    }
    return n;
}

int isEmptyO(StackO *S)//判断栈是否为空
{
    int n=0,top,base;
    top =S->top;
    base =S->base;
    if(top==base)
    {
        return 1;
    }
    return n;
}

int isFullN(StackN *S)
{
    int n=0,top,base;
    top =S->top;
	base =S->base;
    if(top>=1000)
    {
        return 1;
    }
    return n;
}
int isFullO(StackO *S)
{
    int n=0,top,base;
    top =S->top;
	base =S->base;
    if(top>=1000)
    {
        return 1;
    }
    return n;
}

int getTopN(StackN *S,double *e)// 返回top值改变栈结构
{
    if(isEmptyN(S))
    {
        return 0;
    }
	*e=S->number[S->top-1];//取出数据;    
	return 1;
}

int getTopO(StackO *S,char *e)// 返回top值改变栈结构
{
    if(isEmptyO(S))
    {
        return 0;
    }
	*e=S->data[S->top-1];//取出数据;    
	return 1;
}

int popN(StackN *S,double *e)// 出栈返回
{
    if(isEmptyN(S))
    {
        printf("栈空\n");
		exit(-1);
    } 
	*e=S->number[S->top-1];
	S->top--;
    S->length--;
    S->number[S->top]='\0';//消除数据

    return 1;//取出数据;
}
int popO(StackO *S,char *e)// 出栈返回
{
    if(isEmptyO(S))
    {
		printf("栈空\n");
		exit(-1);
    } 
	*e=S->data[S->top-1];//取出数据;
	S->top--;
    S->length--;
    S->data[S->top]='\0';//消除数据

    return 1;
}

void pushN(StackN *S,double n)//入栈
{
    if(isFullN(S))
    {
        printf("栈满\n");      
    }
    else
    {
		S->number[S->top]=n;//存入数据
		S->top++;//改变位置
    }

}
void pushO(StackO *S,char n)//入栈
{
    if(isFullO(S))
    {
        printf("栈满\n");      
    }
    else
    {
		S->data[S->top]=n;//存入数据
		S->top++;//改变位置
    }

}

void showN(StackN *S)//输出栈数据
{
    int top,base;
    top=S->top;
    base=S->base;
    while(top>base)
    {
        printf("%d,",S->number[--top]);
    }
    printf("\n");
}
void showO(StackO *S)//输出栈数据
{
    int top,base;
    top=S->top;
    base=S->base;
    while(top>base)
    {
        printf("%c,",S->data[--top]);
    }
    printf("\n");
}                                 

//******************************************
//				以上为栈操作
//******************************************
