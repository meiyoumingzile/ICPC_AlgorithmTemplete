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
    int rnd;//小顶堆，随机取,
    int cnt=1;//该节点出现次数
    int sumcnt=0;//自己所有儿子节点数的个数，会把相同的算进去
};

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
    void updataSumcnt(){//得到包含当前节点在内的，节点数目，包括了相同的
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

    void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }
    void updataSumcnt(Node *now,int k){//从父亲开始，每个节点数量加减
        for(now=now->parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }


    void split(int k,Node *&tl,Node *&tr){//把以root为根的树的按key的把比k小的节点组成的树分离，tl,tr是返回结果
        __split(root,k,tl,tr,[](int a,int b)->bool{
            return a<=b;
        });
    }
    void __split(Node *r,int k,Node *&tl,Node *&tr,bool (*cmp)(int a,int b)){//把以r为根的树的按key的把比k小的节点组成的树分离，tl,tr是返回结果
        if(r==NULL){//到达叶子
            tl=NULL;
            tr=NULL;
            return;
        }
        if(cmp(r->val.k,k)){//如果根小于等于k，则根本身以及它的左都是tl的，递归右边
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

    Node* FHQmerge(Node *x,Node *y){//x和y是分裂而来的，按照rnd合并，小根堆
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
        }else{//y的小，则y的右边不变，但y的左边可能变
            Node *e=FHQmerge(x,y->son[0]);
            linkNode(y,e,0);
            y->updataSumcnt();
            return y;
        }
    }

    Node *findNode(Data val){//同BST树
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
            root=FHQmerge(FHQmerge(tl,node),tr);//把tl,node,tr合并
        }else{
            root=node;
        }
    }
    bool deleteNode(Data val){//有多个相同的数删除一个
        Node *tl,*tr,*now;
        split(val.k,tl,tr);//root分成两部分tl和tr，
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

    void println(){//中序遍历
        __LDRprint(root);
        printf("\n");
    }
    void __LDRprint(Node *now){//中序遍历
        if(now){
            __LDRprint(now->son[0]);
            printf("%d-%d ",now->val.k,now->val.cnt);
            __LDRprint(now->son[1]);
        }
    }
    void printBFS(){//中序遍历
        queue<Node*>que;
        que.push(root);
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
    int findRank(Data val){//fp==0查询val.k数的排名,第几小(若有多个相同的数，输出最小的排名)
        Node *tl,*tr;
        split(val.k-1,tl,tr);//root分成两部分tl和tr，
        int sum=tl?tl->val.cnt+tl->val.sumcnt:0;
        root=FHQmerge(tl,tr);
        return sum+1;
    }


    Node *findRankNode(int x,int fp){//返回节点的D指针，fp=0(第K小的数),fp=1(第K大的数),
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
    Node* rankNode(int k){//查询排名第k小的节点
        return __rankNode(root,k);
    }
    Node* __rankNode(Node *now,int k){//查询排名第k小的节点,递归写法
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
    Node *getAdjoin(Data val,int fp){//返回val相邻的节点的指针，fp==0表示小于now的最大数，fp==1表示大于now的最小数
        Node *now,*tl,*tr;
        if(fp==0){
            __split(root,val.k,tl,tr,[](int a,int b)->bool{
                return a<b;
            });
            if(tl==NULL)//tl为空说明没有前驱
                return NULL;
            for(now=tl;now->son[1];now=now->son[1]);
        }else{
            __split(root,val.k,tl,tr,[](int a,int b)->bool{
                return a<=b;
            });
            if(tr==NULL)//tl为空说明没有后继
                return NULL;
            for(now=tr;now->son[0];now=now->son[0]);
        }
        root=FHQmerge(tl,tr);
        return now;
    }
};

int main(int argc,char *argv[]){
   // freopen("P3369_5.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
   // freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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
