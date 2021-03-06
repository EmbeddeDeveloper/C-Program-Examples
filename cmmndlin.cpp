#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUMBER 'n'
#define STACKVALUE 100

int getop(const char *s);
void push(double value);
double pop(void);

static double stack[STACKVALUE];
static double *pStack = stack; /* next free position in stack */

int main(int argc, char *argv[])
{
	 double tmpOp;
	 char c;

	 if(argc >3) {

		  while(--argc) {
				c = getop(*++argv);
				switch(c) {
					 case NUMBER:
						  push(atof(*argv));
						  break;
					 case '+':
						  push(pop() + pop());
						  break;
					 case '-':
						  tmpOp = pop();
						  push(pop() - tmpOp);
						  break;
					 case '*':
						  push(pop() * pop());
                    break;
                case '\\':
                    tmpOp = pop();

                    if(!tmpOp) {
								printf("error: can't divide by 0\n");
                    }
                    else {
								push(pop()/tmpOp);
                    }
                    break;
                default:
                    printf("error: invalid expression %s\n", *argv);
            }
        }
		  printf("%g\n", pop());
	 }
    else {
		  printf("invalid call\n");
    }

	 return 0;
}

static int isNumber(const char *s) {
    int i = 0;

    if(isdigit(s[i])) {
        for(; isdigit(s[i]); i++)
            ;
    }

    if(s[i] == '.') {
        i++;
        for(; isdigit(s[i]); i++)
            ;
    }

    if(s[i] == 'e' || s[i] == 'E') {
        i++;
        for(; isdigit(s[i]); i++)
            ;
    }

    if(s[i] != '\0') {
        return 0;
    }
    return 1;
}


int getop(const char *op) {
    int i;

	 if(!isdigit(op[0]) && op[0] != '.') {
		  return op[0];
    }

    i = 0;

    /* support for negative number */
	 if(op[0] == '-' && !isdigit(op[1])) {
        return op[0];
    }
    else {
        i++;
    }
    if(isNumber(op + i)) {
        return NUMBER;
    }

    return op[0];
}


void push(double value) {
	 if(pStack - stack > STACKVALUE) {
        printf("error: there is not enough psace in stack");
    }
    else {
       *(pStack++) = value;
    }
}

double pop(void) {
	 if((pStack - stack) > 0) {
        return *--pStack;
    }

	 printf("warning: the stack is free");
	 return 0.0;
}
