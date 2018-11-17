#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//define filepath
#define FILEPATH "D:\\数据结构\\第二次大作业\\src\\weight.csv"
//define string and construct
#define String char*
#define String_MAXSIZE 100
#define Init_String (String)malloc(sizeof(char)*String_MAXSIZE)

typedef struct node Node;
//Define BinaryTree
struct node{
    String Data;
    int Weight;
    Node* Lchild;
    Node* Rchild;
    Node* Father;
};

//Define RawData
typedef struct raw Raw;
struct raw{
    String Data;
    int Weigth;
};

Raw*[] readFromFile(){

}

Node* initEmptyNode(Node* father){
    Node* np;
    np = (Node*)malloc(sizeof(Node));
    return np;
}

Node* initNode(Node* father,String data,int weight){
    Node* np;
    String str;
    str = Init_String;
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
    
}