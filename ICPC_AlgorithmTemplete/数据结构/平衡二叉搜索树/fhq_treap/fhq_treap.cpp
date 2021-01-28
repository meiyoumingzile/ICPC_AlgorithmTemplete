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
    int k;//key
    int rnd;//�����ȼ������ȡ
    int cnt=1;//�ýڵ���ִ���
    int sumcnt=0;//�Լ��ڵ����ĸ����������ͬ�����ȥ
};

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
    void updataSumcnt(){//�õ�������ǰ�ڵ����ڵģ��ڵ���Ŀ����������ͬ��
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+son[i]->val.cnt;
            }
        }
    }
    int getSum(int fp){
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
};

struct FHQ_Treap{
    Node *root=NULL;

    void linkNode(Node *now,Node *next,int fp){//fp 0������1������
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }
    void updataSumcnt(Node *now,int k){
        for(now=now->parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }

    void insertNode(Data val){
        Node *now=root;
        Node *node=new Node(val);
        int fp;
        while(now){
            if(now->val.k == node->val.k){
                now->val.cnt++;
                updataSumcnt(now,1);
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.k > node->val.k?0:1;
            now=now->son[fp];
        }
        if(now!=root){
            linkNode(node->parent,node,fp);
            //adjust(node);
            updataSumcnt(node,1);
        }else{
            root=node;
        }
    }

    void split(Node *r,int k,Node *&tl,Node *&tr){//����rΪ�������İ�key�İѱ�kС�Ľڵ���ɵ������룬ans1,ans2�Ƿ��ؽ��
        if(r==NULL){//����Ҷ��
            tl=tr=NULL;
            return;
        }
        if(r->val.k < k){
            tl=r;
            split(tl->son[1],k,tl->son[1],tr);
            tl->son[1]->parent=tl;
        }else{
            tr=r;
            split(tr->son[0],k,tl,tr->son[0]);
            tr->son[0]->parent=tr;
        }
        r->updataSumcnt();
    }
    Node* merge(Node *a,Node *b){


    }
    Node *findNode(Data val){//ͬBST��
        int fp;
        for(Node *now=root; now ;now=now->son[fp]){
            if(now->val.k == val.k)
                return now;
            fp=now->val.k > val.k?0:1;
        }
        return NULL;
    }
    bool deleteNode(Data val){//�ж����ͬ����ɾ��һ��

    }

    void println(){//�������
        __LDRprint(root);
        printf("\n");
    }
    void __LDRprint(Node *now){//�������
        if(now){
            __LDRprint(now->son[0]);
            printf("%d-%d ",now->val.k,now->val.cnt);
            __LDRprint(now->son[1]);
        }
    }
    int findRank(Data val,int fp){//fp==0��ѯval.k��������,�ڼ�С(���ж����ͬ�����������С������),fp==1�෴
        int sum=1,_fp;
        for(Node *now=root; now ;now=now->son[_fp]){
            if(now->val.k == val.k)
                return sum+now->getSum(fp);
            _fp=now->val.k > val.k ? 0:1;
            if(_fp==fp^1){
                sum+=now->val.cnt+now->getSum(fp);
            }
        }
        return sum;
    }
    Node *findRankNode(int x,int fp){//���ؽڵ��Dָ�룬fp=0(��KС����),fp=1(��K�����),
        int fp1,pr=0,r=root->getSum(fp)+1;
        Node *now=root,*last=NULL;
        while(1){
            if(x==r)
                return now;
            fp1=x>r?1-fp:fp;
            if(now->son[fp1]==NULL){
                for(now;fp1==fp&&now;now=now->parent)
                    fp1=now->getfp();
                return now;
            }
            now=now->son[fp1];
            if(fp1!=fp){
                pr=r;
                last=now->parent;
                r=pr +  now->getSum(fp) + now->parent->val.cnt;
            }else{
                r=pr+now->getSum(fp);
                r+=last==NULL?1:last->val.cnt;
            }
        }
    }
    Node *getAdjoin(Node *now,int fp){//����ָ��,�Ҳ�������NULL��������now��������ڣ�fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *e=now->son[fp];
        if(e){
            for(;e->son[1-fp];e=e->son[1-fp]);
        }else{
            for(e=now;e->getfp()==fp;e=e->parent);//û��fp�����ϵ��ӽڵ������£�������һ��һ����
            e=e->parent;
        }
        return e;
    }
    Node *getAdjoin(Data val,int fp){//����val���ڵĽڵ��ָ�룬fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *now,*last;
        int fp1;
        for(now=root; now ;now=now->son[fp1]){
            if(now->val.k == val.k)
                return getAdjoin(now,fp);//������now���������
            last=now;
            fp1=now->val.k > val.k ? 0:1;
        }
        if(fp1==fp){
            for(now=last;now!=root&&now->getfp()==fp;now=now->parent);
            if(now!=root)
                return now->parent;
            return NULL;
        }else{
            return last;
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int id,k,T;
    Node *e;
    scanf("%d",&T);
    FHQ_Treap *t=new FHQ_Treap();
    while(T--){
        Data data;
        scanf("%d%d",&id,&data.k);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            printf("%d\n",t->findRank(data,0));
        }else if(id==4){
            e=t->findRankNode(data.k,0);
            if(e)
                printf("%d\n",e->val.k);
        }else if(id==5){
            e=t->getAdjoin(data,0);
            if(e){
                printf("%d\n",e->val.k);
            }
        }else if(id==6){
            e=t->getAdjoin(data,1);
            if(e){
                printf("%d\n",e->val.k);
            }
        }
        //t->println();
    }
return 0;
}
/*
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598

*/
