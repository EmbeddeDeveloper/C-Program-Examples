#include<stdio.h>
#include<ctype.h>
#define MAXLINE 100
#define MAXOP 6
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp=0;
double stck[MAXVAL];
int sp=0;

void push(double f);
double pop(void);
int getint(int *pn);
int getch(void);
void ungetch(int);

double atof(char s[])
{
int sign,i;
double val,power;

//for(i=0;isspace(s[i]);i++)
for(i=0;s[i]=='\0';i++)
	 ;
	sign=(s[i]=='-')?-1:1;
		if(s[i]=='+'||s[i]=='-')
			++i;
		//for(val=0.0;isdigit(s[i]);i++)
			for(val=0.0;s[i]>='0' && s[i]<='9';i++)
			val = 10.0*val+(s[i]-'0');
		if(s[i]=='.')
		i++;
		//for(power=1.0;isdigit(s[i]);i++)
		for(power=1.0;s[i]>='0' && s[i]<='9';i++)
			{
			val = 10.0*val+(s[i]-'0');
			power *=10.0;
			}

			return sign*val/power;
}

int main()
{
int type;
double op2;
int *s[MAXOP];

	while((type=getint(*s))!=EOF)
	{
		switch(type)
		{
		case NUMBER:
				push(atof(s));
				break;
		case '+':
				push(pop()+pop());
				break;
		case '*':
				push(pop()*pop());
				break;
		case '-':
				op2=pop();
				push(pop()-op2);
				break;
		case '/':
				op2=pop();
				if(op2!=0.0)
					push(pop()/op2);
				else
					printf("error:zero divisor\n");
				break;
		case '\n':
				printf("\t%.8g\n",pop());
				break;
		default:
				printf("error:unknown command %s\n",s);
				break;
		}
	}
	return 0;
}


int getline(char s[],int lim)
{
int c,i;
	for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
		s[i]=c;
		if(c=='\n')
		{
		 s[i]=c;
		 ++i;
		}
		s[i]='\0';
		return i;

}

void push(double f)
{
	if(sp<MAXVAL)
		stck[sp++]=f;
	else
		printf("error: Stack Full %g\n",f);
}

double pop(void)
{
	if(sp>0)
		{printf("%g\n",stck[--sp]);
		return stck[--sp];
		}
	else
	{
	printf("error: stack empty\n");
	return 0.0;
	}

}

int getint(int *pn)
{
	int c,sign

	while(isspace(c=getch()))
	;
	if(!isdigit(c) && c!=EOF && c!='+' && c!='-')
	{
	ungetch(c);
	return 0;
	}
	sign = (c=='-')?-1:1;
	if(c=='+' || c=='-')
		c=getch();
	for(*pn=0;isdigit(c);c=getch())
		*pn=10 * *pn+(c-'0');
		*pn *=sign;
		if(c!=EOF)
			ungetch(c);
		return c;
}

int getch(void)
{
return (bufp>0)?buf[--bufp]:getchar();

}

void ungetch(int c)
{
if(bufp>=BUFSIZE)
	printf("ungetch:too many characters\n");
else
	buf[bufp++]=c;
}
