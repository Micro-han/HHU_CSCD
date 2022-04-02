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
//预定义常用类型和常数 美化代码

struct HuffNode{
    uc ch;//8比特无符号字符
    ul val;//字符出现的频次
    char *code;//哈夫曼编码
    int father,lchild,rchild;//父亲 左右儿子
};
typedef struct HuffNode *PHuffNode;
typedef struct HuffNode *HuffTree;//创建哈夫曼树数据结构

char inputName[MAXSIZE],outputName[MAXSIZE];//读入文件和生成文件名

int init(){//每轮操作的初始化
    int i, m;
    for(i = 0; i < mNum; i++)printf("-");
    printf("请输入你要进行的操作");
    for(i = 0; i < mNum; i++)printf("-");
    printf("\n");
 	   
    printf("1: 压缩指定文件\n");
    printf("2: 解压指定文件\n");
    printf("3: 退出系统\n");
    printf("请输入你要选择的操作数：\n");
    
    scanf("%d", &m);//操作种类
    return m;
}

void initflush(){//初始化 读入读入文件名和生成文件名
    printf("请输入读入文件名称:\n");
    fflush(stdin);
    gets(inputName);
    printf("请输入输出文件名称:\n");
    fflush(stdin);
    gets(outputName);
}

void checkFile(int flag){//检查压缩文件或者解压操作中有无错误发生
    if( flag == -1)
        printf("输入文件%s不存在\n",inputName);
    else printf("操作成功\n");
}

//寻找最小和次小的两个结点
void findTwoMinNode(HuffTree tree, ui n, int *s1, int *s2){
    ui i;
    ul minValue = INF;
    for(i = 0; i < n; i++)
        if(tree[i].father == 0 && tree[i].val < minValue){
            minValue = tree[i].val;
            *s1 =i;
        }
    tree[*s1].father = 1;//选中 下回不做选择
    minValue = INF;
    for(i = 0; i < n; i++)
        if(tree[i].father == 0 && tree[i].val < minValue){
            minValue = tree[i].val;
            *s2 = i;
        }
}

//生成哈夫曼树
void createTree(HuffTree tree, ui chNum, ui nodeNum){
    ui i;
    int s1, s2;
    for(i = chNum; i < nodeNum; i++){//每次寻找频度最小和次小的两个点 和在一起
        findTwoMinNode(tree, i, &s1, &s2);
        tree[s1].father = i;
        tree[s2].father = i;
        tree[i].lchild = s1;
        tree[i].rchild = s2;
        tree[i].val = tree[s1].val + tree[s2].val;
    }
}

//生成哈夫曼编码
void HuffCode(HuffTree tree, u chNum){
    ui i;
    int cur,next,idx;
    char *filetmp = (char *)malloc(sizeof(char) * (Length + 1));//编码长度不超过255
    filetmp[Length]='\0';
    for(i = 0; i < chNum; i++){
        idx = Length;
        //从叶子向根反向遍历 求出编码
        cur = i;	
        next=tree[i].father;
        while(next != 0){
            if(tree[next].lchild == cur) filetmp[--idx] = '0';
            else filetmp[--idx] = '1';//左0右1
            cur = next;
            next = tree[next].father;
        }
        tree[i].code = (char *)malloc(sizeof(char) * (Length + 1 - idx));
        strcpy(tree[i].code, &filetmp[idx]);//保存编码到哈夫曼树中
    }
    free(filetmp);//释放临时空间
}

//压缩过程
int compress(char *inName, char *outName){
    ui i, j;//循环控制变量
    ui chNum;//字符种类
    ul fileLen = 0, aftLen = 0;
    uc chTmp;
    FILE *infile, *outfile, *in2file;
    HuffNode nodeTmp;
    ui nodeNum;
    HuffTree tree;
    HuffTree treeTmp;
    char code_buf[Length + 1] = "\0";//待存编码缓冲区
    ui code_len;
    
    //初始化
    treeTmp = (HuffTree)malloc(sizeof(HuffNode) * (Length + 1));
    for(i = 0; i <= Length; i++){
        treeTmp[i].val = 0;
        treeTmp[i].ch = (uc) i;
    }
    
    //便利文件 获取字符频度
    infile = fopen(inName, "rb");
    if(infile == NULL) return -1;
    fread((char *) &chTmp, sizeof(uc), 1, infile);
    while(! feof(infile)){
        treeTmp[chTmp].val++;
        fileLen++;
        fread((char *) &chTmp, sizeof(uc), 1, infile);
    }
    fclose(infile);
    
    //选择排序 剔除频度为0的字符
    for(i = 0; i < Length; i++)
        for(j = i + 1; j <= Length; j++)
            if(treeTmp[i].val < treeTmp[j].val){
                nodeTmp = treeTmp[i];
                treeTmp[i] = treeTmp[j];
                treeTmp[j] = nodeTmp;
            }
    //统计实际字符种类 
    for(i = 0; i <= Length; i++)
        if(treeTmp[i].val == 0) break;
    chNum = i;
    
    if(chNum == 1){//特殊情况
        outfile = fopen(outName, "wb");
        fwrite((char *) &chNum, sizeof(ui), 1, outfile);
        fwrite((char *) &treeTmp[0].ch, sizeof(uc), 1, outfile);
        fwrite((char *) &treeTmp[0].val, sizeof(ul), 1, outfile);
        free(treeTmp);
        fclose(outfile);
    }else {
        nodeNum = 2 * chNum - 1;//计算哈夫曼树所需结点
        tree = (HuffTree)malloc(sizeof(HuffNode) * nodeNum);
        
        //哈夫曼树初始化
        for(i = 0; i < chNum; i++){
            tree[i].ch = treeTmp[i].ch;
            tree[i].val = treeTmp[i].val;
            tree[i].father = 0;
        }
        free(treeTmp);
        for(i = chNum; i < nodeNum; i++)
            tree[i].father = 0;
        //创建哈夫曼树
        createTree(tree, chNum, nodeNum);
        //生成哈夫曼编码
        HuffCode(tree, chNum);
        
        //写入字符及相应权重
        outfile = fopen(outName, "wb");
        fwrite((char *) &chNum, sizeof(ui), 1, outfile);//写入字符种类
        for(i = 0; i < chNum; i++){
            fwrite((char *) &tree[i].ch, sizeof(uc), 1, outfile);//写入字符
            fwrite((char *) &tree[i].val, sizeof(ul), 1, outfile);//写入字符权重
        }
        fwrite((char *) &fileLen, sizeof(ul), 1, outfile);//写入文件长度
        
        //以二进制形式打开待压缩文件
        infile = fopen(inName, "rb");
        fread((char *) &chTmp, sizeof(uc), 1, infile);
        while(!feof(infile)){
            //匹配编码
            for(i = 0; i < chNum; i++)
                if(chTmp == tree[i].ch)
                    strcat(code_buf, tree[i].code);
            //每次用8比特对应字符 匹配编码
            ul buf_len = strlen(code_buf);
            while(buf_len >= 8){
                chTmp = '\0';
                for(i = 0; i < 8; i++){
                    chTmp <<= 1;//左移一位 为下一个比特腾出空间
                    if(code_buf[i] == '1') chTmp |= 1;
                }
                fwrite((char *) &chTmp, sizeof(uc), 1, outfile);//字节对应编码写入文件
                strcpy(code_buf, code_buf+8);
                buf_len = strlen(code_buf);
            }
            fread((char *) &chTmp, sizeof(uc), 1, infile);//持续处理
        }
        //处理最后不足8比特的部分
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
        //关闭文件 释放内存
        fclose(infile);
        fclose(outfile);
        for(i = 0 ; i < chNum; i++) free(tree[i].code);
        free(tree);
    }
    
    //统计压缩后文件的字节数 
    in2file = fopen(outName, "rb");
    fread((char *) &chTmp, sizeof(uc), 1, in2file);
    while(! feof(in2file)){
        aftLen++;
        fread((char *) &chTmp, sizeof(uc), 1, in2file);
    }
    fclose(in2file);
    printf("原文件共有%d字节数\n", fileLen);
    printf("压缩后文件共有%d字节数\n", aftLen);
    printf("压缩前后比为%.2lf\n", 1.0 * fileLen / aftLen); 
    return 1;
}

//解压缩过程
int extract(char *inName, char *outName){
    ui i;
    ul fileLen;
    ul writeLen = 0;//控制文件写入长度
    FILE *infile, *outfile;
    ui chNum;//存储字符种类
    ui nodeNum;
    HuffTree tree;
    uc chTmp;
    ui root;//以根结点为索引 匹配编码
    
    infile = fopen(inName, "rb");
    if(infile == NULL) return -1;//特判
    
    //读取文件字符及其编码
    fread((char *) &chNum, sizeof(ui), 1, infile);//读取字符数
    if(chNum == 1){//特殊情况
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
        //读取字符和权重 存入哈夫曼节点
        for(i = 0; i < chNum; i++){
            fread((char *) &tree[i].ch, sizeof(uc), 1, infile);
            fread((char *) &tree[i].val, sizeof(ul), 1, infile);
            tree[i].father = 0;
        }
        for(i = chNum; i < nodeNum; i++)tree[i].father = 0;
        //建立哈夫曼树
        createTree(tree, chNum, nodeNum);
        //读取文件长度和编码 进行解码
        fread((char *) &fileLen, sizeof(ul), 1, infile);
        outfile = fopen(outName, "wb");
        root = nodeNum - 1;
        while(true){
            fread((char *) &chTmp, sizeof(uc), 1, infile);
            //处理读取的一个字符长度的编码
            for(i = 0; i < 8 ; i++){
                //由根节点向叶节点正向匹配
                if(chTmp & 128)
                    root = tree[root].rchild;
                else
                    root = tree[root].lchild;
                if(root < chNum){
                    fwrite((char *) &tree[root].ch, sizeof(uc), 1, outfile);
                    writeLen++;
                    if(writeLen == fileLen) break;//循环终止
                    root = nodeNum - 1;//匹配下一个字符
                }
                chTmp <<= 1;//下一位移动到最高 供匹配
            }
            if(writeLen == fileLen)break;//循环终止
        }
        //关闭文件 释放内存
        fclose(infile);
        fclose(outfile);
        free(tree);
    }
    return  1;
}

int main(){
    int isRunning = 1, opt, flag;//flag为操作成功与否判断标志
    while (isRunning) {//isRunning判断系统是否运行
        opt = init();//操作种类
        switch (opt) {
            case 1:
                initflush();
                printf("压缩中……\n");
                flag = compress(inputName, outputName);
                checkFile(flag);
                break;
            case 2:
                initflush();
                printf("解压中……\n");
                flag = extract(inputName, outputName);
                checkFile(flag);
                break;
            case 3:
                isRunning = 0;
                printf("谢谢使用\n");
                break;
            default:
                printf("指令错误\n");
                break;
        }
        printf("\n");
    }
    return 0;
}

