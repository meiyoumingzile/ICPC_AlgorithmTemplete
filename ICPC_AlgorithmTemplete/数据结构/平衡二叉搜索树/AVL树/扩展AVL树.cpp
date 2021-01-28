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
    int k;//key作为排序的值
    int cnt=1;//该节点出现次数
    int sumcnt=0;//子节点数的个数，会把相同的算进去
};
struct Node{
    Node *parent,*son[2];//son[0]代表左，son[1]代表右
    Data val;
    int h=1;//高度
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//得到当前节点是父节点的哪个儿子，左返回0，右返回1，没有父节点返回-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
    Node* getBrother(){
        if(parent)
            return parent->son[0]==this?parent->son[1]:parent->son[0];
        return NULL;
    }
    void updataSumcnt(){//更新当前点的sumcnt的值
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+son[i]->val.cnt;
            }
        }
    }
    void updataSumcnt(int k){//向上更新sumcnt直到根节点为止
        for(Node *now=parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }
    int getSum(int fp){//返回当前节点左边或者右边的点，的数量总和
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
    int getSum(){//返回当前节点以及子节点所有数量总和
        return val.sumcnt+val.cnt;
    }
    void updatah(){//更新当前点的h的值
        h=max((son[0]?son[0]->h:0),(son[1]?son[1]->h:0))+1;
    }
    int difh(){//得到左右高多差,负数代表右边高，整数代表左边高
        return (son[0]?son[0]->h:0) - (son[1]?son[1]->h:0);
    }
};

struct AVL_tree{
    Node *root=NULL;
    inline void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
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
        Node *node=new Node(val);
        insertNode(node);
    }
    void insertNode(Node *node){
        if(root==NULL){//是空树
            root=node;
            return;
        }
        Node *p,*now=root;
        int fp;
        while(now){
            if(now->val.k== node->val.k){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.k < node->val.k;
            now=now->son[fp];
        }
        p=node->parent;
        p->son[fp]=node;
        node->updataSumcnt(1);
        adjustTree(p);
    }
    bool deleteNode(Data val){
        Node *now,*temp,*p;
        now=findNode(val);
        if(now==NULL)
            return 0;
        if(now->val.cnt>1){
            now->val.cnt--;
            now->updataSumcnt(-1);
            return 1;
        }
        if(now->son[0]&&now->son[1]){//如果两个儿子都有，就找最值，换过去
            for(temp=now->son[0];temp->son[1];temp=temp->son[1]);
            swap(now->val,temp->val);
            now=temp;
            for(;temp;temp=temp->parent){
                temp->updataSumcnt();
            }
        }
        int fp=now->son[0]?0:1;
        p=now->parent;
        int nowfp=now->getfp();
        if(now==root){
            root=now->son[fp];
        }else{
            linkNode(p,now->son[fp],nowfp);
            now->updataSumcnt(-1);
            adjustTree(p);
        }
        if(root)
            root->parent=NULL;
        delete now;
        return 1;
    }
    void adjustTree(Node* now){
        int fp,fp1,difh,difh1;
        Node *s;
        for(;now->parent;now=now->parent){
            now->updatah();
            difh=now->difh();
            fp=difh<0;
            if(abs(difh)>1){
                s=now->son[fp];
                difh1=s->difh();
                fp1=difh1<0;
                if(fp!=fp1)
                    rotate_zig(s,fp);
                now=rotate_zig(now,fp^1);
            }
        }
    }
    Node* rotate_zig(Node* now,int fp){//单旋转，以now为支点,fp=0代表把now向左下转，fp=1代表把now向右下转
        Node *e, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp^1];
        linkNode(now,e->son[fp],fp^1);
        linkNode(e,now,fp);
        linkNode(p,e,nowfp);
        now->updataSumcnt();
        now->updatah();
        e->updataSumcnt();
        e->updatah();
        while(root->parent)
            root=root->parent;
        return e;
    }
    int findRank(Data val,int fp){//fp==0查询val.k数的排名,第几小(若有多个相同的数，输出最小的排名),fp==1相反
        Node *now=findNode(val);
        if(now==NULL){
            now=this->getAdjoin(val,fp^1);
            if(now==NULL){
                return root->getSum();
            }
        }
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
            fp1=x>r?fp^1:fp;
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
            for(;e->son[fp^1];e=e->son[fp^1]);
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
            if(now->val.k == val.k)
                return getAdjoin(now,fp);//条件是now在数里存在
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
    void LDRprint(Node *now){//中序遍历
        if(now){
            printf("%d %d %d,高度：%d\n",now->val.k,now->son[0]?now->son[0]->val.k:-1,now->son[1]?now->son[1]->val.k:-1,now->h);
            LDRprint(now->son[0]);
            LDRprint(now->son[1]);
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("data1.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("myout.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int id,k,T;
    Node *e;
    scanf("%d",&T);
    AVL_tree *t=new AVL_tree();
    Data data;
    while(T--){
        scanf("%d%d",&id,&data.k);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            printf("%d\n",t->findRank(data,0));
        }else if(id==4){
            e=t->findRankNode(data.k,0);
            if(e){
                 printf("%d\n",e->val.k);
            }
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
    }
return 0;
}
/*
11
1 6
1 4
1 0
1 1
1 5
2 4
2 0
1 3
1 7
2 3
1 2

*/
