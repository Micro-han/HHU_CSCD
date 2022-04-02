#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

struct SeqString{
    int MAXNUM;
    int n;
    char *c;
};
typedef SeqString *PSeqString;//�����ַ���

//�������ַ���
PSeqString createNullStr_seq(int m){
    PSeqString pstr = (PSeqString)malloc(sizeof(PSeqString));
    if(pstr!=NULL){
        pstr->c = (char *)malloc(sizeof(char) * m);
        if (pstr->c){
            pstr->n = 0;
            pstr->MAXNUM = m;
            return pstr;
        }
        else free(pstr);
    }
    printf("Out of space!\n");
    return NULL;
}

//�����ַ���
PSeqString createStr_seq(PSeqString pstr){
    char ch;
    while((ch = getchar()) != '\n'){
        pstr->c[pstr->n] = ch;
        pstr->n++;
    }
    return pstr;
}

//��ʼ���ַ���
PSeqString init(){
    printf("��������ַ�����\n");
    PSeqString pstr = (PSeqString)malloc(sizeof(PSeqString));
    pstr = createNullStr_seq(MAXSIZE);
    pstr = createStr_seq(pstr);
    return pstr;
}

//Ѱ��������Ӵ�
void findStr(PSeqString s1, PSeqString s2){
    int i, j, k;//ѭ�����Ʊ���
    int ans = 0;//������Ӵ��ĳ���
    char *ansStr;//������Ӵ�
    for(i = 0; i < s1->n; i++){
        for(j = 0; j < s2->n; j++){
            if(s1->c[i] == s2->c[j]){
                int st1 = i, st2 = j, cnt = 1;
                while (s1->c[st1] == s2->c[st2]){
                    st1++;
                    st2++;
                    cnt++;
                }//Ѱ��������ͬ���Ӵ�
                if( cnt > ans){//�ȵ�ǰ�Ĺ����Ӵ��� ���´�
                    for(k = 0; k < cnt; k++)
                        ansStr[k] = s1->c[i+k];
                    ans = cnt;
                }
            }
        }
    }
    for(k = 0; k < ans; k++) printf("%c", ansStr[k]);
    printf("\n");
}

int main(){
    PSeqString s1, s2, s;
    s1 = (PSeqString)malloc(sizeof(PSeqString));
    s1=init();//��һ���ַ���
    
    s2 = (PSeqString)malloc(sizeof(PSeqString));
    s2=init();//�ڶ����ַ���
    
    printf("������Ӵ�Ϊ��");
    findStr(s1, s2);
    return 0;
}
