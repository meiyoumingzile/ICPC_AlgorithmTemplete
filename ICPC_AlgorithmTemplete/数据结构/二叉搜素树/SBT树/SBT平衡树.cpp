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
    int s=0;
    int cnt=1;//��¼�ýڵ���ִ���
};
Data A[MAX];

struct Node{
    Node *p; //�ý��ĸ��ڵ㣬�������
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(Data val){
        p=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//�õ���ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(p==NULL)
            return -1;
        return p->son[0]==this?0:1;
    }
    void gets(){//����sֵ
        int i,sum=0;
        for(i=0;i<2;i++){
            if(son[i]){
                sum+=son[i]->val.s+1;
            }
        }
        val.s=sum;
    }
};

struct SBT{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0������1������
        if(now)
            now->son[fp]=next;
        if(next)
            next->p=now;
    }
    bool compare(Node *a,Node *b){//a>=b����true,a<b����false
        if(a&&b){
            return a->val.s >= b->val.s;
        }else if(b){
            return 0;
        }else {
            return 1;
        }
    }

    void insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    void insertNode(Node *node){
        Node *last,*now=root;
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                delete node;
                return;
            }
            node->p=now;
            fp=now->val.d > node->val.d?0:1;
            now=now->son[fp];
        }

        if(now!=root){
            linkNode(node->p,node,fp);
            for(now=node->p;now;now=now->p){//����sֵ��ͬʱ����
                now->gets();
                matain(now,1);
                matain(now,0);
            }
        }else{
            root=node;
        }
    }

    void matain(Node *t,int fp){
        if(t->son[1-fp]){
            if(!compare(t->son[fp],t->son[1-fp]->son[1-fp])){
                rotate(t,1-fp);
            }
            if(!compare(t->son[fp],t->son[1-fp]->son[fp])){
                rotate(t->son[1-fp],fp);
                rotate(t,1-fp);
            }
        }
    }
    void rotate(Node *now,int fp){//now�����ĸ��ڵ�Ϊ����fp��Ҫתnow����߻����ұ�
        Node *p=now->p;
        Node *e=now->son[fp];
        int nowfp=now->getfp();
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        now->gets();
        e->gets();
        if(root==now)
            root=e;
    }
    Node *findNode(Data val){
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
        Node *now,*temp;
        now=findNode(val);
        if(now==NULL)
            return 0;
        temp=now;
        if(now->son[0]==NULL){
            if(now==root)
                root=now->son[1];
            else
                linkNode(now->p,now->son[1],now==now->p->son[0]?0:1);
        }else if(now->son[1]==NULL){
            if(now==root)
                root=now->son[0];
            else
                linkNode(now->p,now->son[0],now==now->p->son[0]?0:1);
        }else{
            for(temp=now->son[0];temp->son[1]!=NULL;temp=temp->son[1]);
            swap(now->val,temp->val);
            if(now->son[0]==temp){
                linkNode(now,temp->son[0],0);
            }else{
                temp->p->son[1]=NULL;
            }
        }
        for(now=temp->p;now;now=now->p){
            now->val.s--;
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
    SBT *t=new SBT();
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i].d);
        t->insertNode(A[i]);
        t->LDRprint(t->root);
        printf("\n");
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
10
40 20 80 10 30 5 15 25 35 1
*/
