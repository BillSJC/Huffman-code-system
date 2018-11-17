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
    char* Data;
    int Weight;
    Node* Lchild;
    Node* Rchild;
    Node* Father;
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

Node* initNode(Node* father,char* data,int weight){
    Node* np;
    char* str;
    str = INIT_STRING;
    strcpy(str,data);
    np = initEmptyNode(father);
    np->Data = str;
    np->Weight = weight;
    return np;
}

/** main
 main entry fnuction 
*/
int main(){
    Raw** npp;
    int i;
    npp = readFromFile();
    for(i=0;npp[i]!=NULL;i++){
        printf("%s %d\n",npp[i]->Data,npp[i]->Weigth);
    } 
    system("pause");
}