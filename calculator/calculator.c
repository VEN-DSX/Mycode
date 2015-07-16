#include "calculator.h"

#define MAXSIZE 1000
#define FUNC_NUM 23
#define YES 1
#define NO 0



int isOperate(char temp)//是否操作符  +-*/^()#  分别返回 12345678
{
    
	if(temp=='+') return 1;
	if(temp=='-') return 2;
	if(temp=='*') return 3;
	if(temp=='/') return 4;
	if(temp=='^') return 5;
	if(temp=='(') return 6;
	if(temp==')') return 7;
	if(temp=='#') return 8;
	return 0;
}

int isValue(char temp)//数值返回2和小数点返回1
{
    if(temp=='.'){return 1;}//
	if(temp>='0'&&temp<='9') {return 2;}	
	return 0;
}

int isLetter(char temp)//字母  大写返回1  小写返回2
{
	if(temp>=65&&temp<=90)	return 1;
	if(temp>=97&&temp<=122)   return 2;
	else return 0;
}

int isAvail(char temp)//是否有效字符
{
    if(isOperate(temp)||isValue(temp)||isLetter(temp))//temp既操作符和数值则非法
    {return 1;}
    return 0;
}                              



//******************************************
//			 以上为字符判断操作
//******************************************
 
    
    
char priority[8][8]=        //全局变量  + - * / &( ) #		//     + - * / & ( ) #
															//     1 2 3 4 5 6 7 8
					{ 
                        {'<','<','<','<','<','>','>','>'},//   + 1 < < < < < > > > 

                        {'<','<','<','<','<','>','>','>'},//   - 2 < < < < < > > >

                        {'>','>','<','<','<','>','>','>'},//   * 3 > > < < < > > >

                        {'>','>','<','<','<','>','>','>'},//   / 4 > > < < < > > > 
						
						{'>','>','>','>','>','<','>','>'}, //  & 5 > > > > > < > >

                        {'>','>','>','>','>','>','=','>'},//   ( 6 > > > > > > = 0 

                        {'<','<','<','<','<','=','0','>'}, //  ) 7 < < < < < = 0 >

                        {'<','<','<','<','<','>','<','='},  // # 8 < < < < < > 0 =
                    };

int detect(char temp)//搜索矩阵位置
{
    int i=0;
    char oper[8]={'+','-','*','/','^','(',')','#'};
    for(i=0;i<8;i++)
    {
        if(temp==oper[i])	{return i;}
    }
	return -1;
}


char Priority(char temp,char optr)//判断优先级
{
    int row ,col;
	row = detect(temp);//找出对应矩阵下标;
    col = detect(optr); 
	return priority[row][col];
}
//******************************************
//			以上为操作优先级判断操作
//******************************************

double evaluate(double a,double b,char oper)
{
    switch(oper)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
		case '^': return pow(a,b);
        default : return 0;
    }
}

double transnumber(char *a)   //把存在字符数组a里的数字字符转化为一个double型数字
{
	double num=0;
	int found=0,count=0;

	while(*(a)!='\0')
	{
		if(*(a)=='.') {found=1;a++;count++;continue;}
		num=num*10+*(a)-'0';
		a++;
		if(found==1) count++;
	}
	for(;count>1;count--)
	{
		num=num/10;
	}
	return num;

}//9999999999.999999

int isrightnumber(char *a)  //判断数字字符数组a里的数字是不是一个正确的数字
{
	int found=0;
	while(*(a+1)!='\0'&&isValue(*(a+1)))
	{
		if(*(a+1)=='.') found++;
		a++;
	}
	if(found==1||found==0) return 1;
	else return 0;
	
}

int getnumber(char *express,char *a)
{
	int i=0;
	while(isValue(*express)) 
	{
		
		*a=*express;
		i++;
		express++;
		a++;
	}
	*(a)='\0';
	return i;
}//从字符数组a中提取数字部分并返回到b数字字符数组中

int getletter(char *a,char *b)
{
	int i=0;
	int k;
	while(k=isLetter(*a)) 
	{
		if(k==1)	*a=*a+32;
		*b=*a;
		i++;
		a++;
		b++;
	}
	*(b)='\0';
	return i;	
}//将包含字母的运算符 (sin cos mod log)提取出来并赋到b中  同理于getNumber函数



double calculateExpress(char *express);//计算表达式    具体内容在main函数后面




int Array(char *express,double *array)
//将经过Mfunction_parameter_cutout处理的out作为这里的express,再将out中的 参数 提取到array数组进行下一步的处理 
{
	int i=0,j=0,m,n,k;
	char temp[MAXSIZE];
	char *t=(char*)malloc(sizeof(char));//临时变量
	StackO S;initO(&S);


	if(*express=='(')
	{
		n=1;m=0;k=1;
		if(*(express+1)=='[')
		{n=2;m=0;k=2;}
	}
	else
	{
		printf("error!\n");
		exit(-1);
	}
		do
		{
			if(*(express+m)=='(') 
			{
				pushO(&S,'1');			
			}
			if(*(express+m)=='[') 
			{
				pushO(&S,'2');			
			}
			
			if(*(express+m)==')')
			{
				getTopO(&S,t);
				if(*t=='1') popO(&S,t);
				else {printf("error!\n");exit(-1);}	
			}
			if(*(express+m)==']')
			{
				getTopO(&S,t);
				if(*t=='2') popO(&S,t);
				else {printf("error!\n");exit(-1);}	
			}

			if(( *(express+m) ==',' && S.top-S.base==k) ||  (S.top-S.base==k-1&&*(express+m+1)=='#') ) 
			{
				for(i=0;n<m;n++,i++)
				{
					temp[i]=*(express+n);
				}
				temp[i]='#';
				temp[i+1]='\0';
				*array=calculateExpress(temp);
				array++;
				j++;
				n++;
			}
			m++;
		
			 
		}while(*(express+m)!='\0');
	
	
	if(isEmptyO(&S)==0)
	{printf("error!\n");exit(-1);}
	return j;

}
char Mfunction[][9]=
{
	"sin","cos","tan",

	"sinh","cosh","tanh",

	"arcsin","arccos","arctan",

	"ln",
	
	"exp","fact",
	
	"cuberoot",	"sqrt",
	
	"avg","sum","var","varp","stdev","stdevp",

	
	"pow","mod","yroot","log",


};//一共23个 宏定义FUNC_NUM

int search_function(char *word)   //返回函数名在Mfunction的位置
{
	int i=0,found=0;char temp[8];
	for(i=0;isLetter(*word);i++) 
	{
		temp[i]=*word;
		word++;
	}
	temp[i]='\0';
	i=0;
	while(i<=FUNC_NUM) 
	{
		if(strcmp(temp,Mfunction[i])==0) {found=1;break;}
		i++;
	}
	if(found==1) return i;
	else return -1;

}

int Mfunction_parameter_cutout(char *express,char *out)
//函数返回一共有多少字符，out返回的是函数后面的参数表达式
{
	char *temp=(char*)malloc(sizeof(char));
	int i=0;
	StackO S;initO(&S);

	do
	{
		if(*express=='(') 
		{
			pushO(&S,*express);
		}
		
		if(*express==')')
		{
			popO(&S,temp);
		}
		*out=*express;
		out++;
		express++;
		i++;
		 
	}while(isEmptyO(&S)!=1);
	*out='#';
	*(out+1)='\0';

	return i;

}






int fact(int number)
{
    if (number==1||number==0) return 1;
    else return (number*fact(number-1));
} 

double sum(char *express)
{
	double sum=0.0;
	double *array=(double*)malloc(MAXSIZE*sizeof(double));
	int i=0;
	i=Array(express,array);
	for(;i>0;i--,array++)
	{
		sum+=*array;
	}

	return sum;
	

}

double avg(char *express)
{
	int i;
	double *b=(double*)malloc(MAXSIZE*sizeof(double));
	i=Array(express,b);
	return sum(express)/i;
}

double var(char *express)
{
	double va=0;
	double av=avg(express);
	double *b=(double*)malloc(MAXSIZE*sizeof(double));
	int i=Array(express,b);
	int n;
	for(n=0;n<i;n++,b++)
	{
		va+=(*b-av)*(*b-av);
	}
	return va/(i-1);

}

double varp(char *express)
{
	double va=0;
	double av=avg(express);
	double *b=(double*)malloc(MAXSIZE*sizeof(double));
	int i=Array(express,b);
	int n;
	for(n=0;n<i;n++,b++)
	{
		va+=(*b-av)*(*b-av);
	}
	return va/i;

}
double stdev(char *express)
{
	double va=0;
	double av=avg(express);
	double *b=(double*)malloc(MAXSIZE*sizeof(double));
	int i=Array(express,b);
	int n;
	for(n=0;n<i;n++,b++)
	{
		va+=(*b-av)*(*b-av);
	}
	return sqrt(va/(i-1));

}

double stdevp(char *express)
{
	double va=0;
	double av=avg(express);
	double *b=(double*)malloc(MAXSIZE*sizeof(double));
	int i=Array(express,b);
	int n;
	for(n=0;n<i;n++,b++)
	{
		va+=(*b-av)*(*b-av);
	}
	return sqrt(va/i);

}


//******************************************
//			以上为函数及数组操作
//******************************************



int function_evaluate(char *express,double *result)
//计算函数，并将结果存储到result中，返回整个函数包括他的参数的字符总长，方便控制外部express指针的移动
{
	char *out=(char*)malloc(MAXSIZE*sizeof(char));
	double *array=(double*)malloc(MAXSIZE*sizeof(double));
	int i=0,found=0,re,count,t;char temp[8];
	i=getletter(express,temp);
	express+=i;
	re=i;//re记录共有多少字符，方便控制外部使用的express指针
	i=0;
	while(i<=FUNC_NUM) 
	{
		if(strcmp(temp,Mfunction[i])==0) {found=1;break;}
		i++;
	}
	if(found!=1)  return -1;		//查找函数名 找不到就返回-1    此时i为函数名代号

	
	found=0;

	if(i<=13)
	{
		re+=Mfunction_parameter_cutout(express,out);
		*result=calculateExpress(out);
	}
	else 
	{
		if(i<=22)
		{
			re+=Mfunction_parameter_cutout(express,out);
			count=Array(out,array);
		}
	}

	switch(i)
	{
	case 0: *result=sin(*result);	break;
	case 1: *result=cos(*result);	break;
	case 2:	*result=tan(*result);	break;
	case 3:	*result=asin(*result);	break;		
	case 4:	*result=acos(*result);	break;			
	case 5:	*result=atan(*result);	break;				
	case 6:	*result=sinh(*result);	break;					
	case 7:	*result=cosh(*result);	break;						
	case 8:	*result=tanh(*result);	break;							
	case 9:	*result=log(*result);	break;						
	case 10:*result=exp(*result);	break;
	case 11:
		if(*result==(int)*result)*result=fact((int)*result);//是否为整数的判断（fact）
		else 
		{
			printf("fact函数参数非法！\n");
			exit(-1);
		}
		break;											
	case 12:*result=pow(*result,1.0/3.0);	break;												
	case 13:*result=sqrt(*result);		break;											
	case 14:*result=avg(out);			break;											
	case 15:*result=sum(out);			break;													
	case 16:*result=var(out);			break;														
	case 17:*result=varp(out);			break;															
	case 18:*result=stdev(out);			break;																
	case 19:*result=stdevp(out);		break;
	case 20:*result=pow(*array,*(array+1));break;
	case 21:												
		if(*array==(int)*array&&*(array+1)==(int)*(array+1)) *result=((int)(*array))%((int)(*(array+1)));//是否为整数的判断（mod）
		else 
		{
			printf("mod函数参数非法！\n");
			exit(-1);
		}
		break;
	case 22:*result=pow(*array,1/(*(array+1)));break;
	case 23:
		while(isValue(*express)==2) 
			{found=10*found+(*express-'0');re++;express++;}
		re+=Mfunction_parameter_cutout(express,out);
		t=Array(out,array);
		if(found==10||found==0)
		{
			if(found==10)
				*result=log(*array)/log(10);
			if(found==0)
			*result=log(*array)/log(*(array+1));
		}
		else
		{
			printf("log函数出错\n");
			exit(-1);
		}

		break;

	}
	return re;
}





void inputExpress(char *express)//输入表达式
{
    int length=0;
	char *temp=(char *)malloc(MAXSIZE*sizeof(char));
    gets(temp);
	while(*temp!='\0')
	{
		if(*temp==' ') 
		{
			temp++;
			continue;
		}
		*express=*temp;
		express++;
		temp++;
	}
    *express='#';//表达式位默认'#';
    *(express+1)='\0';
}

void output(char *express,double result)//输出表达式
{
    int i=0;
    printf("\n表达式:");
    while(express[i]!='#')
    {
        printf("%c",express[i]);
        i++;
    }
    printf("=%lf\n",result);
}




int main()
{

    char express[MAXSIZE];//表达式 
    double result =0;
    inputExpress(express);//输入表达式搜索
	result = calculateExpress(express);//计算表达式；
	output(express,result); //输出表达式

	system("pause");
   return 0;
}







double calculateExpress(char *express)//计算表达式
{
    double *result=(double*)malloc(sizeof(double));     //用来存储运算结果
	char *tempc=(char*)malloc(MAXSIZE*(sizeof(char)));  //在本函数中充当express的角色	
    double *a=(double*)malloc(sizeof(double));//运算数
	double *b=(double*)malloc(sizeof(double));//运算数
	char *t=(char*)malloc(MAXSIZE*(sizeof(char)));//临时使用变量
	char prior;//存储优先级符 方便进行压栈运算
	double c;//配合getnumber函数使用 获得从express中提取到的数字
	int step;//控制express指针移动的步伐变量
   // char oper,result;
	StackO OPTR;//OPTR存储操作符
	StackN OPND;//OPND操作数值
    initO(&OPTR);
    initN(&OPND);
    pushO(&OPTR,'#');

    while(*express!='\0')
    {
        
        tempc= express; 
        //printf("---------------------------------\n");
        //printf("当前符号%c\n",tempc);
        if(isAvail(*tempc))//否有效字符
        { 
                if(isOperate(*tempc) )//输入操作符
                {
					char *oper=(char*)malloc(sizeof(char));
					double result;
                    char *optr;
					char useless;
					optr=(char *)malloc(sizeof(char));//栈top位操作符
					getTopO(&OPTR,optr);

                    //printf("栈顶操作符位：%c\n",optr);
                    
					prior = Priority(*tempc,*optr);//判断优先级
                    switch(prior)
                    {
                        case '>':
                                    pushO(&OPTR,*tempc);
																//printf("符号位%c入栈\n",tempc);
                                    express++;
                                    break;
                        case '<':
									popN(&OPND,a);		
                                    popN(&OPND,b);

                                    popO(&OPTR,oper);
                                    result=evaluate(*b,*a,*oper);  //出栈操作符计算结
																//printf("%d",result-'0');
                                    pushN(&OPND,result);			//结入OPND
																//printf("%d%c%d结:%d\n",b,oper,a,result-'0');
									
                                    break;               
                        case '=':								//消除括号
									
                                    popO(&OPTR,&useless);
																//printf("消除括号\n");
                                    express++;
                                    break;
                    }
                }


                if(isValue(*tempc))//输入数值
                {
					step=getnumber(tempc,t);
					if(isrightnumber(t))
					{
						c=transnumber(t);
					}
					else
					{
						printf("非法数字\n");
						exit(-1);//退出程序
					}
                    pushN(&OPND,c);//数值位入栈;
                    express+=step;
					step=0;
                    //printf("数值%c压入栈\n",tempc);
                    //show(&OPND);
                }

				if(isLetter(*tempc))
				{
					//step=getletter(tempc,t);
					//search_function(t);
					//Mfunction_parameter_cutout(tempc,t);
					step=function_evaluate(tempc,&c);
					if(step==-1) 
					{
						printf("函数不支持!\n");
						exit(-1);
					}
					pushN(&OPND,c);//数值位入栈;
                    express+=step;
					step=0;

				}


        }
        else //表达式有非法字符
        {
			if(*tempc==' ') {express++;continue;}
            printf("表达式有非法字符\n");
            exit(-1);//退出程序
        }
}
	getTopN(&OPND,result);
    return *result;
}
