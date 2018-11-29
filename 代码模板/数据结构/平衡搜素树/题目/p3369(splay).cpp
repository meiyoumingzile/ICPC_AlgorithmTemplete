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
    bool com=0;//1代表左大于右，0代表右大于左
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

struct Splay{
    void reversal(Node *now);
    Node *root=NULL;//原始节点，左边才是真正的根

    void linkNode(Node *now,Node *next,int fp){//fp 0代表左，1代表右
        if(now&&fp!=-1)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }

    void build(int l,int r){//建一个d从l到r的树[l,r]
        Data data;
        data.d=l;
        root=new Node(data);
        Node *now=root,*node;
        int i;
        for(i=l+1;i<=r;i++,now=now->son[1]){//插入点
            data.d=i;
            node=new Node(data);
            linkNode(now,node,1);
        }
        //printf("d");
        for(i=0;now;now=now->parent){//更新sumcnt
            now->val.sumcnt=i++;
        }
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
                if(now!=root)
                   topRoot(now);
                return now;
            }
            fp=now->val.d > val.d?now->val.com:1-now->val.com;
        }
        return NULL;
    }

    Node* rotate_zig(Node *now,int fp){//now是以哪个节点为根，fp是要转now的左边还是右边
        Node *p=now->parent;
        Node *e=now->son[fp];
        int nowfp=now->getfp();
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        now->updataSumcnt();
        e->updataSumcnt();
        return e;
    }
    Node* rotate_zigzig(Node* now,int fp){//同向双旋转，，fp是指，fp是1，代表操作右的右，0代表操作左的左
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[fp],pe=now->son[fp];//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
        linkNode(now,pe->son[1-fp],fp);
        linkNode(pe,e->son[1-fp],fp);
        linkNode(e,pe,1-fp);
        linkNode(pe,now,1-fp);
        now->updataSumcnt();
        pe->updataSumcnt();
        e->updataSumcnt();
        linkNode(p,e,nowfp);//更新旋转后的父亲节点
        return e;
    }
    Node* rotate_zigzag(Node* now,int fp){//异向双旋转，fp是1，代表操作右的左，0代表操作左的右
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[1-fp],pe=now->son[fp];//e是要旋转到顶的节点，pe是e的父节点，now是pe的父节点
        linkNode(now,e->son[1-fp],fp);
        linkNode(pe,e->son[fp],1-fp);
        linkNode(e,pe,fp);
        linkNode(e,now,1-fp);
        now->updataSumcnt();
        pe->updataSumcnt();
        e->updataSumcnt();
        linkNode(p,e,nowfp);//更新旋转后的父亲节点
        return e;
    }
    void topRoot(Node *node){//调整节点到根
        Node *tem,*p;
        for(tem=node;tem->parent;){
            p=tem->parent->parent;
            if(p==NULL){
                tem=rotate_zig(tem->parent,tem->getfp());
                break;
            }else if(tem->getfp()==tem->parent->getfp()){
                tem=rotate_zigzig(p,tem->getfp());
            }else{
                tem=rotate_zigzag(p,1 - tem->getfp());
            }
        }
        root=node;
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
            printf("%d ",now->val.d);
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

    //区间操作:[l,r],这里之前build的区间是[1,r+2],[2,r+1]表示原来区间,
    //getSection后root的左边就是要找的区间，可以拿来用
    void getSection(int l,int r){//区间操作:[l,r],这里之前build的区间是[1,r+2],[2,r+1]表示原来区间,
        Data data;
        data.d=l;
        findNode(data);//把l到根节点
        Node *now,*temp;
        int fp;
        for(now=root; now ;now=now->son[fp]){//找到r+2的节点，把它放在旋转在根节点右儿子
            if(now->val.d == r+2)
                break;
            fp=now->val.d > r+2 ? now->val.com : 1-now->val.com;
        }
        //printf("%d \n",now->val.d);
       // println();
        for(temp=now;temp->parent!=root;  ){
            if(temp->parent==root->son[1]){
                temp=rotate_zig(temp->parent,temp->getfp());
                break;
            }else if(temp->getfp()==temp->parent->getfp()){
                temp=rotate_zigzig(temp->parent->parent,temp->getfp());
            }else{
                temp=rotate_zigzag(temp->parent->parent,1-temp->getfp());
            }
        }
    }
};


void Splay::reversal(Node *now){//交换区间，交换以某个节点为根的所有子节点，但会破坏平衡树结构
    if(now){
        Node *left=now->son[0];
        linkNode(now,now->son[1],0);
        linkNode(now,left,1);
        now->val.com=1-now->val.com;
        reversal(now->son[0]);
        reversal(now->son[1]);
    }
}


int main(int argc,char *argv[]){
   // freopen("in2.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("myout.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int id,k,T;
    Node *e;
    scanf("%d",&T);
    Splay *t=new Splay();
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

