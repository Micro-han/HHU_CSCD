#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

struct SeqString{
    int MAXNUM;
    int n;
    char *c;
};
typedef SeqString *PSeqString;//定义字符串

//创建空字符串
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

//创建字符串
PSeqString createStr_seq(PSeqString pstr){
    char ch;
    while((ch = getchar()) != '\n'){
        pstr->c[pstr->n] = ch;
        pstr->n++;
    }
    return pstr;
}

//初始化字符串
PSeqString init(){
    printf("请输入该字符串：\n");
    PSeqString pstr = (PSeqString)malloc(sizeof(PSeqString));
    pstr = createNullStr_seq(MAXSIZE);
    pstr = createStr_seq(pstr);
    return pstr;
}

//寻找最长公共子串
void findStr(PSeqString s1, PSeqString s2){
    int i, j, k;//循环控制变量
    int ans = 0;//最长公共子串的长度
    char *ansStr;//最长公共子串
    for(i = 0; i < s1->n; i++){
        for(j = 0; j < s2->n; j++){
            if(s1->c[i] == s2->c[j]){
                int st1 = i, st2 = j, cnt = 1;
                while (s1->c[st1] == s2->c[st2]){
                    st1++;
                    st2++;
                    cnt++;
                }//寻找两串相同的子串
                if( cnt > ans){//比当前的公共子串长 更新答案
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
    s1=init();//第一个字符串
    
    s2 = (PSeqString)malloc(sizeof(PSeqString));
    s2=init();//第二个字符串
    
    printf("最长公共子串为：");
    findStr(s1, s2);
    return 0;
}
