#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

int MAXNUM = 20*20;//栈的最大容量
int N = 15;//迷宫的长 宽

struct DataType{
    int x, y;
};//结点数据类型 x,y表示坐标

struct SeqStack{
    int top;
    DataType *s;
};
typedef struct SeqStack *PSeqStack;//定义栈的数据结构

int dis[4][2]={ {1,0}, {0,1}, {-1,0}, {0,-1} };
char fx[4]={'D', 'R', 'U', 'L'};
//向下 向右 向上 向左四个不同方向
int vis[15][15];//每个点是否已经走过
int mp_init[15][15];//地图备份 
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
};//定义迷宫地图
//迷宫 0 代表可以通过 1代表不可通过 2代表起点 3代表终点

//创建空栈
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

//进栈
void push_seq(PSeqStack pstack, DataType x){
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

//寻找起点和终点
void findPos(DataType &st, DataType &ed){
    int i, j;//循环控制变量
    int cnt = 0;//判断是否已经找到两个所需点
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

//利用栈找到答案路径
void findPath_stack(PSeqStack pstack, DataType st, DataType ed){
    push_seq(pstack, st);
    DataType pointNow,pointTmp;
    int i, cnt = 4, flag = 0;
    //i 循环控制变量 flag是否到终点 cnt计数器
    while(isEmptyStack_seq(pstack) == 0){
        pointNow = pstack->s[pstack->top];
        pop_seq(pstack);
        if(mp[pointNow.x][pointNow.y] == 0) mp[pointNow.x][pointNow.y] = cnt;//如果当前点已经走到 那么赋值 
        for(i = 0; i < 4; i++){
            pointTmp.x = pointNow.x + dis[i][0];
            pointTmp.y = pointNow.y + dis[i][1];//走到一个新点 
            if(pointTmp.x < 0 || pointTmp.y < 0 || pointTmp.x > N-1 || pointTmp.y > N-1)continue;//超出地图边界
            if(mp[pointTmp.x][pointTmp.y] == 1)continue;//1不可走
            if(vis[pointTmp.x][pointTmp.y] == 1)continue;//该点已经走过
            if(mp[pointTmp.x][pointTmp.y] == 3){
                flag = 1;
                break;
            }
            vis[pointTmp.x][pointTmp.y] = 1;
            push_seq(pstack, pointTmp);
            cnt++;//重复递归
        }
        if(flag) break;
    }
}

//利用栈来输出路径 
void printPath_stack(PSeqStack pstack, DataType st, DataType ed){
    DataType pointTmp, pointNow = st;
    char *ans = (char *)malloc(sizeof(char)*MAXNUM);//答案路径
    int m = mp[pointNow.x][pointNow.y] , i, j, flag = 0, pos = -1, cnt = 0;
    //i j循环控制变量 pos为该步选择的方向
    while(mp[pointNow.x][pointNow.y] != 3){
        for(i = 0 ; i < 4; i++){
            pointTmp.x = pointNow.x + dis[i][0];
            pointTmp.y = pointNow.y + dis[i][1];//形成新点 
            if(pointTmp.x < 0 || pointTmp.y > N-1 || pointTmp.x > N-1 || pointTmp.y < 0) continue;//超出地图边界
            if(mp[pointTmp.x][pointTmp.y] == 1)continue;//1不可走
            if(mp[pointTmp.x][pointTmp.y] == 3){//到终点
                flag = 1;
                break;
            }
            if(mp[pointTmp.x][pointTmp.y] > m) {//当前为答案路径上的点
                m = mp[pointTmp.x][pointTmp.y];
                pos = i;
                ans[cnt] = fx[i];
            }
        }
        //重复循环
        pointNow.x = pointNow.x + dis[pos][0];
        pointNow.y = pointNow.y + dis[pos][1];
        mp[pointNow.x][pointNow.y] = -1;
        cnt++;
        m = 3;
        if(flag)break;
    }
    //输出答案
    printf("答案地图为：\n");
    for(i = 0; i < N ; i++){
        for(j = 0; j < N; j++)
            if(mp[i][j] == -1) printf("- ");
            else if(mp[i][j] > 3) printf("0 ");
            else printf("%d ",mp[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("答案路径为：\n%s\n", ans);
}

//利用队列找到答案路径
void findPath_queue(DataType st, DataType ed){
    std::queue <DataType> pointqueue;//结点队列
    std::queue <int> countqueue;//等级权值队列
    int flag = 3, Count = 1,count = 0 , i, j = 0;
    //i 为循环控制变量 Count为一次广度同级别结点个数 j为搜索退出变量
    //count为每个坐标点有路径的方向个数
    DataType nowP, tmpP;
    //nowP当前点 tmpP尝试的新节点
    pointqueue.push(st);
    vis[st.x][st.y] = 1;//初始化
    
    while (!pointqueue.empty()){//判断结点队列是否为空
        nowP = pointqueue.front();//取队首
        pointqueue.pop();//弹出
        if(Count < 1 && !countqueue.empty()){//判断权值队列是否为空
            Count = countqueue.front();//取队首
            countqueue.pop();//弹出
        }
        if(Count == 0)continue;
        Count--;

        mp[nowP.x][nowP.y] = flag;//已走过 设为权值
        for(i = 0; i < 4; i++){//四个方向尝试
            tmpP.x = nowP.x + dis[i][0];
            tmpP.y = nowP.y + dis[i][1];//形成新点 
            if(tmpP.x < 0 || tmpP.y < 0 || tmpP.x > N-1 || tmpP.y > N-1)continue;//超出地图边界
            if(mp[tmpP.x][tmpP.y] == 1)continue;//为1不能走
            if(vis[tmpP.x][tmpP.y] == 1)continue;//已经走过
            if(mp[tmpP.x][tmpP.y] == 3){//到达终点
                j = 1;
                break;
            }
            vis[tmpP.x][tmpP.y] = 1;//记录可到达的点
            pointqueue.push(tmpP);//入队
            count++;
        }
        if( j )break;//循环退出 
        if(Count < 1){
            countqueue.push(count);//入队
            flag++;
            count = 0;
        }
    }
}

//利用队列输出路径 
void printPath_queue(DataType st, DataType ed){
    DataType tmp, now;//now为当前结点 tmp为尝试的结点
    int i, val, j, cnt = 1;
    char *ans;//答案序列
    ans = (char *)malloc(sizeof(char) * MAXNUM);
    now = ed;//从终点反推
    val = mp[ed.x][ed.y];
    //第一步特判
    for(i = 0 ; i < 4; i++){
        tmp.x = now.x + dis[i][0];
        tmp.y = now.y + dis[i][1];//形成新点 
        if(tmp.x < 0 || tmp.y < 0 || tmp.x > N-1 || tmp.y > N-1)continue;
        if(mp[tmp.x][tmp.y] > val){
            val = mp[tmp.x][tmp.y];
            mp[tmp.x][tmp.y] = -1;
            ans[0] = fx[i];
            now = tmp;
            break;
        }
    }
    //重复操作 直到起点
    //从终点往前反推
    while (now.x != st.x || now.y != st.y){
        for(i = 0 ; i < 4 ; i++){
            tmp.x = now.x + dis[i][0];
            tmp.y = now.y + dis[i][1];
            if(mp[tmp.x][tmp.y] == val - 1){
                mp[tmp.x][tmp.y] = -1;//不断更新操作
                now = tmp;
                ans[cnt++] = fx[i];
                val--;
                break;
            }
        }
    }
    //输出
    printf("迷宫地图为：\n");
    for(i = 0 ;i < N ; i++){
        for (j = 0 ; j <  N; j++)
            if(mp[i][j] == -1)printf("- ");
            else if(mp[i][j] > 3)printf("0 ");
            else printf("%d ",mp[i][j]);
        printf("\n");
    }
    //因为是反推 所以要将答案序列逆置 且方向对换
    std::reverse(ans, ans+cnt);//逆置
    for(i = 0; i < cnt; i++){
        if(ans[i] == 'L') ans[i] = 'R';
        else if(ans[i] == 'U') ans[i] = 'D';
        else if(ans[i] == 'D') ans[i] = 'U';
        else if(ans[i] == 'R') ans[i] = 'L';//方向对换
        else ans[i] = '\0';
    }
    
    printf("答案序列为:\n");
    printf("%s\n",ans);
}
//输出地图
void printMap(){
    int i, j;
    printf("原迷宫为：\n");
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        	printf("%d ", mp[i][j]);
        	mp_init[i][j] = mp[i][j];//备份地图方便重置 
        	vis[i][j] = 0;//初始化vis数组 
        }
        printf("\n");
    }
    printf("\n");
}
//重置地图 
void renewMap(){
	int i, j;
	for(i = 0 ; i < N; i++)
		for( j = 0 ; j < N; j++) mp[i][j] = mp_init[i][j];
}

int main(){
    //初始化部分
    DataType st, ed;
    findPos(st, ed);
    PSeqStack s;
    s = createEmptyStack_seq();
    //利用栈处理
    printMap();
    printf("栈的应用过程如下：\n");
	printf("\n"); 
    findPath_stack(s, st, ed);
    printPath_stack(s, st, ed);
     
    renewMap();
    //利用队列处理 
	printMap();
	printf("队列的应用过程如下：\n");
    printf("\n");
    findPath_queue(st, ed);
    printPath_queue(st, ed);
    return 0;
}
/*
    
 */

