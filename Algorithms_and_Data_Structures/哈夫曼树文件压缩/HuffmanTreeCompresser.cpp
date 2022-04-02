#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mNum 10
#define MAXSIZE 256
#define INF 0xffffffffUL
#define Length 255

typedef unsigned char uc;
typedef unsigned long ul;
typedef unsigned int ui;
typedef unsigned u;
//Ԥ���峣�����ͺͳ��� ��������

struct HuffNode{
    uc ch;//8�����޷����ַ�
    ul val;//�ַ����ֵ�Ƶ��
    char *code;//����������
    int father,lchild,rchild;//���� ���Ҷ���
};
typedef struct HuffNode *PHuffNode;
typedef struct HuffNode *HuffTree;//���������������ݽṹ

char inputName[MAXSIZE],outputName[MAXSIZE];//�����ļ��������ļ���

int init(){//ÿ�ֲ����ĳ�ʼ��
    int i, m;
    for(i = 0; i < mNum; i++)printf("-");
    printf("��������Ҫ���еĲ���");
    for(i = 0; i < mNum; i++)printf("-");
    printf("\n");
 	   
    printf("1: ѹ��ָ���ļ�\n");
    printf("2: ��ѹָ���ļ�\n");
    printf("3: �˳�ϵͳ\n");
    printf("��������Ҫѡ��Ĳ�������\n");
    
    scanf("%d", &m);//��������
    return m;
}

void initflush(){//��ʼ�� ��������ļ����������ļ���
    printf("����������ļ�����:\n");
    fflush(stdin);
    gets(inputName);
    printf("����������ļ�����:\n");
    fflush(stdin);
    gets(outputName);
}

void checkFile(int flag){//���ѹ���ļ����߽�ѹ���������޴�����
    if( flag == -1)
        printf("�����ļ�%s������\n",inputName);
    else printf("�����ɹ�\n");
}

//Ѱ����С�ʹ�С���������
void findTwoMinNode(HuffTree tree, ui n, int *s1, int *s2){
    ui i;
    ul minValue = INF;
    for(i = 0; i < n; i++)
        if(tree[i].father == 0 && tree[i].val < minValue){
            minValue = tree[i].val;
            *s1 =i;
        }
    tree[*s1].father = 1;//ѡ�� �»ز���ѡ��
    minValue = INF;
    for(i = 0; i < n; i++)
        if(tree[i].father == 0 && tree[i].val < minValue){
            minValue = tree[i].val;
            *s2 = i;
        }
}

//���ɹ�������
void createTree(HuffTree tree, ui chNum, ui nodeNum){
    ui i;
    int s1, s2;
    for(i = chNum; i < nodeNum; i++){//ÿ��Ѱ��Ƶ����С�ʹ�С�������� ����һ��
        findTwoMinNode(tree, i, &s1, &s2);
        tree[s1].father = i;
        tree[s2].father = i;
        tree[i].lchild = s1;
        tree[i].rchild = s2;
        tree[i].val = tree[s1].val + tree[s2].val;
    }
}

//���ɹ���������
void HuffCode(HuffTree tree, u chNum){
    ui i;
    int cur,next,idx;
    char *filetmp = (char *)malloc(sizeof(char) * (Length + 1));//���볤�Ȳ�����255
    filetmp[Length]='\0';
    for(i = 0; i < chNum; i++){
        idx = Length;
        //��Ҷ������������ �������
        cur = i;	
        next=tree[i].father;
        while(next != 0){
            if(tree[next].lchild == cur) filetmp[--idx] = '0';
            else filetmp[--idx] = '1';//��0��1
            cur = next;
            next = tree[next].father;
        }
        tree[i].code = (char *)malloc(sizeof(char) * (Length + 1 - idx));
        strcpy(tree[i].code, &filetmp[idx]);//������뵽����������
    }
    free(filetmp);//�ͷ���ʱ�ռ�
}

//ѹ������
int compress(char *inName, char *outName){
    ui i, j;//ѭ�����Ʊ���
    ui chNum;//�ַ�����
    ul fileLen = 0, aftLen = 0;
    uc chTmp;
    FILE *infile, *outfile, *in2file;
    HuffNode nodeTmp;
    ui nodeNum;
    HuffTree tree;
    HuffTree treeTmp;
    char code_buf[Length + 1] = "\0";//������뻺����
    ui code_len;
    
    //��ʼ��
    treeTmp = (HuffTree)malloc(sizeof(HuffNode) * (Length + 1));
    for(i = 0; i <= Length; i++){
        treeTmp[i].val = 0;
        treeTmp[i].ch = (uc) i;
    }
    
    //�����ļ� ��ȡ�ַ�Ƶ��
    infile = fopen(inName, "rb");
    if(infile == NULL) return -1;
    fread((char *) &chTmp, sizeof(uc), 1, infile);
    while(! feof(infile)){
        treeTmp[chTmp].val++;
        fileLen++;
        fread((char *) &chTmp, sizeof(uc), 1, infile);
    }
    fclose(infile);
    
    //ѡ������ �޳�Ƶ��Ϊ0���ַ�
    for(i = 0; i < Length; i++)
        for(j = i + 1; j <= Length; j++)
            if(treeTmp[i].val < treeTmp[j].val){
                nodeTmp = treeTmp[i];
                treeTmp[i] = treeTmp[j];
                treeTmp[j] = nodeTmp;
            }
    //ͳ��ʵ���ַ����� 
    for(i = 0; i <= Length; i++)
        if(treeTmp[i].val == 0) break;
    chNum = i;
    
    if(chNum == 1){//�������
        outfile = fopen(outName, "wb");
        fwrite((char *) &chNum, sizeof(ui), 1, outfile);
        fwrite((char *) &treeTmp[0].ch, sizeof(uc), 1, outfile);
        fwrite((char *) &treeTmp[0].val, sizeof(ul), 1, outfile);
        free(treeTmp);
        fclose(outfile);
    }else {
        nodeNum = 2 * chNum - 1;//�����������������
        tree = (HuffTree)malloc(sizeof(HuffNode) * nodeNum);
        
        //����������ʼ��
        for(i = 0; i < chNum; i++){
            tree[i].ch = treeTmp[i].ch;
            tree[i].val = treeTmp[i].val;
            tree[i].father = 0;
        }
        free(treeTmp);
        for(i = chNum; i < nodeNum; i++)
            tree[i].father = 0;
        //������������
        createTree(tree, chNum, nodeNum);
        //���ɹ���������
        HuffCode(tree, chNum);
        
        //д���ַ�����ӦȨ��
        outfile = fopen(outName, "wb");
        fwrite((char *) &chNum, sizeof(ui), 1, outfile);//д���ַ�����
        for(i = 0; i < chNum; i++){
            fwrite((char *) &tree[i].ch, sizeof(uc), 1, outfile);//д���ַ�
            fwrite((char *) &tree[i].val, sizeof(ul), 1, outfile);//д���ַ�Ȩ��
        }
        fwrite((char *) &fileLen, sizeof(ul), 1, outfile);//д���ļ�����
        
        //�Զ�������ʽ�򿪴�ѹ���ļ�
        infile = fopen(inName, "rb");
        fread((char *) &chTmp, sizeof(uc), 1, infile);
        while(!feof(infile)){
            //ƥ�����
            for(i = 0; i < chNum; i++)
                if(chTmp == tree[i].ch)
                    strcat(code_buf, tree[i].code);
            //ÿ����8���ض�Ӧ�ַ� ƥ�����
            ul buf_len = strlen(code_buf);
            while(buf_len >= 8){
                chTmp = '\0';
                for(i = 0; i < 8; i++){
                    chTmp <<= 1;//����һλ Ϊ��һ�������ڳ��ռ�
                    if(code_buf[i] == '1') chTmp |= 1;
                }
                fwrite((char *) &chTmp, sizeof(uc), 1, outfile);//�ֽڶ�Ӧ����д���ļ�
                strcpy(code_buf, code_buf+8);
                buf_len = strlen(code_buf);
            }
            fread((char *) &chTmp, sizeof(uc), 1, infile);//��������
        }
        //���������8���صĲ���
        code_len = strlen(code_buf);
        if(code_len > 0){
            chTmp = '\0';	
            for(i = 0; i < code_len; i++){
                chTmp <<= 1;
                if(code_buf[i] == '1') chTmp |= 1;
            }
            chTmp <<= 8 - code_len;
            fwrite((char *) &chTmp, sizeof(uc), 1, outfile);
        }
        //�ر��ļ� �ͷ��ڴ�
        fclose(infile);
        fclose(outfile);
        for(i = 0 ; i < chNum; i++) free(tree[i].code);
        free(tree);
    }
    
    //ͳ��ѹ�����ļ����ֽ��� 
    in2file = fopen(outName, "rb");
    fread((char *) &chTmp, sizeof(uc), 1, in2file);
    while(! feof(in2file)){
        aftLen++;
        fread((char *) &chTmp, sizeof(uc), 1, in2file);
    }
    fclose(in2file);
    printf("ԭ�ļ�����%d�ֽ���\n", fileLen);
    printf("ѹ�����ļ�����%d�ֽ���\n", aftLen);
    printf("ѹ��ǰ���Ϊ%.2lf\n", 1.0 * fileLen / aftLen); 
    return 1;
}

//��ѹ������
int extract(char *inName, char *outName){
    ui i;
    ul fileLen;
    ul writeLen = 0;//�����ļ�д�볤��
    FILE *infile, *outfile;
    ui chNum;//�洢�ַ�����
    ui nodeNum;
    HuffTree tree;
    uc chTmp;
    ui root;//�Ը����Ϊ���� ƥ�����
    
    infile = fopen(inName, "rb");
    if(infile == NULL) return -1;//����
    
    //��ȡ�ļ��ַ��������
    fread((char *) &chNum, sizeof(ui), 1, infile);//��ȡ�ַ���
    if(chNum == 1){//�������
        fread((char *) &chTmp, sizeof(uc), 1, infile);
        fread((char *) &fileLen, sizeof(ul), 1,infile);
        outfile = fopen(outName, "wb");
        while(fileLen--)
            fwrite((char *) &chTmp, sizeof(uc), 1, outfile);
        fclose(infile);
        fclose(outfile);
    } else {
        nodeNum = 2 * chNum - 1;
        tree = (HuffTree)malloc(sizeof(HuffNode) * nodeNum);
        //��ȡ�ַ���Ȩ�� ����������ڵ�
        for(i = 0; i < chNum; i++){
            fread((char *) &tree[i].ch, sizeof(uc), 1, infile);
            fread((char *) &tree[i].val, sizeof(ul), 1, infile);
            tree[i].father = 0;
        }
        for(i = chNum; i < nodeNum; i++)tree[i].father = 0;
        //������������
        createTree(tree, chNum, nodeNum);
        //��ȡ�ļ����Ⱥͱ��� ���н���
        fread((char *) &fileLen, sizeof(ul), 1, infile);
        outfile = fopen(outName, "wb");
        root = nodeNum - 1;
        while(true){
            fread((char *) &chTmp, sizeof(uc), 1, infile);
            //�����ȡ��һ���ַ����ȵı���
            for(i = 0; i < 8 ; i++){
                //�ɸ��ڵ���Ҷ�ڵ�����ƥ��
                if(chTmp & 128)
                    root = tree[root].rchild;
                else
                    root = tree[root].lchild;
                if(root < chNum){
                    fwrite((char *) &tree[root].ch, sizeof(uc), 1, outfile);
                    writeLen++;
                    if(writeLen == fileLen) break;//ѭ����ֹ
                    root = nodeNum - 1;//ƥ����һ���ַ�
                }
                chTmp <<= 1;//��һλ�ƶ������ ��ƥ��
            }
            if(writeLen == fileLen)break;//ѭ����ֹ
        }
        //�ر��ļ� �ͷ��ڴ�
        fclose(infile);
        fclose(outfile);
        free(tree);
    }
    return  1;
}

int main(){
    int isRunning = 1, opt, flag;//flagΪ�����ɹ�����жϱ�־
    while (isRunning) {//isRunning�ж�ϵͳ�Ƿ�����
        opt = init();//��������
        switch (opt) {
            case 1:
                initflush();
                printf("ѹ���С���\n");
                flag = compress(inputName, outputName);
                checkFile(flag);
                break;
            case 2:
                initflush();
                printf("��ѹ�С���\n");
                flag = extract(inputName, outputName);
                checkFile(flag);
                break;
            case 3:
                isRunning = 0;
                printf("ллʹ��\n");
                break;
            default:
                printf("ָ�����\n");
                break;
        }
        printf("\n");
    }
    return 0;
}

