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
    int rnd;//小顶堆，随机取,
    int sumcnt=0;//自己所有儿子节点数的个数，会把相同的算进去
};

struct Node{
    Node *son[2];//son[0]代表左，son[1]代表右
    Data val; //结点值
    Node(Data val){
        son[0]=son[1]=NULL;
        val.rnd=rand();
        this->val=val;
    }
    inline int rand(){
        static int seed = 2333;
        return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
    }
    void updataSumcnt(){//得到包含当前节点在内的，节点数目，包括了相同的
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
    void split(Node *r,int k,Node *&tl,Node *&tr,bool per){//把以root为根的树的按key的把比k小的节点组成的树分离，tl,tr是返回结果
        __split(r,k,tl,tr,[](int a,int b)->bool{
            return a<=b;
        },per);
    }
    void __split(Node *r,int k,Node *&tl,Node *&tr,bool (*cmp)(int a,int b),bool per){//把以r为根的树的按key的把比k小的节点组成的树分离，tl,tr是返回结果
        if(r==NULL){//到达叶子
            tl=NULL;
            tr=NULL;
            return;
        }
        if(cmp(r->val.k,k)){//如果根小于等于k，则根本身以及它的左都是tl的，递归右边
            tl=per?r->clone():r;
            __split(tl->son[1],k,tl->son[1],tr,cmp,per);
            tl->updataSumcnt();
        }else{
            tr=per?r->clone():r;
            __split(tr->son[0],k,tl,tr->son[0],cmp,per);
            tr->updataSumcnt();
        }
    }
    Node* merge(Node *x,Node *y){//x和y是分裂而来的，按照rnd合并，小根堆.per代表是否可持久化
        if(x==NULL){
            return y;
        }else if(y==NULL){
            return x;
        }
        if(x->val.rnd < y->val.rnd){
            x->son[1]=merge(x->son[1],y);
            x->updataSumcnt();
            return x;
        }else{//y的小，则y的右边不变，但y的左边可能变
            y->son[0]=merge(x,y->son[0]);
            y->updataSumcnt();
            return y;
        }
    }

    Node *findNode(int verID,Data val){//同BST树
        int fp;
        for(Node *now=root[verID]; now ;now=now->son[fp]){
            if(now->val.k == val.k)
                return now;
            fp=now->val.k > val.k?0:1;
        }
        return NULL;
    }
    Node* insertNode(int verID,Data val){//在版本verID下插入
        Node *tl,*tr;
        split(root[verID],val.k,tl,tr,1);
        root[rlen++]=merge(merge(tl,new Node(val)),tr);//把tl,node,tr合并
        return root[rlen-1];
    }
    bool deleteNode(int verID,Data val){//在版本verID下删除
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

    void printBFS(int verID){//中序遍历
        queue<Node*>que;
        if(root[verID]){
            printf("根是%d: ",root[verID]->val.k);
        }else{
            printf("没有\n");
            return;
        }
        que.push(root[verID]);
        while(!que.empty()){
            Node *e=que.front();
            que.pop();
            if(e->son[0]){
                printf("%d-%d ",e->val.k,e->son[0]->val.k);
                if(e->val.rnd>e->son[0]->val.rnd){
                    printf("错误");
                }
                que.push(e->son[0]);
            }
            if(e->son[1]){
                printf("%d-%d ",e->val.k,e->son[1]->val.k);
                if(e->val.rnd>e->son[1]->val.rnd){
                    printf("错误");
                }
                que.push(e->son[1]);
            }
        }printf("\n");
    }
    int findRank(int verID,Data val){//fp==0查询val.k数的排名,第几小(若有多个相同的数，输出最小的排名)
        Node *tl,*tr;
        split(root[verID],val.k-1,tl,tr,0);//root分成两部分tl和tr，
        int sum=tl?1+tl->val.sumcnt:0;
        root[verID]=merge(tl,tr);
        return sum+1;
    }

    Node* rankNode(int verID,int k){//查询排名第k小的节点
        return __rankNode(root[verID],k);
    }
    Node* __rankNode(Node *now,int k){//查询排名第k小的节点,递归写法
        if(now==NULL)
            return NULL;
        if(k<=now->getSum(0))
            return __rankNode(now->son[0],k);//说明在左子树中
        else{
            if(k==now->getSum(0)+1)
                return now;
            else{
                k-=now->getSum(0)+1;//右子树只是当前子树的排名，要减去前面的

                return __rankNode(now->son[1],k);//递归查找右子树
            }
        }
    }
    Node *getAdjoin(int verID,Data val,int fp){//返回val相邻的节点的指针，fp==0表示小于now的最大数，fp==1表示大于now的最小数
        Node *now,*tl,*tr;
        if(fp==0){
            __split(root[verID],val.k,tl,tr,[](int a,int b)->bool{
                return a<b;
            },0);
            if(tl==NULL)//tl为空说明没有前驱
                return NULL;
            for(now=tl;now->son[1];now=now->son[1]);
        }else{
            __split(root[verID],val.k,tl,tr,[](int a,int b)->bool{
                return a<=b;
            },0);
            if(tr==NULL)//tl为空说明没有后继
                return NULL;
            for(now=tr;now->son[0];now=now->son[0]);
        }
        root[verID]=merge(tl,tr);
        return now;
    }
};

 Persistent_FHQ_Treap *t=new Persistent_FHQ_Treap();
int main(int argc,char *argv[]){
   // freopen("P3369_5.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
   // freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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
        }else if(id==3){//此题查询操作也要建立新版本，但保持和原版本一样
            k=t->findRank(version,data);
            t->cloneRoot(version);
            printf("%d\n",k);
        }else if(id==4){//该步骤因题意要创建新版本
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
