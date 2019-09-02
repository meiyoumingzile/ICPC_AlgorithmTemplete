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
    int rnd;//�����ȼ������ȡ
    int cnt=1;//�ýڵ���ִ���
};
Data A[MAX];

struct Node{
    Node *parent; //�ý��ĸ��ڵ㣬�������
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        val.rnd=rand();
        this->val=val;
    }
    inline int rand(){
        static int seed = 2333;
        return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
    }
    int getfp(){//�õ���ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
};

struct Treap{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0������1������
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

    void  adjust(Node *now){//��ת������ʹ�ò��������ѵ�����
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
    Node* rotate(Node *now,int fp){//now�����ĸ��ڵ�Ϊ����fp��Ҫתnow����߻����ұ�
        Node *p=now->parent;
        Node *e=now->son[fp];
        int nowfp=now->getfp();
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        return e;
    }

    Node *findNode(Data val){//ͬBST��
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
    bool deleteNode(Data val){//��ת��Ҷ�ӽ��
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
