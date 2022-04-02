#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100//二叉树最多结点个数
/*
 题意：
 给出n个结点的二叉排序树 将其线索化 并求出中序遍历
 */

struct ThrBinTreeNode;
typedef ThrBinTreeNode *PThrBinTreeNode;
typedef ThrBinTreeNode *ThrBinTree;
struct ThrBinTreeNode{
    char data;
    int ltag, rtag;
    PThrBinTreeNode llink, rlink;
};
typedef ThrBinTree *PThrBinTree;//建立线索二叉树数据结构

ThrBinTree root;//线索二叉树根
int n,a[MAXSIZE];//结点个数 及 结点信息

//求出最左下结点
PThrBinTreeNode getFirst(PThrBinTreeNode p){
    while(p->ltag == 0)
        p = p->llink;
    return p;
}

//找到后继线索
PThrBinTreeNode getNext(PThrBinTreeNode p){
    if(p->rtag == 0)
        return getFirst(p->rlink);
    return p->rlink;
}

//中序遍历
void inOrder(ThrBinTree root){
    PThrBinTreeNode p;
    for(p = getFirst(root); p != NULL ; p = getNext(p))
        printf("%d ",p->data);
    printf("\n");
}

//建立二叉排序树
void buildBinTree(int m){
    ThrBinTree now, aft;
    if(root == NULL){//第一个结点
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
            else if((m < now->data) && (now->llink == NULL)){//找到一个比他大且左子树为空的点
                aft = new ThrBinTreeNode;
                aft->data = m;
                aft->llink = NULL;
                aft->rlink = NULL;
                now->llink = aft;
                return;
            }else if((m > now->data) && (now->rlink == NULL)){//找到一个比他小且右子树为空的点
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

//中序遍历线索化二叉树
void InThreading(ThrBinTree p, PThrBinTreeNode &pre){
    if(p != NULL){
        InThreading(p->llink, pre);//左子树线索化
        if(p->llink == NULL){//建立当前结点的前驱线索
            p->llink = pre;
            p->ltag = 1;
        }
        if(pre != NULL && pre->rlink == NULL){//建立当前结点的后继线索
            pre->rlink = p;
            pre->rtag = 1;
        }
        pre = p;
        InThreading(p->rlink, pre);//右子树线索化
    }
}

//创建线索二叉树
void createThrBinTree(){
    int i;
    //建立二叉排序树
    for(i = 0; i < n; i++)
        buildBinTree(a[i]);
    //二叉排序树线索化
    PThrBinTreeNode pre = NULL;//前驱结点指针
    if(root != NULL){
        InThreading(root, pre);
        pre->rlink = NULL;
        pre->rtag = 1;//处理最后一个结点
    }
}

int main(){
    //初始化部分
    int i;
    printf("输入结点数量：\n");
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    //核心模块
    createThrBinTree();
    //输出部分
    printf("中序遍历输出：\n");
    inOrder(root);
    return 0;
}

