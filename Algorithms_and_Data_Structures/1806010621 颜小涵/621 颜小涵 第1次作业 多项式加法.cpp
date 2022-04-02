#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node *PNode;
typedef struct Node *List;
struct Node{
	int idx;
	int exp;
	PNode next;
}; //创建单链表 

//创建单链表 
List createList(int no){//no为当前多项式的标号 
	int m ,i;
	int idx, exp;
	List l;
	PNode s,r;
	
	printf("请输入第%d个多项式的项数：", no);
	scanf("%d", &m);
	
	l = (List)malloc(sizeof(Node));
	r = l;
	for(i = 0; i < m; i++){
		printf("请输入第%d项的系数和指数:", (i+1));
		scanf("%d %d", &idx, &exp);
		
		s = (PNode)malloc(sizeof(Node));
		s->idx = idx;
		s->exp = exp;
		r->next = s;
		r = s;
	}//创建单链表 
	r->next=NULL;
	
	return l;
}

//求单链表的节点个数 
int ListLength(List L){
	int cnt = 0;
	PNode p = L->next;
	
	while(p->next != NULL){
		cnt++;
		p = p->next;
	}
	return cnt;
}

//输出单链表的所有节点 
void printList(List L){
	printf("该多项式为:\n");
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

//单链表加法 
List addList(PNode L1, PNode L2){
	PNode L, s, r;
	L1 = L1->next;
	L2 = L2->next;
	L = (PNode)malloc(sizeof(Node));
	r = L;
	
	while (L1 != NULL && L2 != NULL){
		if (L1->exp > L2->exp){//L1的指数大于L2的指数 
			s = (PNode)malloc(sizeof(Node));
			s->idx = L1->idx;
			s->exp = L1->exp;
			r->next = s;
			r = s;
			L1 = L1->next;
		}
		else if (L1->exp == L2->exp){//指数相同 
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
		else{//L1的指数小于L2的指数 
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
	printList(l1);//输入一个单链表并输出 
	
	l2 = (List)malloc(sizeof(Node));
	l2 = createList(2);
	printList(l2);
	
	printf("加法最后得到的多项式为：\n"); 
	l = (List)malloc(sizeof(Node)); 
	l = addList(l1, l2);
	printList(l); 
	return 0;
}
