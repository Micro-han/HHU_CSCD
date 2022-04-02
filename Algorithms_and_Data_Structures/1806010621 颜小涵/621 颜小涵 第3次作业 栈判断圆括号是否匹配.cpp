#include<stdio.h>
#include<stdlib.h>

int MAXNUM = 200;//栈的最大容量

struct SeqStack{
    int top;
    char *s;
};
typedef struct SeqStack *PSeqStack;//定义栈的数据结构

//创建空栈
PSeqStack createEmptyStack_seq(){
    PSeqStack pstack = (PSeqStack)malloc(sizeof(PSeqStack));
    if(pstack != NULL){
        pstack->s = (char*)malloc(sizeof(char)*MAXNUM);
        if(pstack->s){
            pstack->top = -1;
            return pstack;
        }
        else free(pstack);
    }
    printf("Out of space!\n");
    return NULL;
}

//进栈
void push_seq(PSeqStack pstack, int x){
    if(pstack->top == MAXNUM - 1)printf("Overflow!\n");
    else{
        pstack->top = pstack->top+1;
        pstack->s[pstack->top] = x;
    }
}

//弹出栈顶
void pop_seq(PSeqStack pstack){
    if(pstack->top == -1)printf("Underflow!\n");
    else pstack->top = pstack->top-1;
}

//判断栈是否为空
int isEmptyStack_seq(PSeqStack pstack){
    if(pstack->top == -1)return 1;
    return 0;
}

int main(){
    char c;
    PSeqStack pstack = createEmptyStack_seq();
    int x = 0, flag = 1;
    
    printf("请输入括号序列：\n");
    while((c = getchar()) != '\n'){
        if(c == '(')
            push_seq(pstack,x);
        else {
            if(isEmptyStack_seq(pstack))//右括号比左括号多 说明右括号不匹配
                flag = 0;
            else
                pop_seq(pstack);
        }
        x=0;
    }
    if(flag == 1){
        if( isEmptyStack_seq(pstack) == 0) flag =2;
    }//判断栈是否为空 如果不为空说明左括号有剩余
    
    if(flag == 2) printf("左括号不匹配!\n");
    else if(flag == 0) printf("右括号不匹配!\n");
    else printf("括号序列匹配!\n");
    return 0;
}

