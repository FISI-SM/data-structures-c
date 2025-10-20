//another version of stack
#include<stdio.h>
#include<stdlib.h>
void push(int*,int*,int,int);
int pop(int*,int*);
void display(int*,int);
int main()
{
  int top,size,ch,k,key;
  int *st;
  printf("Enter the size of the stack..\n");
  scanf("%d",&size);
  st=(int*)malloc(sizeof(int)*size);
  top=-1;
  while(1)
  {
    display(st,top);
    printf("\n1..push\n");
    printf("2..pop\n");
    printf("3..display\n");
    scanf("%d",&ch);
    switch(ch)
    {                                
    case 1:printf("Enter the data\n");
             scanf("%d",&key);
             push(st,&top,size,key);
             break;
     case 2:k=pop(st,&top);
            if(k>0)
               printf("\nElement popped=%d\n",k);
            break;
     case 3:display(st,top);
            break;
     case 4:exit(0);
   }
 }
}
 
   void push(int *st, int *t, int size, int key)
   {
	   if(*t==size-1)    
		   printf("\nStack full..\n");
	   else
	   {
		   (*t)++;  // ++*t   or *t=*t+1
		   st[*t]=key;
	   }
   }
		   
	int pop(int *st, int *t)
    {
		  int key;
		  
         if(*t==-1)    
		 {
		   printf("\nStack empty..\n");
	       return -1;
		 }
		 key = st[*t];
		 (*t )--;// or --*t , *t=*t-1
		 return key;
	}

		
	void display(int *st, int t)
	{
		int i;
		if(t==-1)
				printf("Empty stack.\n");
		else
		{
			for(i=t;i>=0;i--)
				printf("%d ",st[i]);
		}
	}
			
			
		
	
		   
 











   
 


  



   

    






   

   
