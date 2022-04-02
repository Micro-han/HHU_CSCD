#include<stdio.h>
#include<stdlib.h>

int MAXNUM = 200;//ջ���������

struct SeqStack{
    int top;
    char *s;
};
typedef struct SeqStack *PSeqStack;//����ջ�����ݽṹ

//������ջ
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

//��ջ
void push_seq(PSeqStack pstack, int x){
    if(pstack->top == MAXNUM - 1)printf("Overflow!\n");
    else{
        pstack->top = pstack->top+1;
        pstack->s[pstack->top] = x;
    }
}

//����ջ��
void pop_seq(PSeqStack pstack){
    if(pstack->top == -1)printf("Underflow!\n");
    else pstack->top = pstack->top-1;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmptyStack_seq(PSeqStack pstack){
    if(pstack->top == -1)return 1;
    return 0;
}

int main(){
    char c;
    PSeqStack pstack = createEmptyStack_seq();
    int x = 0, flag = 1;
    
    printf("�������������У�\n");
    while((c = getchar()) != '\n'){
        if(c == '(')
            push_seq(pstack,x);
        else {
            if(isEmptyStack_seq(pstack))//�����ű������Ŷ� ˵�������Ų�ƥ��
                flag = 0;
            else
                pop_seq(pstack);
        }
        x=0;
    }
    if(flag == 1){
        if( isEmptyStack_seq(pstack) == 0) flag =2;
    }//�ж�ջ�Ƿ�Ϊ�� �����Ϊ��˵����������ʣ��
    
    if(flag == 2) printf("�����Ų�ƥ��!\n");
    else if(flag == 0) printf("�����Ų�ƥ��!\n");
    else printf("��������ƥ��!\n");
    return 0;
}

