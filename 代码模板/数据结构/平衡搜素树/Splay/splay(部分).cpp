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
    int getfp(){//得到当前节点是父节点的哪个儿子，左返回0，右返回1，没有父节点返回-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
};

struct Spaly{
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

    Node* rotate_zig(Node* now,int fp){//单旋转，用于根节点时，fp是指，要转now的左边还是右边，到根节点,fp是1代表右
        Node *e, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp];
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        return e;
    }
    Node* rotate_zigzig(Node* now,int fp){//同向双旋转，，fp是指，fp是1，代表操作右的右，0代表操作左的左
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[fp],pe=now->son[fp];//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
        linkNode(now,pe->son[1-fp],fp);
        linkNode(pe,e->son[1-fp],fp);
        linkNode(e,pe,1-fp);
        linkNode(pe,now,1-fp);
        /*if(fp==1){
            e=now->right->right,pe=now->right;//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
            linkNode(now,pe->left,1);
            linkNode(pe,e->left,1);
            linkNode(e,pe,0);
            linkNode(pe,now,0);
        }else{
            e=now->left->left,pe=now->left;//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
            linkNode(now,pe->right,0);
            linkNode(pe,e->right,0);
            linkNode(e,pe,1);
            linkNode(pe,now,1);
        }*/
        linkNode(p,e,nowfp);//更新旋转后的父亲节点
        return e;
    }
    Node* rotate_zigzag(Node* now,int fp){//异向双旋转，fp是1，代表操作右的左，0代表操作左的右
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[1-fp],pe=now->son[fp];//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
        linkNode(now,e->son[1-fp],fp);
        linkNode(pe,e->son[fp],1-fp);
        linkNode(e,pe,fp);
        linkNode(e,now,1-fp);
        /*if(fp==1){
            e=now->right->left,pe=now->right;//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
            linkNode(now,e->left,1);
            linkNode(pe,e->right,0);
            linkNode(e,pe,1);
            linkNode(e,now,0);
        }else{
            e=now->left->right,pe=now->left;//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
            linkNode(now,e->right,0);
            linkNode(pe,e->left,1);
            linkNode(e,pe,0);
            linkNode(e,now,1);
        }*/
        linkNode(p,e,nowfp);//更新旋转后的父亲节点
        return e;
    }
    void topRoot(Node *node){//调整节点到根
        if(node->parent==root){//在根节点下面
            root=rotate_zig(root,node->getfp());
            return;
        }
        Node *p=node->parent,*pp=p->parent,*e;
        if(pp->son[1]==p&&p->son[1]==node){
            e=rotate_zigzig(pp,1);
        }else if(pp->son[0]==p&&p->son[0]==node){
            e=rotate_zigzig(pp,0);
        }else{
            e=rotate_zigzag(pp,p->getfp());
        }
        if(pp==root)
            root=e;
    }
    Node *findNode(Data val){
        Node *res=__findNode(val);
        if(res&&res!=root)//res不是根节点就移动到根
            topRoot(res);
        return res;
    }
    Node *__findNode(Data val){//
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
    Data data;
    Spaly *t=new Spaly();
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i].d);
        t->insertNode(A[i]);
    }
    data.d=100;
    t->deleteNode(data);
    while(~scanf("%d",&data.d)){
        t->insertNode(data);
        t->LDRprint(t->root);
        printf("\n");
    }
return 0;
}
/*
10
1 5 -22 222 999 0 8 6 88888 -222
4
4 3 2 1 1
20
50 40 30 60 80 67 55 33 10 15 24 65 87 67 69 89 90 39 57 62
7
40 20 80 10 30 60 160
60 10 20 40
*/
