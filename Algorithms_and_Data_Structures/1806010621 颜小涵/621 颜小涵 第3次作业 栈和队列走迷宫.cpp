#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

int MAXNUM = 20*20;//ջ���������
int N = 15;//�Թ��ĳ� ��

struct DataType{
    int x, y;
};//����������� x,y��ʾ����

struct SeqStack{
    int top;
    DataType *s;
};
typedef struct SeqStack *PSeqStack;//����ջ�����ݽṹ

int dis[4][2]={ {1,0}, {0,1}, {-1,0}, {0,-1} };
char fx[4]={'D', 'R', 'U', 'L'};
//���� ���� ���� �����ĸ���ͬ����
int vis[15][15];//ÿ�����Ƿ��Ѿ��߹�
int mp_init[15][15];//��ͼ���� 
int mp[15][15] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};//�����Թ���ͼ
//�Թ� 0 �������ͨ�� 1������ͨ�� 2������� 3�����յ�

//������ջ
PSeqStack createEmptyStack_seq(){
    PSeqStack pstack = (PSeqStack)malloc(sizeof(PSeqStack));
    if(pstack != NULL){
        pstack->s = (DataType*)malloc(sizeof(DataType) * MAXNUM);
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
void push_seq(PSeqStack pstack, DataType x){
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

//Ѱ�������յ�
void findPos(DataType &st, DataType &ed){
    int i, j;//ѭ�����Ʊ���
    int cnt = 0;//�ж��Ƿ��Ѿ��ҵ����������
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(mp[i][j] == 2){
                st.x = i;
                st.y = j;
                cnt++;
            }
            if(mp[i][j] == 3){
                ed.x = i;
                ed.y = j;
                cnt++;
            }
            if(cnt == 2) return ;
        }
    }
}

//����ջ�ҵ���·��
void findPath_stack(PSeqStack pstack, DataType st, DataType ed){
    push_seq(pstack, st);
    DataType pointNow,pointTmp;
    int i, cnt = 4, flag = 0;
    //i ѭ�����Ʊ��� flag�Ƿ��յ� cnt������
    while(isEmptyStack_seq(pstack) == 0){
        pointNow = pstack->s[pstack->top];
        pop_seq(pstack);
        if(mp[pointNow.x][pointNow.y] == 0) mp[pointNow.x][pointNow.y] = cnt;//�����ǰ���Ѿ��ߵ� ��ô��ֵ 
        for(i = 0; i < 4; i++){
            pointTmp.x = pointNow.x + dis[i][0];
            pointTmp.y = pointNow.y + dis[i][1];//�ߵ�һ���µ� 
            if(pointTmp.x < 0 || pointTmp.y < 0 || pointTmp.x > N-1 || pointTmp.y > N-1)continue;//������ͼ�߽�
            if(mp[pointTmp.x][pointTmp.y] == 1)continue;//1������
            if(vis[pointTmp.x][pointTmp.y] == 1)continue;//�õ��Ѿ��߹�
            if(mp[pointTmp.x][pointTmp.y] == 3){
                flag = 1;
                break;
            }
            vis[pointTmp.x][pointTmp.y] = 1;
            push_seq(pstack, pointTmp);
            cnt++;//�ظ��ݹ�
        }
        if(flag) break;
    }
}

//����ջ�����·�� 
void printPath_stack(PSeqStack pstack, DataType st, DataType ed){
    DataType pointTmp, pointNow = st;
    char *ans = (char *)malloc(sizeof(char)*MAXNUM);//��·��
    int m = mp[pointNow.x][pointNow.y] , i, j, flag = 0, pos = -1, cnt = 0;
    //i jѭ�����Ʊ��� posΪ�ò�ѡ��ķ���
    while(mp[pointNow.x][pointNow.y] != 3){
        for(i = 0 ; i < 4; i++){
            pointTmp.x = pointNow.x + dis[i][0];
            pointTmp.y = pointNow.y + dis[i][1];//�γ��µ� 
            if(pointTmp.x < 0 || pointTmp.y > N-1 || pointTmp.x > N-1 || pointTmp.y < 0) continue;//������ͼ�߽�
            if(mp[pointTmp.x][pointTmp.y] == 1)continue;//1������
            if(mp[pointTmp.x][pointTmp.y] == 3){//���յ�
                flag = 1;
                break;
            }
            if(mp[pointTmp.x][pointTmp.y] > m) {//��ǰΪ��·���ϵĵ�
                m = mp[pointTmp.x][pointTmp.y];
                pos = i;
                ans[cnt] = fx[i];
            }
        }
        //�ظ�ѭ��
        pointNow.x = pointNow.x + dis[pos][0];
        pointNow.y = pointNow.y + dis[pos][1];
        mp[pointNow.x][pointNow.y] = -1;
        cnt++;
        m = 3;
        if(flag)break;
    }
    //�����
    printf("�𰸵�ͼΪ��\n");
    for(i = 0; i < N ; i++){
        for(j = 0; j < N; j++)
            if(mp[i][j] == -1) printf("- ");
            else if(mp[i][j] > 3) printf("0 ");
            else printf("%d ",mp[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("��·��Ϊ��\n%s\n", ans);
}

//���ö����ҵ���·��
void findPath_queue(DataType st, DataType ed){
    std::queue <DataType> pointqueue;//������
    std::queue <int> countqueue;//�ȼ�Ȩֵ����
    int flag = 3, Count = 1,count = 0 , i, j = 0;
    //i Ϊѭ�����Ʊ��� CountΪһ�ι��ͬ��������� jΪ�����˳�����
    //countΪÿ���������·���ķ������
    DataType nowP, tmpP;
    //nowP��ǰ�� tmpP���Ե��½ڵ�
    pointqueue.push(st);
    vis[st.x][st.y] = 1;//��ʼ��
    
    while (!pointqueue.empty()){//�жϽ������Ƿ�Ϊ��
        nowP = pointqueue.front();//ȡ����
        pointqueue.pop();//����
        if(Count < 1 && !countqueue.empty()){//�ж�Ȩֵ�����Ƿ�Ϊ��
            Count = countqueue.front();//ȡ����
            countqueue.pop();//����
        }
        if(Count == 0)continue;
        Count--;

        mp[nowP.x][nowP.y] = flag;//���߹� ��ΪȨֵ
        for(i = 0; i < 4; i++){//�ĸ�������
            tmpP.x = nowP.x + dis[i][0];
            tmpP.y = nowP.y + dis[i][1];//�γ��µ� 
            if(tmpP.x < 0 || tmpP.y < 0 || tmpP.x > N-1 || tmpP.y > N-1)continue;//������ͼ�߽�
            if(mp[tmpP.x][tmpP.y] == 1)continue;//Ϊ1������
            if(vis[tmpP.x][tmpP.y] == 1)continue;//�Ѿ��߹�
            if(mp[tmpP.x][tmpP.y] == 3){//�����յ�
                j = 1;
                break;
            }
            vis[tmpP.x][tmpP.y] = 1;//��¼�ɵ���ĵ�
            pointqueue.push(tmpP);//���
            count++;
        }
        if( j )break;//ѭ���˳� 
        if(Count < 1){
            countqueue.push(count);//���
            flag++;
            count = 0;
        }
    }
}

//���ö������·�� 
void printPath_queue(DataType st, DataType ed){
    DataType tmp, now;//nowΪ��ǰ��� tmpΪ���ԵĽ��
    int i, val, j, cnt = 1;
    char *ans;//������
    ans = (char *)malloc(sizeof(char) * MAXNUM);
    now = ed;//���յ㷴��
    val = mp[ed.x][ed.y];
    //��һ������
    for(i = 0 ; i < 4; i++){
        tmp.x = now.x + dis[i][0];
        tmp.y = now.y + dis[i][1];//�γ��µ� 
        if(tmp.x < 0 || tmp.y < 0 || tmp.x > N-1 || tmp.y > N-1)continue;
        if(mp[tmp.x][tmp.y] > val){
            val = mp[tmp.x][tmp.y];
            mp[tmp.x][tmp.y] = -1;
            ans[0] = fx[i];
            now = tmp;
            break;
        }
    }
    //�ظ����� ֱ�����
    //���յ���ǰ����
    while (now.x != st.x || now.y != st.y){
        for(i = 0 ; i < 4 ; i++){
            tmp.x = now.x + dis[i][0];
            tmp.y = now.y + dis[i][1];
            if(mp[tmp.x][tmp.y] == val - 1){
                mp[tmp.x][tmp.y] = -1;//���ϸ��²���
                now = tmp;
                ans[cnt++] = fx[i];
                val--;
                break;
            }
        }
    }
    //���
    printf("�Թ���ͼΪ��\n");
    for(i = 0 ;i < N ; i++){
        for (j = 0 ; j <  N; j++)
            if(mp[i][j] == -1)printf("- ");
            else if(mp[i][j] > 3)printf("0 ");
            else printf("%d ",mp[i][j]);
        printf("\n");
    }
    //��Ϊ�Ƿ��� ����Ҫ������������ �ҷ���Ի�
    std::reverse(ans, ans+cnt);//����
    for(i = 0; i < cnt; i++){
        if(ans[i] == 'L') ans[i] = 'R';
        else if(ans[i] == 'U') ans[i] = 'D';
        else if(ans[i] == 'D') ans[i] = 'U';
        else if(ans[i] == 'R') ans[i] = 'L';//����Ի�
        else ans[i] = '\0';
    }
    
    printf("������Ϊ:\n");
    printf("%s\n",ans);
}
//�����ͼ
void printMap(){
    int i, j;
    printf("ԭ�Թ�Ϊ��\n");
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        	printf("%d ", mp[i][j]);
        	mp_init[i][j] = mp[i][j];//���ݵ�ͼ�������� 
        	vis[i][j] = 0;//��ʼ��vis���� 
        }
        printf("\n");
    }
    printf("\n");
}
//���õ�ͼ 
void renewMap(){
	int i, j;
	for(i = 0 ; i < N; i++)
		for( j = 0 ; j < N; j++) mp[i][j] = mp_init[i][j];
}

int main(){
    //��ʼ������
    DataType st, ed;
    findPos(st, ed);
    PSeqStack s;
    s = createEmptyStack_seq();
    //����ջ����
    printMap();
    printf("ջ��Ӧ�ù������£�\n");
	printf("\n"); 
    findPath_stack(s, st, ed);
    printPath_stack(s, st, ed);
     
    renewMap();
    //���ö��д��� 
	printMap();
	printf("���е�Ӧ�ù������£�\n");
    printf("\n");
    findPath_queue(st, ed);
    printPath_queue(st, ed);
    return 0;
}
/*
    
 */

