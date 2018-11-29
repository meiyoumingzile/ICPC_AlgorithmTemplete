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
    int cnt=1;//该节点出现次数
    int sumcnt=0;//自己节点数的个数，会把相同的算进去
};
Data A[MAX];

struct Node{
    Node *parent; //该结点的父节点，方便操作
    Node *son[2];//son[0]代表左，son[1]代表右
    Data val; //结点值
    Node(){
        parent=son[0]=son[1]=NULL;
    }
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//返回当前节点是父节点的哪个儿子，左返回0，右返回1，没有父节点返回-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
    void updataSumcnt(){//更新当前点的sumcnt的值
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+son[i]->val.cnt;
            }
        }
    }
    void updataSumcnt(int k){//向上更新sumcnt直到前驱节点为止
        for(Node *now=parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }
    int getSum(int fp){//返回当前节点左边或者右边的点，的数量总和
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
};

struct BST{
    Node *root=NULL;//原始节点，左边才是真正的根

    void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }

    void insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    void insertNode(Node *node){
        Node *now=root;//初始G的d是无限大
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.d > node->val.d?0:1;
            now=now->son[fp];
        }
        if(now!=root){
            linkNode(node->parent,node,fp);
            node->updataSumcnt(1);
        }else{
            root=node;
        }
    }

    Node *findNode(Data val){//同BST树
        int fp;
        for(Node *now=root; now ;now=now->son[fp]){
            if(now->val.d == val.d){
                return now;
            }
            fp=now->val.d > val.d?0:1;
        }
        return NULL;
    }


    bool deleteNode(Data val){
        Node *now,*temp,*p;
        now=findNode(val);
        if(now==NULL)
            return 0;
        if(now->val.cnt > 1){
            now->val.cnt--;
            now->updataSumcnt(-1);
            return 1;
        }
        temp=now;
        if(now->son[0]&&now->son[1]){
            for(temp=now->son[0];temp->son[1]!=NULL;temp=temp->son[1]);
            swap(now->val,temp->val);

            if(now->son[0]==temp){
                linkNode(now,temp->son[0],0);
            }else{
                linkNode(temp->parent,temp->son[0],1);
            }
            temp->updataSumcnt(- now->val.cnt);
            now->updataSumcnt();
            now->updataSumcnt(now->val.cnt-1);
        }else{
            int fp=now->son[0]?0:1;;
            if(now==root){
                root=now->son[fp];
                if(root)
                    root->parent=NULL;
            }else{
                linkNode(now->parent,now->son[fp],now->getfp());
                now->updataSumcnt(-1);
            }
        }
        delete temp;
        return 1;
    }

    void println(){//中序遍历
        printf(":");
        __LDRprint(root);
        printf("\n");
    }
    void __LDRprint(Node *now){//中序遍历
        if(now){
            __LDRprint(now->son[0]);
            printf("%d-%d ",now->val.d,now->val.sumcnt);
            __LDRprint(now->son[1]);
        }
    }
    int findRank(Data val,int fp){//fp==0查询val.d数的排名,第几小(若有多个相同的数，输出最小的排名),fp==1相反
        Node *now=findNode(val);
        if(now==NULL)
            return -1;
        int sum=1;
        if(now->son[fp])
            sum+=now->getSum(fp);
        for(;now!=root;now=now->parent){
            if(now->getfp()!=fp){//是根或者右边才可以算
                sum+=now->parent->val.cnt+now->parent->getSum(fp);
            }
        }
        return sum;
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
    Node *getAdjoin(Node *now,int fp){//返回指针,找不到返回NULL，条件是now在数里存在，fp==0表示小于now的最大数，fp==1表示大于now的最小数
        Node *e=now->son[fp];
        if(e){
            for(;e->son[1-fp];e=e->son[1-fp]);
        }else{
            for(e=now;e->getfp()==fp;e=e->parent);//没有fp方向上的子节点的情况下，向上找一个一个找
            e=e->parent;
        }
        return e;
    }
    Node *getAdjoin(Data val,int fp){//返回val相邻的节点的指针，fp==0表示小于now的最大数，fp==1表示大于now的最小数
        Node *now,*last;
        int fp1;
        for(now=root; now ;now=now->son[fp1]){
            if(now->val.d == val.d)
                return getAdjoin(now,fp);//条件是now在数里存在
            last=now;
            fp1=now->val.d > val.d ? 0:1;
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
   // freopen("in2.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("myout.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int id,k,T;
    Node *e;
    scanf("%d",&T);
    BST *t=new BST();
    while(T--){
        Data data;
        scanf("%d%d",&id,&data.d);
        //printf("%d %d ",id,data.d);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            printf("%d\n",t->findRank(data,0));
        }else if(id==4){
            e=t->findRankNode(data.d,0);
            if(e)
                printf("%d\n",e->val.d);
        }else if(id==5){
            e=t->getAdjoin(data,0);
            if(e){
                printf("%d\n",e->val.d);
            }
        }else if(id==6){
            e=t->getAdjoin(data,1);
            if(e){
                printf("%d\n",e->val.d);
            }
        }
    }
return 0;
}
