#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=500010;
const int mod=1e9+7;

struct Data{
    int k;//key
    int rnd;//С���ѣ����ȡ,
    int sumcnt=0;//�Լ����ж��ӽڵ����ĸ����������ͬ�����ȥ
};

struct Node{
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(Data val){
        son[0]=son[1]=NULL;
        val.rnd=rand();
        this->val=val;
    }
    inline int rand(){
        static int seed = 2333;
        return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
    }
    void updataSumcnt(){//�õ�������ǰ�ڵ����ڵģ��ڵ���Ŀ����������ͬ��
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+1;
            }
        }
    }
    int getSum(int fp){
        if(son[fp])
            return son[fp]->val.sumcnt+1;
        return 0;
    }
    Node *clone(){
        Node *node=new Node(val);
        node->son[0]=son[0];
        node->son[1]=son[1];
        return node;
    }
};

struct Persistent_FHQ_Treap{
    Node *root[MAX];
    int rlen=1;
    void cloneRoot(int verID){
        root[rlen]=root[verID]->clone();
        rlen++;
    }
    void split(Node *r,int k,Node *&tl,Node *&tr,bool per){//����rootΪ�������İ�key�İѱ�kС�Ľڵ���ɵ������룬tl,tr�Ƿ��ؽ��
        __split(r,k,tl,tr,[](int a,int b)->bool{
            return a<=b;
        },per);
    }
    void __split(Node *r,int k,Node *&tl,Node *&tr,bool (*cmp)(int a,int b),bool per){//����rΪ�������İ�key�İѱ�kС�Ľڵ���ɵ������룬tl,tr�Ƿ��ؽ��
        if(r==NULL){//����Ҷ��
            tl=NULL;
            tr=NULL;
            return;
        }
        if(cmp(r->val.k,k)){//�����С�ڵ���k����������Լ���������tl�ģ��ݹ��ұ�
            tl=per?r->clone():r;
            __split(tl->son[1],k,tl->son[1],tr,cmp,per);
            tl->updataSumcnt();
        }else{
            tr=per?r->clone():r;
            __split(tr->son[0],k,tl,tr->son[0],cmp,per);
            tr->updataSumcnt();
        }
    }
    Node* merge(Node *x,Node *y){//x��y�Ƿ��Ѷ����ģ�����rnd�ϲ���С����.per�����Ƿ�ɳ־û�
        if(x==NULL){
            return y;
        }else if(y==NULL){
            return x;
        }
        if(x->val.rnd < y->val.rnd){
            x->son[1]=merge(x->son[1],y);
            x->updataSumcnt();
            return x;
        }else{//y��С����y���ұ߲��䣬��y����߿��ܱ�
            y->son[0]=merge(x,y->son[0]);
            y->updataSumcnt();
            return y;
        }
    }

    Node *findNode(int verID,Data val){//ͬBST��
        int fp;
        for(Node *now=root[verID]; now ;now=now->son[fp]){
            if(now->val.k == val.k)
                return now;
            fp=now->val.k > val.k?0:1;
        }
        return NULL;
    }
    Node* insertNode(int verID,Data val){//�ڰ汾verID�²���
        Node *tl,*tr;
        split(root[verID],val.k,tl,tr,1);
        root[rlen++]=merge(merge(tl,new Node(val)),tr);//��tl,node,tr�ϲ�
        return root[rlen-1];
    }
    bool deleteNode(int verID,Data val){//�ڰ汾verID��ɾ��
        Node *tl,*tr,*now;
        split(root[verID],val.k,tl,tr,1);
        __split(tl,val.k-1,tl,now,[](int a,int b)->bool{
            return a<=b;
        },1);
        if(now&&now->val.k==val.k){
            now=merge(now->son[0],now->son[1]);
            root[rlen++]=merge(merge(tl,now),tr);
            return true;
        }else{
            root[rlen++]=merge(merge(tl,now),tr);
            return false;
        }
    }

    void printBFS(int verID){//�������
        queue<Node*>que;
        if(root[verID]){
            printf("����%d: ",root[verID]->val.k);
        }else{
            printf("û��\n");
            return;
        }
        que.push(root[verID]);
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
    int findRank(int verID,Data val){//fp==0��ѯval.k��������,�ڼ�С(���ж����ͬ�����������С������)
        Node *tl,*tr;
        split(root[verID],val.k-1,tl,tr,0);//root�ֳ�������tl��tr��
        int sum=tl?1+tl->val.sumcnt:0;
        root[verID]=merge(tl,tr);
        return sum+1;
    }

    Node* rankNode(int verID,int k){//��ѯ������kС�Ľڵ�
        return __rankNode(root[verID],k);
    }
    Node* __rankNode(Node *now,int k){//��ѯ������kС�Ľڵ�,�ݹ�д��
        if(now==NULL)
            return NULL;
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
    Node *getAdjoin(int verID,Data val,int fp){//����val���ڵĽڵ��ָ�룬fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *now,*tl,*tr;
        if(fp==0){
            __split(root[verID],val.k,tl,tr,[](int a,int b)->bool{
                return a<b;
            },0);
            if(tl==NULL)//tlΪ��˵��û��ǰ��
                return NULL;
            for(now=tl;now->son[1];now=now->son[1]);
        }else{
            __split(root[verID],val.k,tl,tr,[](int a,int b)->bool{
                return a<=b;
            },0);
            if(tr==NULL)//tlΪ��˵��û�к��
                return NULL;
            for(now=tr;now->son[0];now=now->son[0]);
        }
        root[verID]=merge(tl,tr);
        return now;
    }
};

 Persistent_FHQ_Treap *t=new Persistent_FHQ_Treap();
int main(int argc,char *argv[]){
   // freopen("P3369_5.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
   // freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int id,k,T,version;
    Node *e;
    scanf("%d",&T);
    Data data;
    while(T--){
        scanf("%d%d%d",&version,&id,&data.k);
        if(id==1){
            t->insertNode(version,data);
        }else if(id==2){
            t->deleteNode(version,data);
        }else if(id==3){//�����ѯ����ҲҪ�����°汾�������ֺ�ԭ�汾һ��
            k=t->findRank(version,data);
            t->cloneRoot(version);
            printf("%d\n",k);
        }else if(id==4){//�ò���������Ҫ�����°汾
            e=t->rankNode(version,data.k);
            if(e){
                t->cloneRoot(version);
                printf("%d\n",e->val.k);
            }
        }else if(id==5){
            e=t->getAdjoin(version,data,0);
            if(e){
                t->cloneRoot(version);
                printf("%d\n",e->val.k);
            }else{
                printf("-2147483647\n");
            }
        }else if(id==6){
            e=t->getAdjoin(version,data,1);
            if(e){
                t->cloneRoot(version);
                printf("%d\n",e->val.k);
            }else{
                printf("2147483647\n");
            }
        }
    }
return 0;
};
/*
10
0 1 9
1 1 3
1 1 10
2 4 2
3 3 9
3 1 2
6 4 1
6 2 9
8 6 3
4 5 8
*/
