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
    int rnd;//堆优先级，随机取
    int cnt=1;//该节点出现次数
};
Data A[MAX];

struct Node{
    Node *parent; //该结点的父节点，方便操作
    Node *son[2];//son[0]代表左，son[1]代表右
    Data val; //结点值
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        val.rnd=rand();
        this->val=val;
    }
    inline int rand(){
        static int seed = 2333;
        return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
    }
    int getfp(){//得到当前节点是父节点的哪个儿子，左返回0，右返回1，没有父节点返回-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
};

struct Treap{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }

    void insertNode(Data val){
        Node *now=root;
        Node *node=new Node(val);
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.d > node->val.d?0:1;
            now=now->son[fp];
        }
        if(now!=root){
            linkNode(node->parent,node,fp);
            adjust(node);
        }else{
            root=node;
        }
    }

    void  adjust(Node *now){//旋转调整，使得插入后满足堆的性质
        Node *i,*j=now->parent;
        for(i=now;i->val.rnd < j->val.rnd;i=j){
            j=i->parent;
            rotate(j,i->getfp());
            if(j==root){
                root=i;
                break;
            }
        }
    }
    Node* rotate(Node *now,int fp){//now是以哪个节点为根，fp是要转now的左边还是右边
        Node *p=now->parent;
        Node *e=now->son[fp];
        int nowfp=now->getfp();
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        return e;
    }

    Node *findNode(Data val){//同BST树
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
    bool deleteNode(Data val){//旋转到叶子结点
        Node *i,*j,*now;
        now=findNode(val);
        if(now==NULL)
            return 0;
        j=now;
        int fp;
        while(1){
            if(j->son[0]&&j->son[1]){
                fp=j->son[0]->val.rnd < j->son[1]->val.rnd? 0:1;
            }else if(j->son[0]){
                fp=0;
            }else if(j->son[1]){
                fp=1;
            }else{
                break;
            }
            i=j->son[fp];
            rotate(j,fp);
            if(j==root)
                root=i;
        }
        if(j->parent){
            j->parent->son[j->getfp()]=NULL;
        }else{
            root=NULL;
        }
        delete j;
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
    Data data;
    Treap *t=new Treap();
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i].d);
        t->insertNode(A[i]);
    }
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
