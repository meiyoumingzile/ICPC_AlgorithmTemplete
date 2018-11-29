#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
struct Data{
    int d;
};
Data A[MAX];

struct Node{
    Node *parent; //该结点的父节点，方便操作
    Node *son[2];//son[0]代表左，son[1]代表右
    Data val; //结点值
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
};

struct BST{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }

    bool insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    bool insertNode(Node *node){
        Node *last,*now=root;
        int fp;
        while(now){
            if(now->val.d == node->val.d)
                return 0;
            node->parent=now;
            fp=now->val.d > node->val.d?0:1;
            now=now->son[fp];
        }
        if(now!=root)
            linkNode(node->parent,node,fp);
        else
            root=node;
        return 1;
    }

    Node *findNode(Data val){
        for(Node *now=root; now ;){
            if(now->val.d == val.d)
                return now;
            if(now->val.d > val.d){//要插入的点值比较小，向左走
                now=now->son[0];
            }else{//要插入的点值比较大，向右走
                now=now->son[1];
            }
        }
        return NULL;
    }
    bool deleteNode(Data val){
        Node *last,*now,*temp,*p;;
        now=findNode(val);
        if(now==NULL)
            return 0;
        temp=now;
        if(now->son[0]==NULL){
            if(now==root)
                root=now->son[1];
            else
                linkNode(now->parent,now->son[1],now==now->parent->son[0]?0:1);
        }else if(now->son[1]==NULL){
            if(now==root)
                root=now->son[0];
            else
                linkNode(now->parent,now->son[0],now==now->parent->son[0]?0:1);
        }else{
            for(temp=now->son[0];temp->son[1]!=NULL;temp=temp->son[1]);
            swap(now->val,temp->val);
            if(now->son[0]==temp){
                linkNode(now,temp->son[0],0);
            }else{
                temp->parent->son[1]=NULL;
            }
        }
        delete temp;
        return 1;
    }


    void LDRprint(Node *now){//中序遍历
        if(now){
            LDRprint(now->son[0]);
            printf("%d ",now->val.d);
            LDRprint(now->son[1]);
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N,i,j,k;
    BST *t=new BST();
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i].d);
        t->insertNode(A[i]);
    }
    Data data;
    while(~scanf("%d",&data.d)){
        t->deleteNode(data);
        t->LDRprint(t->root);
        printf("\n");
    }
return 0;
}
/*
7
40 20 80 10 30 60 160
*/
