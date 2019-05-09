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
    Node *parent; //�ý��ĸ��ڵ㣬�������
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//�õ���ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
};

struct Spaly{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0������1������
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

    Node* rotate_zig(Node* now,int fp){//����ת�����ڸ��ڵ�ʱ��fp��ָ��Ҫתnow����߻����ұߣ������ڵ�,fp��1������
        Node *e, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp];
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        return e;
    }
    Node* rotate_zigzig(Node* now,int fp){//ͬ��˫��ת����fp��ָ��fp��1����������ҵ��ң�0������������
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[fp],pe=now->son[fp];//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
        linkNode(now,pe->son[1-fp],fp);
        linkNode(pe,e->son[1-fp],fp);
        linkNode(e,pe,1-fp);
        linkNode(pe,now,1-fp);
        /*if(fp==1){
            e=now->right->right,pe=now->right;//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
            linkNode(now,pe->left,1);
            linkNode(pe,e->left,1);
            linkNode(e,pe,0);
            linkNode(pe,now,0);
        }else{
            e=now->left->left,pe=now->left;//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
            linkNode(now,pe->right,0);
            linkNode(pe,e->right,0);
            linkNode(e,pe,1);
            linkNode(pe,now,1);
        }*/
        linkNode(p,e,nowfp);//������ת��ĸ��׽ڵ�
        return e;
    }
    Node* rotate_zigzag(Node* now,int fp){//����˫��ת��fp��1����������ҵ���0������������
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[1-fp],pe=now->son[fp];//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
        linkNode(now,e->son[1-fp],fp);
        linkNode(pe,e->son[fp],1-fp);
        linkNode(e,pe,fp);
        linkNode(e,now,1-fp);
        /*if(fp==1){
            e=now->right->left,pe=now->right;//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
            linkNode(now,e->left,1);
            linkNode(pe,e->right,0);
            linkNode(e,pe,1);
            linkNode(e,now,0);
        }else{
            e=now->left->right,pe=now->left;//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
            linkNode(now,e->right,0);
            linkNode(pe,e->left,1);
            linkNode(e,pe,0);
            linkNode(e,now,1);
        }*/
        linkNode(p,e,nowfp);//������ת��ĸ��׽ڵ�
        return e;
    }
    void topRoot(Node *node){//�����ڵ㵽��
        if(node->parent==root){//�ڸ��ڵ�����
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
        if(res&&res!=root)//res���Ǹ��ڵ���ƶ�����
            topRoot(res);
        return res;
    }
    Node *__findNode(Data val){//
        for(Node *now=root; now ;){
            if(now->val.d == val.d)
                return now;
            if(now->val.d > val.d){//Ҫ����ĵ�ֵ�Ƚ�С��������
                now=now->son[0];
            }else{//Ҫ����ĵ�ֵ�Ƚϴ�������
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
    void LDRprint(Node *now){//�������
        if(now){
            LDRprint(now->son[0]);
            printf("%d ",now->val.d);
            LDRprint(now->son[1]);
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
