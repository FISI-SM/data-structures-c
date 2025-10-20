//program to convert a valid infix expression to prefix
#include<stdio.h>
#include<string.h>
#define BLANK ' '
#define TAB '\t'
int white_space_clear(char ch)
{
    if (ch == BLANK || ch == TAB || ch == '\0')
        return 1;
    else
        return 0;
}

int input_prec(char);
int stack_prec(char);
char peep(char *,int);
void convert_prefix(char*,char*);
void push(char *, int *, char);
char pop(char *, int *);
char* reverse(char*);
int eval_pre(char* eval,char *prefix,int *top);

int main()
{
  char infix[100],postfix[100];
  int n;
  scanf("%d",&n);
  scanf("%s",infix);
  char* reverse_;
  reverse_=reverse(infix);

  convert_prefix(reverse_,postfix);
  char* prefix=reverse(postfix);
  int eval[100];int tope=-1;
  int result=eval_pre(eval,prefix,&tope);
  printf("%s %d\n",prefix,result);
  return 0;
}

void convert_prefix(char* infix,char* postfix)
{
	int i,j;
	char ch;
	char s[100];//stack
	int top=-1;
	i=0;
	j=0;
	push(s,&top,'#'); //push # to stack
	while(infix[i]!='\0')
	{
		if(!white_space_clear(ch)){ 
		ch=infix[i];
		while(stack_prec(peep(s,top)) > input_prec(ch))
		          postfix[j++]=pop(s,&top);
		if(input_prec(ch)>stack_prec(peep(s,top)))
				    push(s,&top,ch);
		else
			  pop(s,&top); //for parenthesis
		  i++;
	}
	}
	while(peep(s,top)!='#')	
        postfix[j++]=pop(s,&top);		
	
	postfix[j]='\0';
}	 
			
	int stack_prec(char ch)
	{
		switch(ch)
		{
			case '+':
			case '-':return 1;
			case '*':
			case'/':return 3;
			case'^':return 6;
			case '(':return 0;
			case '#':return -1;
			default:return 8;
		}
	}
	
	int input_prec(char ch)
	{
		switch(ch)
		{
			case '+':
			case '-':return 2;
			case '*':
			case'/':return 4;
			case'^':return 5;
			case '(':return 9;
			case ')':return 0;
			default:return 7;
		}
	}
	
	char peep(char *s ,int top)
	{
		return s[top];
	}
	
		void push(char *s, int *top, char ch)
		{
			(*top)++; //or ++*top
			s[*top]=ch;
		}
		
		
		
     char pop(char *s, int *top)
	 {
		 char x;
		 x=s[*top];
		 --*top; //or (*top)--;
		 return x;
	 }

char* reverse(char * str) {  
    // declare variable  
    int i, len, temp;  
    len = strlen(str); // use strlen() to get the length of str string  
      
    // use for loop to iterate the string   
    for (i = 0; i < len/2; i++)  
    {  
        // temp variable use to temporary hold the string  
        temp = str[i];  
        str[i] = str[len - i - 1];  
        str[len - i - 1] = temp;  
    }  
    return str;
}  

int eval_pre(char* eval,char *prefix,int *top)
{
        int a,b,temp,result;
        int i;

        for(i=strlen(prefix)-1;i>=0;i--)
        {
                if(prefix[i]<='9' && prefix[i]>='0')
                        push(eval,top,prefix[i]-48 );
                else
                {
                        b=pop(eval,top);
                        a=pop(eval,top);
                        switch(prefix[i])
                        {
                        case '+':
                                temp=b+a; break;
                        case '-':
                                temp=b-a;break;
                        case '*':
                                temp=b*a;break;
                        case '/':
                                temp=b/a;break;
                        case '%':
                                temp=b%a;break;
                        case '^':
                                temp=pow(b,a);
                        }
                        push(eval,top,temp);
                }
        }
        result=pop(eval,top);
        return result;
}
		 
		 
		 
		
	
	
	
	
	
	
	

