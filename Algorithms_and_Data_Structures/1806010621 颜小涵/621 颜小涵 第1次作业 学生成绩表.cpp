#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define mNum 10

struct DataType{
	char *name;
	double score;
};//为顺序表定义基本数据类型 
struct SeqList{
	int MAXNUM;//表单大小 
	DataType *element;
	int n;//实际数量 
}; 
typedef struct SeqList *PSeqList;

//创建空的顺序表
PSeqList createNullList_seq (int m){ 
	PSeqList palist;
	palist = (PSeqList)malloc(sizeof(struct SeqList));
	
	if(palist != NULL){
		palist->element = (DataType*)malloc(sizeof(DataType)*m);
		if (palist->element){
			palist->MAXNUM = m;
			palist->n = 0;
			return (palist);
		}
		else free(palist);
	}
	
	return NULL;
}

//将下标位置为p的顺序表数据更新 
int update_seq (PSeqList palist,int p,DataType x){
	if(p < 0 || p > palist->n){
		printf("Not exist!\n");
		return 0;
	}//异常判断 
	
	palist->element[p]=x;
	return 1;
} 

//在顺序表指定位置之前插入数据 
int insertPre_seq (PSeqList palist, int p, DataType x){
	int q;
	if(palist->n >= palist->MAXNUM){
		printf("Overflow!\n");
		return 0;
	}
	if(p < -1 || p > palist->n){
		printf("Not exist!\n");
		return 0;
	}//异常判断 
	
	for(q = palist -> n-1; q >= p; q--)
		palist -> element[q+1] = palist->element[q];
	palist->element[p] = x;
	palist->n = palist->n+1;
	return 1;
} 

//删除顺序表指定位置的数据 
int delete_seq (PSeqList palist,int p){
	int q;
	if(p < 0 || p > palist->n-1){
		printf("Not exist\n");
		return 0;
	}//异常判断 
	
	for(q = p; q < palist->n-1; q++)
		palist->element[q] = palist->element[q+1];
	palist->n = palist->n-1;
	return 1;
} 

//输出整个顺序表 
int printSeqList(PSeqList palist){
	if(palist->n == 0){
		printf("数据表为空！\n");
		return 0;
	}//异常判断 
	
	int i;
	printf("数据表共有%d个数据\n", palist->n);
	for(i=0; i < palist->n; i++){
		printf("| %d    |   %s   |   %lf   |\n", palist->n, palist->element[i].name, palist->element[i].score);
	}
	printf("\n");
	return 1;
}

//每轮操作的初始化处理 
int initPrint(){
	int i, ch;
	
	for(i = 0; i < mNum; i++)printf("-");
	printf("学生成绩管理系统");
	for(i = 0; i < mNum; i++)printf("-");
	printf("\n");
	
	printf("1: 更新顺序表指定位置的数据\n");
	printf("2: 向顺序表指定位置前插入数据\n");
	printf("3: 删除顺序表指定位置的数据\n");
	printf("4: 输出顺序表的全部数据\n");
	printf("5: 退出学生成绩管理系统\n");
	printf("\n");
	
	printf("输入1-5，选择所需功能并进行确认：");
	printf("\n");
	scanf("%d", &ch);
	return ch; 
}

int main(){
	int isRunning = 1 , opt, pos; 
	double score;
	char *name;
	DataType x; 
	PSeqList Student = createNullList_seq(MAXSIZE);
	/*
		isRunning为系统是否结束的标志
		opt为每轮的操作种类
		pos为每次操作所对应的下标位置 由用户输入而来
		score name x分别为学生成绩 学生姓名 和学生这个数据类的临时变量 由用户输入而来
		Student为顺序表 
	*/
	
	while(isRunning){
		opt = initPrint();	//每轮的操作 
		switch (opt){
			case 1:
				printf("请依次输入想更换的下标，学生的成绩和姓名:");
				scanf("%d%lf%s", &pos, &score, &name);
				x.score = score;
				x.name = name;//更换操作初始化 
				
				if(update_seq(Student, pos, x)) printf("替换成功!\n");
				else printf("替换失败!\n"); 
				
				break;
			case 2:
				printf("请依次输入想插入的下标，学生的成绩和姓名:");
				scanf("%d%lf%s", &pos, &score, &name);
				x.score = score;
				x.name = name;//插入操作初始化 
				
				if(insertPre_seq(Student, pos, x)) printf("插入成功!\n");
				else printf("插入失败!\n"); 
				
				break;
			case 3:
				printf("请输入想删除的下标：");
				scanf("%d", &pos);//删除操作初始化 
				
				if(delete_seq(Student, pos)) printf("删除成功!\n");
				else printf("删除失败!\n");
				 
				break;
			case 4:
				if(printSeqList(Student)) printf("输出成功!\n");
				else printf("输出失败!\n"); 
				
				break;
			case 5:
				printf("期待您的下次使用!\n");
				isRunning=0;//退出操作 
				
				break;
			default:
				printf("指令格式错误!\n");
		}
		printf("\n");//与下轮操作分隔开来 
	}
	return 0;	
}
