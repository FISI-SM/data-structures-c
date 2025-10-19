#include"stackc.h"

//function to initiliaze the stack

void init_stk(stack_t *ptr_st)
{
	printf("Enter the size of the stack");
	scanf("%d",&ptr_st->size);
	ptr_st->top=-1;
	
	ptr_st->s= (char*)malloc(sizeof(char)*ptr_st->size);
}

void push(stack_t * ptr_st, char key)
{
	//check for stack overflow
	if(ptr_st->top==ptr_st->size-1)
		printf("\nStack full..cannot insert element");
	else
	{
        if(key=='('){
            ++ptr_st->top;
		ptr_st->s[ptr_st->top]=key;}	
	}
}

void display(stack_t* ptr_st)
	 {
		int i;
		if(ptr_st->top==-1)
			printf("Stack empty..");
		else
		{
           for(i=ptr_st->top; i>=0;i--)
              printf("%c    ", ptr_st->s[i]);
		}
	 }		

int pop(stack_t *ptr_st)
    {
		int k;
		//check for stack empty
		if(ptr_st->top==-1)  
		{
			// printf("Empty stack..");
			return -1;
		}
		k=ptr_st->s[ptr_st->top];//copy the top element into k
		ptr_st->top--;
		return k;
	}

int checkstacks(stack_t* one,stack_t* two){

	struct node* top1 = one->top;
	struct node* top2 = two->top;
	while((top1!=NULL) && (top2!=NULL)){
		if(top1->data != top2->data) return 0;
		top1 = top1->link;
		top2 = top2->link;
	}
	if((top1 == NULL) && (top2==NULL)) return 1;
	else return 0;
}


void reversequ(queue *ptrq){
	if(ptrq->capacity == 0) return ptrq;
	else{
		int data = ptrq->q[ptrq->front];
		deleteQ(Queue *ptrq);
		reversequ(ptrq);
		insertQ(Queue * ptrq , data);
		return ptrq;
	}
}
		
		
			
		
		


	
		 
		 
		 
		
		
		
		
		
		
		
	
	
	
	
	
	
	