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
    int rnd;//С���ѣ����ȡ,
    int cnt=1;//�ýڵ���ִ���
    int sumcnt=0;//�Լ����ж��ӽڵ����ĸ����������ͬ�����ȥ
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
    void updataSumcnt(Node *now,int k){//�Ӹ��׿�ʼ��ÿ���ڵ������Ӽ�
        for(now=now->parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }


    void split(int k,Node *&tl,Node *&tr){//����rootΪ�������İ�key�İѱ�kС�Ľڵ���ɵ������룬tl,tr�Ƿ��ؽ��
        __split(root,k,tl,tr,[](int a,int b)->bool{
            return a<=b;
        });
    }
    void __split(Node *r,int k,Node *&tl,Node *&tr,bool (*cmp)(int a,int b)){//����rΪ�������İ�key�İѱ�kС�Ľڵ���ɵ������룬tl,tr�Ƿ��ؽ��
        if(r==NULL){//����Ҷ��
            tl=NULL;
            tr=NULL;
            return;
        }
        if(cmp(r->val.k,k)){//�����С�ڵ���k����������Լ���������tl�ģ��ݹ��ұ�
            tl=r;
            __split(tl->son[1],k,tl->son[1],tr,cmp);
            if(tl->son[1])
                tl->son[1]->parent=tl;
        }else{
            tr=r;
            __split(tr->son[0],k,tl,tr->son[0],cmp);
            if(tr->son[0])
                tr->son[0]->parent=tr;
        }
        r->updataSumcnt();
    }

    Node* FHQmerge(Node *x,Node *y){//x��y�Ƿ��Ѷ����ģ�����rnd�ϲ���С����
        if(x==NULL){
            return y;
        }else if(y==NULL){
            return x;
        }
        if(x->val.rnd < y->val.rnd){
            Node *e=FHQmerge(x->son[1],y);
            linkNode(x,e,1);
            x->updataSumcnt();
            return x;
        }else{//y��С����y���ұ߲��䣬��y����߿��ܱ�
            Node *e=FHQmerge(x,y->son[0]);
            linkNode(y,e,0);
            y->updataSumcnt();
            return y;
        }
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
    void insertNode(Data val){
        Node *tl,*tr;
        Node *node=new Node(val);
        if(root){
            split(val.k,tl,tr);
            root=FHQmerge(FHQmerge(tl,node),tr);//��tl,node,tr�ϲ�
        }else{
            root=node;
        }
    }
    bool deleteNode(Data val){//�ж����ͬ����ɾ��һ��
        Node *tl,*tr,*now;
        split(val.k,tl,tr);//root�ֳ�������tl��tr��
        if(tl==NULL)
            return false;
        __split(tl,val.k-1,tl,now,[](int a,int b)->bool{
            return a<=b;
        });
        if(now&&now->val.k==val.k){

            now=FHQmerge(now->son[0],now->son[1]);
            root=FHQmerge(FHQmerge(tl,now),tr);
            return true;
        }else{
            root=FHQmerge(FHQmerge(tl,now),tr);
            return false;
        }
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
    void printBFS(){//�������
        queue<Node*>que;
        que.push(root);
        while(!que.empty()){
            Node *e=que.front();
            que.pop();
            if(e->son[0]){
                printf("%d-%d ",e->val.k,e->son[0]->val.k);
                if(e->val.rnd>e->son[0]->val.rnd){
                    printf("����");
                }
                que.push(e->son[0]);
            }
            if(e->son[1]){
                printf("%d-%d ",e->val.k,e->son[1]->val.k);
                if(e->val.rnd>e->son[1]->val.rnd){
                    printf("����");
                }
                que.push(e->son[1]);
            }
        }printf("\n");
    }
    int findRank(Data val){//fp==0��ѯval.k��������,�ڼ�С(���ж����ͬ�����������С������)
        Node *tl,*tr;
        split(val.k-1,tl,tr);//root�ֳ�������tl��tr��
        int sum=tl?tl->val.cnt+tl->val.sumcnt:0;
        root=FHQmerge(tl,tr);
        return sum+1;
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
    Node* rankNode(int k){//��ѯ������kС�Ľڵ�
        return __rankNode(root,k);
    }
    Node* __rankNode(Node *now,int k){//��ѯ������kС�Ľڵ�,�ݹ�д��
        if(k<=now->getSum(0))
            return __rankNode(now->son[0],k);//˵������������
        else{
            if(k==now->getSum(0)+1)
                return now;
            else{
                k-=now->getSum(0)+1;//������ֻ�ǵ�ǰ������������Ҫ��ȥǰ���
                return __rankNode(now->son[1],k);//�ݹ����������
            }
        }
    }
    Node *getAdjoin(Data val,int fp){//����val���ڵĽڵ��ָ�룬fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *now,*tl,*tr;
        if(fp==0){
            __split(root,val.k,tl,tr,[](int a,int b)->bool{
                return a<b;
            });
            if(tl==NULL)//tlΪ��˵��û��ǰ��
                return NULL;
            for(now=tl;now->son[1];now=now->son[1]);
        }else{
            __split(root,val.k,tl,tr,[](int a,int b)->bool{
                return a<=b;
            });
            if(tr==NULL)//tlΪ��˵��û�к��
                return NULL;
            for(now=tr;now->son[0];now=now->son[0]);
        }
        root=FHQmerge(tl,tr);
        return now;
    }
};

int main(int argc,char *argv[]){
   // freopen("P3369_5.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
   // freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
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
            printf("%d\n",t->findRank(data));
        }else if(id==4){
            e=t->rankNode(data.k);
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
        //t->printBFS();
    }
return 0;
}
/*
20
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
2 317721
*/
