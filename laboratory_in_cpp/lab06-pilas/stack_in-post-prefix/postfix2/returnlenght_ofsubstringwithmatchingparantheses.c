#include "stackc.h"

int main(){
    stack_t stk;
    init_stk(&stk);
    char str[100];
    scanf("%s",str);
    int percount=0;
    int tempcount=0;
    for(int i=0;i<sizeof(str);i++){
        if(str[i]=='(') {push(&stk,str[i]);}
        if(str[i]==')') {
            tempcount=0;
            if(str[i]==')'){ 
            while(pop(&stk)!=-1)
                i++;
                tempcount+=2;
            }}
            percount+=tempcount;
    }
    printf("The length is %d",percount);



}