#include "calculator.h"

#define MAXSIZE 1000
#define FUNC_NUM 23
#define YES 1
#define NO 0



int isOperate(char temp)//�Ƿ������  +-*/^()#  �ֱ𷵻� 12345678
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

int isValue(char temp)//��ֵ����2��С���㷵��1
{
    if(temp=='.'){return 1;}//
	if(temp>='0'&&temp<='9') {return 2;}	
	return 0;
}

int isLetter(char temp)//��ĸ  ��д����1  Сд����2
{
	if(temp>=65&&temp<=90)	return 1;
	if(temp>=97&&temp<=122)   return 2;
	else return 0;
}

int isAvail(char temp)//�Ƿ���Ч�ַ�
{
    if(isOperate(temp)||isValue(temp)||isLetter(temp))//temp�Ȳ���������ֵ��Ƿ�
    {return 1;}
    return 0;
}                              



//******************************************
//			 ����Ϊ�ַ��жϲ���
//******************************************
 
    
    
char priority[8][8]=        //ȫ�ֱ���  + - * / &( ) #		//     + - * / & ( ) #
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

int detect(char temp)//��������λ��
{
    int i=0;
    char oper[8]={'+','-','*','/','^','(',')','#'};
    for(i=0;i<8;i++)
    {
        if(temp==oper[i])	{return i;}
    }
	return -1;
}


char Priority(char temp,char optr)//�ж����ȼ�
{
    int row ,col;
	row = detect(temp);//�ҳ���Ӧ�����±�;
    col = detect(optr); 
	return priority[row][col];
}
//******************************************
//			����Ϊ�������ȼ��жϲ���
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

double transnumber(char *a)   //�Ѵ����ַ�����a��������ַ�ת��Ϊһ��double������
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

int isrightnumber(char *a)  //�ж������ַ�����a��������ǲ���һ����ȷ������
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
}//���ַ�����a����ȡ���ֲ��ֲ����ص�b�����ַ�������

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
}//��������ĸ������� (sin cos mod log)��ȡ����������b��  ͬ����getNumber����



double calculateExpress(char *express);//������ʽ    ����������main��������




int Array(char *express,double *array)
//������Mfunction_parameter_cutout�����out��Ϊ�����express,�ٽ�out�е� ���� ��ȡ��array���������һ���Ĵ��� 
{
	int i=0,j=0,m,n,k;
	char temp[MAXSIZE];
	char *t=(char*)malloc(sizeof(char));//��ʱ����
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


};//һ��23�� �궨��FUNC_NUM

int search_function(char *word)   //���غ�������Mfunction��λ��
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
//��������һ���ж����ַ���out���ص��Ǻ�������Ĳ������ʽ
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
//			����Ϊ�������������
//******************************************



int function_evaluate(char *express,double *result)
//���㺯������������洢��result�У��������������������Ĳ������ַ��ܳ�����������ⲿexpressָ����ƶ�
{
	char *out=(char*)malloc(MAXSIZE*sizeof(char));
	double *array=(double*)malloc(MAXSIZE*sizeof(double));
	int i=0,found=0,re,count,t;char temp[8];
	i=getletter(express,temp);
	express+=i;
	re=i;//re��¼���ж����ַ�����������ⲿʹ�õ�expressָ��
	i=0;
	while(i<=FUNC_NUM) 
	{
		if(strcmp(temp,Mfunction[i])==0) {found=1;break;}
		i++;
	}
	if(found!=1)  return -1;		//���Һ����� �Ҳ����ͷ���-1    ��ʱiΪ����������

	
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
		if(*result==(int)*result)*result=fact((int)*result);//�Ƿ�Ϊ�������жϣ�fact��
		else 
		{
			printf("fact���������Ƿ���\n");
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
		if(*array==(int)*array&&*(array+1)==(int)*(array+1)) *result=((int)(*array))%((int)(*(array+1)));//�Ƿ�Ϊ�������жϣ�mod��
		else 
		{
			printf("mod���������Ƿ���\n");
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
			printf("log��������\n");
			exit(-1);
		}

		break;

	}
	return re;
}





void inputExpress(char *express)//������ʽ
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
    *express='#';//���ʽλĬ��'#';
    *(express+1)='\0';
}

void output(char *express,double result)//������ʽ
{
    int i=0;
    printf("\n���ʽ:");
    while(express[i]!='#')
    {
        printf("%c",express[i]);
        i++;
    }
    printf("=%lf\n",result);
}




int main()
{

    char express[MAXSIZE];//���ʽ 
    double result =0;
    inputExpress(express);//������ʽ����
	result = calculateExpress(express);//������ʽ��
	output(express,result); //������ʽ

	system("pause");
   return 0;
}







double calculateExpress(char *express)//������ʽ
{
    double *result=(double*)malloc(sizeof(double));     //�����洢������
	char *tempc=(char*)malloc(MAXSIZE*(sizeof(char)));  //�ڱ������г䵱express�Ľ�ɫ	
    double *a=(double*)malloc(sizeof(double));//������
	double *b=(double*)malloc(sizeof(double));//������
	char *t=(char*)malloc(MAXSIZE*(sizeof(char)));//��ʱʹ�ñ���
	char prior;//�洢���ȼ��� �������ѹջ����
	double c;//���getnumber����ʹ�� ��ô�express����ȡ��������
	int step;//����expressָ���ƶ��Ĳ�������
   // char oper,result;
	StackO OPTR;//OPTR�洢������
	StackN OPND;//OPND������ֵ
    initO(&OPTR);
    initN(&OPND);
    pushO(&OPTR,'#');

    while(*express!='\0')
    {
        
        tempc= express; 
        //printf("---------------------------------\n");
        //printf("��ǰ����%c\n",tempc);
        if(isAvail(*tempc))//����Ч�ַ�
        { 
                if(isOperate(*tempc) )//���������
                {
					char *oper=(char*)malloc(sizeof(char));
					double result;
                    char *optr;
					char useless;
					optr=(char *)malloc(sizeof(char));//ջtopλ������
					getTopO(&OPTR,optr);

                    //printf("ջ��������λ��%c\n",optr);
                    
					prior = Priority(*tempc,*optr);//�ж����ȼ�
                    switch(prior)
                    {
                        case '>':
                                    pushO(&OPTR,*tempc);
																//printf("����λ%c��ջ\n",tempc);
                                    express++;
                                    break;
                        case '<':
									popN(&OPND,a);		
                                    popN(&OPND,b);

                                    popO(&OPTR,oper);
                                    result=evaluate(*b,*a,*oper);  //��ջ�����������
																//printf("%d",result-'0');
                                    pushN(&OPND,result);			//����OPND
																//printf("%d%c%d��:%d\n",b,oper,a,result-'0');
									
                                    break;               
                        case '=':								//��������
									
                                    popO(&OPTR,&useless);
																//printf("��������\n");
                                    express++;
                                    break;
                    }
                }


                if(isValue(*tempc))//������ֵ
                {
					step=getnumber(tempc,t);
					if(isrightnumber(t))
					{
						c=transnumber(t);
					}
					else
					{
						printf("�Ƿ�����\n");
						exit(-1);//�˳�����
					}
                    pushN(&OPND,c);//��ֵλ��ջ;
                    express+=step;
					step=0;
                    //printf("��ֵ%cѹ��ջ\n",tempc);
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
						printf("������֧��!\n");
						exit(-1);
					}
					pushN(&OPND,c);//��ֵλ��ջ;
                    express+=step;
					step=0;

				}


        }
        else //���ʽ�зǷ��ַ�
        {
			if(*tempc==' ') {express++;continue;}
            printf("���ʽ�зǷ��ַ�\n");
            exit(-1);//�˳�����
        }
}
	getTopN(&OPND,result);
    return *result;
}
