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
    bool c=0;//0代表红色，1代表黑色
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
};

struct RB_tree{
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
            node->c=1;
            root=node;
            return;
        }
        Node *p,*bro,*now=root;
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
        now=node;
        p=node->parent;
        p->son[fp]=node;
        bro=p->getBrother();
        now->updataSumcnt(1);
        if(p->c==0){//父亲是红色修改,父亲是黑色什么都不做
            while(p&&p->c==0&&bro&&bro->c==0){//叔叔存在是红色
                bro->c=p->c=1;
                now=p->parent;
                now->c=0;
                p=now->parent;
                if(p)
                    bro=p->getBrother();
            }
            root->c=1;
            if(p&&p->c==0){//p存在，说明没访问到根节点，且根一定是黑色，说明这里p最高也是根的儿子
                fp=p->getfp();
                if(fp!=now->getfp()){//叔叔节点不存在或是黑色，now和p方向不一致，要旋转一致
                    rotate_zig(p,fp);
                    now=p;
                    p=now->parent;
                }
                p->c=1;////叔叔节点不存在或是黑色，now和p同方向
                p->parent->c=0;
                rotate_zig(p->parent,fp^1);
            }
        }
        root->c=1;
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
        deleteRBNode(now,p,nowfp);
        if(now==root){
            root=now->son[fp];
        }else{
            linkNode(p,now->son[fp],nowfp);
            now->updataSumcnt(-1);
        }
        if(root){
            root->parent=NULL;
            root->c=1;
        }
        delete now;
        return 1;
    }
    void deleteRBNode(Node *D,Node *p,int fp){
        Node *bro,*nephew1,*nephew2;
        if(D->c==0||D==root){
        }else if(D->son[1]==NULL&&D->son[0]&&D->son[0]->c==0){
            D->son[0]->c=1;
        }else if(D->son[0]==NULL&&D->son[1]&&D->son[1]->c==0){
            D->son[1]->c=1;
        }else{
            p=D->parent;
            bro=D->parent->son[fp^1];
            if(bro->c==0){//
                swap(p->c,bro->c);
                rotate_zig(p,fp);
                bro=p->son[fp^1];
            }
            nephew1=bro->son[fp^1];//远侄子
            nephew2=bro->son[fp];//近侄子
            if(nephew1&&nephew1->c==0){
                aboveself:;
                swap(p->c,bro->c);
                nephew1->c=1;
                rotate_zig(p,fp);
            }else if(nephew2&&nephew2->c==0){
                rotate_zig(bro,fp^1);
                swap(nephew2->c,bro->c);
                bro=p->son[fp^1];
                nephew1=bro->son[fp^1];//远侄子
                goto aboveself;
            }else{
                bro->c=0;
                if(p->c==1)
                    deleteRBNode(p,p->parent,p->getfp());
                else
                    p->c=1;
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
        e->updataSumcnt();
        while(root->parent)
            root=root->parent;
        return e;
    }

    int findRank(Data val,int fp){//fp==0查询val.k数的排名,第几小(若有多个相同的数，输出最小的排名),fp==1相反
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
            printf("%d %d %d,颜色：%d\n",now->val.k,now->son[0]?now->son[0]->val.k:-1,now->son[1]?now->son[1]->val.k:-1,now->c);
            LDRprint(now->son[0]);
            LDRprint(now->son[1]);
        }
    }
};

int main(int argc,char *argv[]){
   // freopen("data//P6136_6.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
   // freopen("data//my.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));
    int i,id,k,T,n,m,last=0;
    Node *e;
    scanf("%d%d",&n,&m);
    RB_tree *t=new RB_tree();
    Data data;
    for(i=0;i<n;i++){
        scanf("%d",&data.k);
        t->insertNode(data);
    }
    int ans=0;
    while(m--){
        scanf("%d%d",&id,&data.k);
        data.k^=last;
        //if(m<3)
           // printf("%d %d %d\n",m,id,last);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            last=t->findRank(data,0);
            ans^=last;
        }else if(id==4){
            e=t->findRankNode(data.k,0);
            last=e->val.k;
            ans^=last;
        }else if(id==5){
            e=t->getAdjoin(data,0);
            last=e->val.k;
            ans^=last;
        }else if(id==6){
            e=t->getAdjoin(data,1);
            last=e->val.k;
            ans^=last;
        }
       // printf("%d\n",ans);
    }
    printf("%d\n",ans);
return 0;
}
/*
6 7
1 1 4 5 1 4
2 1
1 9
4 1
5 8
3 13
6 7
1 4
*/
