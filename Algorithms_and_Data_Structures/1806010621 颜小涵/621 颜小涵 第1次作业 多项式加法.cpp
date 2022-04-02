#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node *PNode;
typedef struct Node *List;
struct Node{
	int idx;
	int exp;
	PNode next;
}; //���������� 

//���������� 
List createList(int no){//noΪ��ǰ����ʽ�ı�� 
	int m ,i;
	int idx, exp;
	List l;
	PNode s,r;
	
	printf("�������%d������ʽ��������", no);
	scanf("%d", &m);
	
	l = (List)malloc(sizeof(Node));
	r = l;
	for(i = 0; i < m; i++){
		printf("�������%d���ϵ����ָ��:", (i+1));
		scanf("%d %d", &idx, &exp);
		
		s = (PNode)malloc(sizeof(Node));
		s->idx = idx;
		s->exp = exp;
		r->next = s;
		r = s;
	}//���������� 
	r->next=NULL;
	
	return l;
}

//������Ľڵ���� 
int ListLength(List L){
	int cnt = 0;
	PNode p = L->next;
	
	while(p->next != NULL){
		cnt++;
		p = p->next;
	}
	return cnt;
}

//�������������нڵ� 
void printList(List L){
	printf("�ö���ʽΪ:\n");
	int i = 0, j = ListLength(L);
	PNode p = L->next;
	
	while(p != NULL){
		printf("%dx^%d", p->idx, p->exp);
		i++;
		if(i <= j) printf("+");
		p = p->next;
	}
	printf("\n");
	printf("\n");
}

//������ӷ� 
List addList(PNode L1, PNode L2){
	PNode L, s, r;
	L1 = L1->next;
	L2 = L2->next;
	L = (PNode)malloc(sizeof(Node));
	r = L;
	
	while (L1 != NULL && L2 != NULL){
		if (L1->exp > L2->exp){//L1��ָ������L2��ָ�� 
			s = (PNode)malloc(sizeof(Node));
			s->idx = L1->idx;
			s->exp = L1->exp;
			r->next = s;
			r = s;
			L1 = L1->next;
		}
		else if (L1->exp == L2->exp){//ָ����ͬ 
			s = (PNode)malloc(sizeof(Node));
			s->idx = L1->idx + L2->idx;
			s->exp = L1->exp;
			if (s->idx == 0) free(s);
			else{
				r->next = s;
				r = s;
			}
			L1 = L1->next;
			L2 = L2->next;
		}
		else{//L1��ָ��С��L2��ָ�� 
			s = (PNode)malloc(sizeof(Node));
			s->idx = L2->idx;
			s->exp = L2->exp;
			r->next = s;
			r = s;
			L2 = L2->next;
		}
	}
	if (L1 != NULL)r->next = L1;
	else if (L2 != NULL)r->next = L2;
	else r->next = NULL;
	return L;
}

int main(){
	List l1, l2, l;
	l1 = (List)malloc(sizeof(Node));
	l1 = createList(1);
	printList(l1);//����һ����������� 
	
	l2 = (List)malloc(sizeof(Node));
	l2 = createList(2);
	printList(l2);
	
	printf("�ӷ����õ��Ķ���ʽΪ��\n"); 
	l = (List)malloc(sizeof(Node)); 
	l = addList(l1, l2);
	printList(l); 
	return 0;
}
