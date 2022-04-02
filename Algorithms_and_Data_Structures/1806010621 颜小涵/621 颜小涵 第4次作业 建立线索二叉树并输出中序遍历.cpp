#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100//��������������
/*
 ���⣺
 ����n�����Ķ��������� ���������� ������������
 */

struct ThrBinTreeNode;
typedef ThrBinTreeNode *PThrBinTreeNode;
typedef ThrBinTreeNode *ThrBinTree;
struct ThrBinTreeNode{
    char data;
    int ltag, rtag;
    PThrBinTreeNode llink, rlink;
};
typedef ThrBinTree *PThrBinTree;//�����������������ݽṹ

ThrBinTree root;//������������
int n,a[MAXSIZE];//������ �� �����Ϣ

//��������½��
PThrBinTreeNode getFirst(PThrBinTreeNode p){
    while(p->ltag == 0)
        p = p->llink;
    return p;
}

//�ҵ��������
PThrBinTreeNode getNext(PThrBinTreeNode p){
    if(p->rtag == 0)
        return getFirst(p->rlink);
    return p->rlink;
}

//�������
void inOrder(ThrBinTree root){
    PThrBinTreeNode p;
    for(p = getFirst(root); p != NULL ; p = getNext(p))
        printf("%d ",p->data);
    printf("\n");
}

//��������������
void buildBinTree(int m){
    ThrBinTree now, aft;
    if(root == NULL){//��һ�����
        root = new ThrBinTreeNode;
        root->data = m;
        root->llink = NULL;
        root->rlink = NULL;
    }
    else{
        now=root;
        while(m != now->data){
            if((m < now->data) && (now->llink != NULL))
                now = now->llink;
            else if((m > now->data) && (now->rlink != NULL))
                now = now->rlink;
            else if((m < now->data) && (now->llink == NULL)){//�ҵ�һ����������������Ϊ�յĵ�
                aft = new ThrBinTreeNode;
                aft->data = m;
                aft->llink = NULL;
                aft->rlink = NULL;
                now->llink = aft;
                return;
            }else if((m > now->data) && (now->rlink == NULL)){//�ҵ�һ������С��������Ϊ�յĵ�
                aft = new ThrBinTreeNode;
                aft->data = m;
                aft->llink = NULL;
                aft->rlink = NULL;
                now->rlink = aft;
                return;
            }
        }
    }
}

//�������������������
void InThreading(ThrBinTree p, PThrBinTreeNode &pre){
    if(p != NULL){
        InThreading(p->llink, pre);//������������
        if(p->llink == NULL){//������ǰ����ǰ������
            p->llink = pre;
            p->ltag = 1;
        }
        if(pre != NULL && pre->rlink == NULL){//������ǰ���ĺ������
            pre->rlink = p;
            pre->rtag = 1;
        }
        pre = p;
        InThreading(p->rlink, pre);//������������
    }
}

//��������������
void createThrBinTree(){
    int i;
    //��������������
    for(i = 0; i < n; i++)
        buildBinTree(a[i]);
    //����������������
    PThrBinTreeNode pre = NULL;//ǰ�����ָ��
    if(root != NULL){
        InThreading(root, pre);
        pre->rlink = NULL;
        pre->rtag = 1;//�������һ�����
    }
}

int main(){
    //��ʼ������
    int i;
    printf("������������\n");
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    //����ģ��
    createThrBinTree();
    //�������
    printf("������������\n");
    inOrder(root);
    return 0;
}

