#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>

//define filepath
#define FILEPATH "D:\\weight.csv"
//define string and construct
#define STRING_MAXSIZE 100
#define INIT_STRING (char*)malloc(sizeof(char)*STRING_MAXSIZE)

typedef struct gnode GNode;
typedef struct node Node;
//Define BinaryTree
struct node{
    int Data;
    int Weight;
    Node* Lchild;
    Node* Rchild;
    Node* Father;
    GNode* toGNode;
};

//Define BinaryTree
struct gnode{
    int Data;
    int Weight;
    int Level;
    int Pos;
    int PrePos;
    int isLeft;
    int isLeaves;
    Node* toNode;
};

typedef struct preOrderData Data;
struct preOrderData{
    int status;
    char* data;
    int strLen;
};

//Define RawData
typedef struct raw Raw;
struct raw{
    char* Data;
    int Weigth;
};

char* strReplace(char* src){
    int i;
    for(i=0;src[i]!='\0';i++){
        if(src[i]==','){
            src[i] = ' ';
        }
    }
    return src;
}


Raw* initRawNode(char* data,int weight){
    Raw* rw;
    char* str;

    rw = (Raw*)malloc(sizeof(Raw));
    str = INIT_STRING;
    strcpy(str,data);
    rw->Data = str;
    rw->Weigth = weight;
    return rw;
}

Raw** readFromFile(){
    FILE* fp;
    int corr,count;
    char *temp1,*temp2;
    int weight;
    Raw* np;
    Raw** npp;
    npp = (Raw**)malloc(sizeof(Raw*)*100);
    count = 0;
    fp = fopen(FILEPATH,"r");
    while(!feof(fp)){
        temp1 = INIT_STRING;
        fscanf(fp,"%s",temp1);
        temp1 = strReplace(temp1);
        temp2 = INIT_STRING;
        corr = sscanf(temp1,"%s %d",temp2,&weight);
        if(corr == 2){
            np = initRawNode(temp2,weight);
            npp[count] = np;
            count++;
        }    
    }
    npp[count] = NULL;
    return npp;
}

Node* initEmptyNode(Node* father){
    Node* np;
    np = (Node*)malloc(sizeof(Node));
    return np;
}

Node* initNode(Node* father,int data,int weight){
    Node* np;
    np = initEmptyNode(father);
    np->Data = data;
    np->Weight = weight;
    return np;
}

Node** sort(Node** npp){
    int count,i,j;
    Node* temp;
    i=0;
    for(i=0;npp[i]!=NULL;i++){
        //啦啦啦
    }
    count = i;
    for(i=count-1;i>0;i--){
        for(j=0;j<=i-1;j++){
            if(npp[j]->Weight < npp[j+1]->Weight){
                temp = npp[j];
                npp[j] = npp[j+1];
                npp[j+1] = temp;
            }
        }
    }
    return npp;
}

Node** rawToNode(Raw** src){
    Node** npp;
    Node* np;
    int count,i;
    npp = (Node**)malloc(sizeof(Node*)*40);
    for(i=0;src[i] != NULL;i++){
        npp[i] = initEmptyNode(NULL);
        if(strcmp("blank",src[i]->Data)==0){
            npp[i]->Data = (int)' ';
        }else{
            npp[i]->Data = (int)src[i]->Data[0];
        }
        npp[i]->Weight = src[i]->Weigth;
        npp[i]->Lchild = NULL;
        npp[i]->Rchild = NULL;
    }
    npp[i] = NULL;
    return npp;
}
/*
char* encode(char src,Node* head){
    char* data;
    int count;
    int srci,lflag,rflag;
    Node* np;
    srci = (int)src;
    np = head;
    data = INIT_STRING;
    count = 0;
    while(1){
        if(np->Data == srci){
            return data;
        }
        
    }
    
}
*/
void preOrderTravel(Node* np){
    if(np == NULL){
        printf("end\n");
        return;
    }
    printf("data:%d  weight:%d\n",np->Data,np->Weight);
    if(np->Lchild == NULL){
        printf("Left ");
    }
    preOrderTravel(np->Lchild);
    if(np->Rchild == NULL){
        printf("Right ");
    }
    preOrderTravel(np->Rchild);
}



/** PreOrderTravel With Data
 * flag:1-Left,0-Right
 * 前序遍历编码字符
*/
Data preOrderTravleWithData(Node* np,char target,int flag,char* data,int strLen){
    Data ret;
    if(np == NULL){
        ret.data = data;
        ret.strLen = -1;
        ret.status = 0;
        return ret;  
    }
    if(flag != -1){
        if(flag){
            data[strLen] = '0';
        }else{
            data[strLen] = '1';
        }
        strLen++;
        data[strLen] = '\0';      
    }

    if((int)target == np->Data){
        ret.status = 1;
        ret.data = data;
        ret.strLen = strLen;
        return ret;
    }else{
        ret = preOrderTravleWithData(np->Lchild,target,1,data,strLen);
        if(ret.status){
            return ret;
        }
        ret = preOrderTravleWithData(np->Rchild,target,0,data,strLen);
        if(ret.status){
            return ret;
        }
        ret.data = data;
        ret.strLen = -1;
        ret.status = 0;
        return ret;
    }
}

/** CreateHaffmanTree
 * Create a Haffman tree from input struct array
*/
Node* CreateHaffmanTree(Node** src){
    int flag,tempi1,tempi2,tempi3,i,j,k,count;
    Node *temp1,*temp2,*temp3;
    Node** npp;
    npp = src;
    flag = 1;
    while(1){
        if(npp[1]==NULL){
            break;
        }
        npp = sort(npp);
        for(i=0;src[i]!=NULL;i++){
            //啦啦啦
        }
        count = i;
        temp1 = npp[count-1];
        temp2 = npp[count-2];
        temp3 = initEmptyNode(NULL);
        temp3->Data = -10;  //标记这个不是叶子节点，Data!=-10则是叶子节点
        temp3->Weight = temp1->Weight + temp2->Weight;
        if(temp1->Weight > temp2->Weight){
            //temp1权值大于temp2，temp1置左
            temp3->Lchild = temp1;
            temp3->Rchild = temp2;
        }else{
            temp3->Lchild = temp2;
            temp3->Rchild = temp1;
        }
        temp1->Father = temp3;
        temp2->Father = temp3;
        npp[count-2] = temp3;
        npp[count-1] = NULL;
    }
    return npp[0];
}

char* encode(char* src,Node* np){
    char* dest,*temp2,*temp;
    Data data;
    int i,j,len,k;
    dest = (char*)malloc(sizeof(char)*500);
    temp2 = INIT_STRING;
    temp2[0] = '\0';
    i = 0;
    j = 0;
    dest[0] = '\0';
    for(i=0;src[i] != '\0';i++){
        data = preOrderTravleWithData(np,src[i],-1,temp2,0);
        temp = data.data;
        len = data.strLen;
        for(k=0;k<len;k++){
            dest[j+k] = temp[k];
        }
        dest[j+k] = '\0';
        j+=k;
    }
    return dest;
}

char* decode(Node* head,char* src){
    int i,j,k;
    char* temp1,temp2;
    Node* np;
    i=0,j=0,k=0;
    np = head;
    temp1 = INIT_STRING;
    for(i=0;src[i-1]!='\0';i++){
        if(np->Lchild==NULL&&np->Rchild==NULL){
            temp1[j] = (char)(np->Data);
            temp1[j+1] = '\0';
            j++;
            np = head;
            i--;
            continue;
        }else{
            if(src[i] == '0'){
                np = np->Lchild;
            }else{
                np = np->Rchild;
            }
        }
    }
    return temp1;
}

int checkInputString(char* src){
    int i;
    for(i=0;src[i] != '\0';i++){
        if(src[i]!=32&&(src[i]<41||src[i]>90)){
            return 0;
        }
    }
    return 1;
}

int checkInputStream(char* src){
    int i;
    for(i=0;src[i] != '\0';i++){
        if(src[i]!='0'&&src[i]!='1'){
            return 0;
        }
    }
    return 1;
}

void encodeMenu(Node* head){
    int flag;
    char*src,*dest;
    src = INIT_STRING;
    system("cls");
    printf(
        "========================= 加密字符串 =========================\n\n"
        "                           请输入待加密字符串\n"
        "                           仅可包含A-Z和空格\n\n"
        "===================================================================\n\n"
    );
    gets(src);
    flag = checkInputString(src);
    if(flag==1){
        dest = encode(src,head);
        system("cls");
        printf(
            "========================= 加密字符串 =========================\n\n"
            "                           加密成功\n"
            "===================================================================\n\n"
        );
        printf("%s",dest);
        getch();
        return;
    }
    system("cls");
    printf(
        "========================= 加密字符串 =========================\n\n"
        "                           加密失败\n"
        "                           非法字符\n\n"
        "===================================================================\n\n"
    );
    getch();
    return;
}

void decodeMenu(Node* head){
    int flag;
    char*src,*dest;
    src = INIT_STRING;
    system("cls");
    printf(
        "========================= 解密字符串 =========================\n\n"
        "                           请输入待加密字符串\n"
        "                             仅可包含0和1\n\n"
        "===================================================================\n\n"
    );
    gets(src);
    flag = checkInputStream(src);
    if(flag==1){
        dest = decode(head,src);
        system("cls");
        printf(
            "========================= 解密字符串 =========================\n\n"
            "                           解密成功\n"
            "===================================================================\n\n"
        );
        printf("%s",dest);
        getch();
        return;
    }
    system("cls");
    printf(
        "========================= 解密字符串 =========================\n\n"
        "                           解密失败\n"
        "                           非法字符\n\n"
        "===================================================================\n\n"
    );
    getch();
    return;
}

void PreOrderTravelGraph(Node* np,int* prePos){
    if(np == NULL){
        return;
    }
    if(np->toGNode->isLeaves){
        np->toGNode->PrePos = *prePos;
        np->toGNode->Pos = (np->toGNode->PrePos+1)*4;
        *prePos = *prePos+1;
    }
    PreOrderTravelGraph(np->Lchild,prePos);
    PreOrderTravelGraph(np->Rchild,prePos);
}

void PreOrderTravelGraph2(Node* np){
    if(np->toGNode->isLeaves){
        return;
    }
    PreOrderTravelGraph2(np->Lchild);
    PreOrderTravelGraph2(np->Rchild);
    np->toGNode->Pos = ((np->Lchild->toGNode->Pos)+(np->Rchild->toGNode->Pos))/2;
}

void levelOrderTravel(Node* np,GNode** array,int* arrLen,int levelNow,int LevelNum[],int tarLevel,int left){
    if(np == NULL){
        return;
    }
    if(levelNow == tarLevel){
        GNode* gnp = (GNode*)malloc(sizeof(GNode));
        gnp->toNode = np;
        np->toGNode = gnp;
        gnp->Data = np->Data;
        gnp->Level = levelNow;
        gnp->isLeft = left;
        gnp->Weight = np->Weight;
        array[*arrLen] = gnp;
        LevelNum[tarLevel]++;
        *arrLen = *arrLen + 1;
        if(gnp->toNode->Data == -10){
            gnp->isLeaves = 0;
        }else{
            gnp->isLeaves = 1;
        }
        return;
    }
    levelOrderTravel(np->Lchild,array,arrLen,levelNow+1,LevelNum,tarLevel,1);
    levelOrderTravel(np->Rchild,array,arrLen,levelNow+1,LevelNum,tarLevel,0);
    return;
}

void graphMenu(Node* head){
    system("cls");
    int i,j,k,temp,*arrLen,*prePos,*arrLenLast,maxLevel,LevelNum[20],LevelNumC[20],LevelPos[20][50],levelNow,tarLevel,max,posNow,nextPos,toPos;
    int ppos1,pposn;
    for(i=0;i<20;i++){
        LevelNum[i] = 0;
        LevelNumC[i] = 0;
    }
    GNode* array[200];//=(GNode**)malloc(sizeof(GNode*)*200);
    array[0] = NULL;
    arrLen = (int*)malloc(sizeof(int));
    arrLenLast = (int*)malloc(sizeof(int));
    prePos = (int*)malloc(sizeof(int));
    *prePos = 0;
    *arrLen = 0;
    *arrLenLast = 0;
    maxLevel = 0;
    levelNow = 0;
    tarLevel = 0;
    for(i=0;i<20;i++){
        *arrLenLast = *arrLen;
        levelOrderTravel(head,array,arrLen,0,LevelNum,i,-1);
        if(*arrLen == *arrLenLast){
            break;
        }
    }
    temp = 0;
    maxLevel = i;
    PreOrderTravelGraph(head,prePos);
    PreOrderTravelGraph2(head);
    for(i=1;i<maxLevel;i++){
        LevelNumC[i] = LevelNumC[i-1] + LevelNum[i-1];
    }
    for(i=0;i<maxLevel;i++){
        for(j=0;j<LevelNum[i];j++){
            LevelPos[i][j] = array[LevelNumC[i]+j]->Pos;
        }
    }
    for(i=0;i<maxLevel;i++){
        max = LevelNum[i];
        j=0,posNow=0;
        while(j<max){
            nextPos=LevelPos[i][j];
            for(k=posNow;k<nextPos-2;k++){
                printf(" ");
            }
            if(array[LevelNumC[i]+j]->isLeaves){
                printf("  %c ",(char)array[LevelNumC[i]+j]->toNode->Data);
            }else{
                if(array[LevelNumC[i]+j]->Weight>1000){
                    printf("%4d",array[LevelNumC[i]+j]->Weight);
                }else if(array[LevelNumC[i]+j]->Weight>100){
                    printf(" %3d",array[LevelNumC[i]+j]->Weight);
                }else if(array[LevelNumC[i]+j]->Weight>10){
                    printf(" %2d ",array[LevelNumC[i]+j]->Weight);
                }else{
                    printf("  %1d ",array[LevelNumC[i]+j]->Weight);
                }
            }
            posNow = nextPos+1;
            j++;
        }
        printf("\n");

        if(i!=maxLevel-1){
            ppos1 = array[LevelNumC[i]]->Pos;
            pposn = array[LevelNumC[i]+LevelNum[i]]->Pos;
            j=0,posNow=0;
            max = LevelNum[i];
            while(j<max){
                nextPos=LevelPos[i][j];
                for(k=posNow;k<nextPos;k++){
                    printf(" ");
                }
                if(array[LevelNumC[i]+j]->isLeaves){
                    printf(" ");
                }else{
                    printf("|");
                }
                posNow = k;
                j++;
            }
            printf("\n");
            posNow=0;
            j=0;
            while(j<max){
                if(array[LevelNumC[i]+j]->isLeaves){
                    j++;
                    continue;
                    posNow-=4;
                }
                for(;posNow<array[LevelNumC[i]+j]->toNode->Lchild->toGNode->Pos;posNow++){
                    printf(" ");
                }
                for(;posNow<array[LevelNumC[i]+j]->toNode->Rchild->toGNode->Pos+2;posNow++){
                    printf("-");
                }
                j++;
                posNow-=2;
            }  
        }


        if(1){
            printf("\n");
            i++;
            j=0,posNow=0;
            max = LevelNum[i];
            while(j<max){
                nextPos=LevelPos[i][j];
                for(k=posNow;k<nextPos;k++){
                    printf(" ");
                }
                printf("|");
                posNow = k;
                j++;
            }
            i--;
        }
        printf("\n");


    }
    printf("\n\n\n按任意键继续....");
    getch();

    return;
}

void mainMenu(Node* head){
    char temp;
    while(1){
        system("cls");
        printf(
            "========================= 霍夫曼树编码系统 =========================\n\n"
            "                           1、加密字符串\n"
            "                           2、解密编码\n"
            "                           3、图形化树\n"
            "                           0、退出系统\n\n"
            "===================================================================\n\n"
        );
        temp = (char)getch();
        switch(temp){
            case '1':{
                encodeMenu(head);
                break;
            }
            case '2':{
                decodeMenu(head);
                break;
            }
            case '3':{
                graphMenu(head);
                break;
            }
            case '0':{
                return;
            }
        }        
    }

}

/** main
 main entry fnuction 
*/
int main(){
    system("chcp 65001");
    Raw** rpp;
    Node** npp;
    char*temp1,*temp2,*en,*de;
    int i;
    rpp = readFromFile();
    npp = rawToNode(rpp);
    npp = sort(npp);
    Node* hft = CreateHaffmanTree(npp);
    mainMenu(hft);
    system("pause");
}
