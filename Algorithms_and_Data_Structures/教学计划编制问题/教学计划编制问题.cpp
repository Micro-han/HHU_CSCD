#include <stdio.h>
#include <vector>
#include <map>
#include <stack>
#include <iostream>

using namespace std;

struct DataType{
    char name[30];//课程名称
    int val;//学分
};
vector < DataType > G[1010];//动态数组G
map < string, int> mp;//映射 表示课程号为string的是结点i
int terms, grades_up, edges, nodes;//学期总数 学期最多学分 变数 点数

//根据读入创建图表
void init_creategraph(){
    int i;
    char s[30];
    DataType data;
    //初始化信息
    printf("\t\t\t欢迎使用教学计划编制系统\n");
    printf("请输入学期总数：");
    scanf("%d", &terms);
    printf("请输入学期学分上限：");
    scanf("%d", &grades_up);
    printf("请输入教学计划的课程数：");
    scanf("%d", &nodes);
    printf("请输入各个课程的先修课程数：");
    scanf("%d", &edges);
    printf("请输入%d个课程的课程号\n", nodes);
    
    for(i = 1; i <= nodes; i++){
        printf("请输入第%d个：", i);
        scanf("%s", data.name);
        G[i].push_back(data);//将课程data的信息放入到动态数组G[i][0]中
        mp[G[i][0].name] = i;//课程号为data.name的是第i个课程
    }
    printf("请输入%d个课程的学分：", nodes);
    for(i = 1; i <= nodes; i++) scanf("%d", &G[i][0].val);
    printf("请输入下列课程的先修课程（以#为结束标志）:\n");

    for(i = 1; i <= nodes; i++){
        printf("%s的先修课程为：" , G[i][0].name);
        scanf("%s", s);
        while(s[0] != '#'){
            G[i].push_back(G[mp[s]][0]);//G[i][j]表示课程i是课程j的先决课程
            scanf("%s", s);
        }
    }
    
    printf("\t\t\t录入数据成功！\n");
}

//展示存储的图表信息
void showgraph(){
    int i, j;
    printf("该图为有向图\n");
    printf("%d个顶点\n", nodes);
    for(i = 1 ; i <= nodes; i++) printf("%s ", G[i][0].name);
    printf("\n");
    printf("%d条边\n", edges);
    for(i = 1 ; i <= nodes; i++)
        for(j = 0 ; j < G[i].size(); j++)
            printf("%s------->%s\n", G[i][0].name, G[i][j].name);
}

int ans[1010], cnt = 0, indegee[1010];
//ans最终为拓扑序 indegee为入度表 cnt为答案结点个数
//拓扑排序
void topusort(){
    int i, j;
    memset(indegee, 0, sizeof(indegee));//初始化indegee数组
    for(i = 1; i <= nodes; i++)
        for(j = 1; j < G[i].size(); j++)
            indegee[mp[G[i][j].name]]++;//统计入度为0的点
    memset(ans, 0, sizeof(ans));//初始化ans数组
    stack<int> s;//栈s
    for(i = 1 ; i <= nodes; i++)
        if(indegee[i] == 0) s.push(i);//将入度为0的点放入栈中
    while( !s.empty()){
        int cur = s.top();s.pop();//取栈顶
        ans[cnt++ ] = cur;
        for(j = 1; j < G[cur].size(); j++){//删除以cur为首的边
            int num = mp[G[cur][j].name];
            indegee[num]--;
            if(indegee[num] == 0)s.push(num);//将新的入度为0的点放入栈中
        }
    }
}

//平均分配课程
void solve1(int ans[]){
    int q = 1, cnt = 0;
    //q为第q个学期 cnt为拓扑序已经学到了第cnt个课程
    while(q <= terms){
        int num = nodes / terms;
        printf("第%d个学期应学课程：\n", q);
        while(num--)
            printf("%s ",G[ans[cnt++]][0].name);
        printf("\n");
        q++;
    }
}

//靠前分配课程
void solve2(int ans[]){
    int q = 1, cnt = 0;
    //q为第q个学期 cnt为拓扑序已经学到了第cnt个课程
    while(q <= terms){
        int tot = G[ans[cnt]][0].val;//tot表示这个学期学的总学分数
        printf("第%d个学期应学课程：", q);
        //尽可能在一个学期内多学课程
        while(cnt < nodes && tot <= grades_up){
            printf("%s ",G[ans[cnt]][0].name);
            if(cnt + 1 < nodes)tot = tot + G[ans[cnt + 1]][0].val;
            cnt ++;
        }
        printf("\n");
        //学满了
        if(cnt >= nodes || q == terms){
            printf("\n");
            break;
        }
        q++;
    }
}
//主程序
int main(){
    init_creategraph();
    showgraph();
    topusort();
    if (cnt != nodes)puts("发生错误！\n");//无法学完所有课程
    else{
        int isRunning = 1;//判断系统是否运行
        puts("成功！\n");
        while(isRunning){
            //每轮操作初始化
            printf("\t\t\t请选择功能：\n");
            printf("\t\t\t1.平均分配\n");
            printf("\t\t\t2.靠前分配\n");
            printf("\t\t\t3.退出\n");
            int opt;
            printf("请输入操作数：");
            scanf("%d", &opt);
            switch(opt){
                case 1:
                    solve1(ans);//平均分配
                    break;
                case 2:
                    solve2(ans);//考前分配
                    break;
                case 3:
                    printf("感谢使用!\n");
                    isRunning = 0;
                    break;
                default:
                    printf("指令错误");
            }
        }
    }
    return 0;
}
/*

 6
 10
 12
 16
 c1
 c2
 c3
 c4
 c5
 c6
 c7
 c8
 c9
 c10
 c11
 c12
 2 3 4 3 2 3 4 4 7 5 2 3
 #
 c1 #
 c1 c2 #
 c1 #
 c3 #
 c11 #
 c5 c3 #
 c3 c6 #
 #
 c9 #
 c9 #
 c9 c10 c1 #

 */