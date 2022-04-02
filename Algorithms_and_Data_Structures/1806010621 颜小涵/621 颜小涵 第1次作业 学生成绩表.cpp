#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define mNum 10

struct DataType{
	char *name;
	double score;
};//Ϊ˳���������������� 
struct SeqList{
	int MAXNUM;//����С 
	DataType *element;
	int n;//ʵ������ 
}; 
typedef struct SeqList *PSeqList;

//�����յ�˳���
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

//���±�λ��Ϊp��˳������ݸ��� 
int update_seq (PSeqList palist,int p,DataType x){
	if(p < 0 || p > palist->n){
		printf("Not exist!\n");
		return 0;
	}//�쳣�ж� 
	
	palist->element[p]=x;
	return 1;
} 

//��˳���ָ��λ��֮ǰ�������� 
int insertPre_seq (PSeqList palist, int p, DataType x){
	int q;
	if(palist->n >= palist->MAXNUM){
		printf("Overflow!\n");
		return 0;
	}
	if(p < -1 || p > palist->n){
		printf("Not exist!\n");
		return 0;
	}//�쳣�ж� 
	
	for(q = palist -> n-1; q >= p; q--)
		palist -> element[q+1] = palist->element[q];
	palist->element[p] = x;
	palist->n = palist->n+1;
	return 1;
} 

//ɾ��˳���ָ��λ�õ����� 
int delete_seq (PSeqList palist,int p){
	int q;
	if(p < 0 || p > palist->n-1){
		printf("Not exist\n");
		return 0;
	}//�쳣�ж� 
	
	for(q = p; q < palist->n-1; q++)
		palist->element[q] = palist->element[q+1];
	palist->n = palist->n-1;
	return 1;
} 

//�������˳��� 
int printSeqList(PSeqList palist){
	if(palist->n == 0){
		printf("���ݱ�Ϊ�գ�\n");
		return 0;
	}//�쳣�ж� 
	
	int i;
	printf("���ݱ���%d������\n", palist->n);
	for(i=0; i < palist->n; i++){
		printf("| %d    |   %s   |   %lf   |\n", palist->n, palist->element[i].name, palist->element[i].score);
	}
	printf("\n");
	return 1;
}

//ÿ�ֲ����ĳ�ʼ������ 
int initPrint(){
	int i, ch;
	
	for(i = 0; i < mNum; i++)printf("-");
	printf("ѧ���ɼ�����ϵͳ");
	for(i = 0; i < mNum; i++)printf("-");
	printf("\n");
	
	printf("1: ����˳���ָ��λ�õ�����\n");
	printf("2: ��˳���ָ��λ��ǰ��������\n");
	printf("3: ɾ��˳���ָ��λ�õ�����\n");
	printf("4: ���˳����ȫ������\n");
	printf("5: �˳�ѧ���ɼ�����ϵͳ\n");
	printf("\n");
	
	printf("����1-5��ѡ�����蹦�ܲ�����ȷ�ϣ�");
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
		isRunningΪϵͳ�Ƿ�����ı�־
		optΪÿ�ֵĲ�������
		posΪÿ�β�������Ӧ���±�λ�� ���û��������
		score name x�ֱ�Ϊѧ���ɼ� ѧ������ ��ѧ��������������ʱ���� ���û��������
		StudentΪ˳��� 
	*/
	
	while(isRunning){
		opt = initPrint();	//ÿ�ֵĲ��� 
		switch (opt){
			case 1:
				printf("������������������±꣬ѧ���ĳɼ�������:");
				scanf("%d%lf%s", &pos, &score, &name);
				x.score = score;
				x.name = name;//����������ʼ�� 
				
				if(update_seq(Student, pos, x)) printf("�滻�ɹ�!\n");
				else printf("�滻ʧ��!\n"); 
				
				break;
			case 2:
				printf("�����������������±꣬ѧ���ĳɼ�������:");
				scanf("%d%lf%s", &pos, &score, &name);
				x.score = score;
				x.name = name;//���������ʼ�� 
				
				if(insertPre_seq(Student, pos, x)) printf("����ɹ�!\n");
				else printf("����ʧ��!\n"); 
				
				break;
			case 3:
				printf("��������ɾ�����±꣺");
				scanf("%d", &pos);//ɾ��������ʼ�� 
				
				if(delete_seq(Student, pos)) printf("ɾ���ɹ�!\n");
				else printf("ɾ��ʧ��!\n");
				 
				break;
			case 4:
				if(printSeqList(Student)) printf("����ɹ�!\n");
				else printf("���ʧ��!\n"); 
				
				break;
			case 5:
				printf("�ڴ������´�ʹ��!\n");
				isRunning=0;//�˳����� 
				
				break;
			default:
				printf("ָ���ʽ����!\n");
		}
		printf("\n");//�����ֲ����ָ����� 
	}
	return 0;	
}
