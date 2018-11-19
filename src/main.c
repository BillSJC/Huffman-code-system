#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//define filepath
#define FILEPATH "D:\\weight.csv"
//define string and construct
#define STRING_MAXSIZE 100
#define INIT_STRING (char*)malloc(sizeof(char)*STRING_MAXSIZE)

typedef struct node Node;
//Define BinaryTree
struct node{
    int Data;
    int Weight;
    Node* Lchild;
    Node* Rchild;
    Node* Father;
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
        if((src[i]!=32)&&src[i]<41&&src[i]>90){
            return 0;
        }
    }
    return 1;
}

int checkInputStream(char* src){
    int i;
    for(i=0;src[i] != '\0';i++){
        if((src[i]!='0'&&src[i]!='1'){
            return 0;
        }
    }
    return 1;
}

/** main
 main entry fnuction 
*/
int main(){
    Raw** rpp;
    Node** npp;
    char*temp1,*temp2,*en,*de;
    int i;
    rpp = readFromFile();
    npp = rawToNode(rpp);
    npp = sort(npp);
    for(i=0;npp[i]!=NULL;i++){
        printf("%c %d\n",(char)npp[i]->Data,npp[i]->Weight);
    } 
    printf("%d\n\n");
    Node* hft = CreateHaffmanTree(npp);
    preOrderTravel(hft);
    temp1 = INIT_STRING;
    temp2 = (char*)malloc(sizeof(char)*500);
    gets(temp1);
    en = encode(temp1,hft);
    de = decode(hft,en);
    printf("%s %s",en,de);
    system("pause");
}