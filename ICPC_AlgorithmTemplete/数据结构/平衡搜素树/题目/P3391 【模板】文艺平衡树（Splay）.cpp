#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
int N;

struct Data{
    int d,a;//d代表排名，用来查找，a代表实际值，交换左右子树就是交换a；
    int cnt=1;//该节点出现次数
    int sumcnt=0;//儿子节点数的总个数，会把相同的算进去
    bool lazy=0;//是否交换子树，1代表交换
    void init(int d,int a){
        this->d=d;
        this->a=a;
    }
};

struct Node{
    Node *p; //该结点的父节点，方便操作
    Node *son[2];//son[0]代表左，son[1]代表右
    Data val; //结点值
    Node(){
        p=son[0]=son[1]=NULL;
    }
    Node(Data val){
        p=son[0]=son[1]=NULL;
        this->val=val;
    }
    Node* getFindSon(Data &other){//返回查找要走哪个方向根据com
        if(val.d==other.d)
            return this;
        int fp= val.d < other.d ? 1 : 0;
        return son[fp];
    }
    int getfp(){//返回当前节点是父节点的哪个儿子，左返回0，右返回1，没有父节点返回-1
        if(p==NULL)
            return -1;
        return p->son[0]==this?0:1;
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
        for(Node *now=p;now;now=now->p)
            now->val.sumcnt+=k;
    }
    int getSonSum(int fp){//返回当前节点左边或右边的点，的数量总和
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
};

struct Splay{
    int ind[MAX];//代表a对应的d值
    void reversal(Node *now);
    void myprint(Node *now);
    Node *root=NULL;//原始节点，左边才是真正的根

    void linkNode(Node *now,Node *nex,int fp){//fp 0代表左，1代表右
        if(now&&fp!=-1)
            now->son[fp]=nex;
        if(nex)
            nex->p=now;
    }
    void pushdown(Node *now){
        if(now&&now->val.lazy==1){
            now->val.lazy=0;
            if(now->son[0]){
                now->son[0]->val.lazy^=1;
                ind[now->son[0]->val.a]=now->son[0]->val.d;
            }
            if(now->son[1]){
                ind[now->son[1]->val.a]=now->son[1]->val.d;
                now->son[1]->val.lazy^=1;
            }
            if(now->son[0]&&now->son[1])
                swap(now->son[0]->val.a,now->son[1]->val.a);
        }
    }
    void pushdown(Node *now,Data &other){//携带数据比较的下方，用于查找
        pushdown(now);
        other.d=ind[other.a];
    }

    void build(int n){//建一个a属于[1,n]的树，节点数是2*n+1,多余节点a是0;
        Data data;
        data.init(2,1);
        ind[1]=2;
        root=new Node(data);
        Node *now=root,*node;
        int i;
        for(i=2;i<=n+1;i++,now=now->son[1]){//插入点,
            data.init(now->val.d+2,i);
            ind[i]=now->val.d+2;
            node=new Node(data);
            linkNode(now,node,1);
            data.init(now->val.d-1,0);
            node=new Node(data);
            linkNode(now,node,0);
        }
        for(i=1,now=now->p;now;now=now->p){//更新sumcnt
            now->updataSumcnt();
        }
    }

    void insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    void insertNode(Node *node){//插入按照d寻找
        Node *now=root;//初始G的d是无限大
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->p=now;
            now=now->getFindSon(node->val);
        }
        if(now!=root){
            linkNode(node->p,node,fp);
            node->updataSumcnt(1);
        }else{
            root=node;
        }
    }

    Node *findNode(Data val){//同BST树
        Node *nex;
        for(Node *now=root; now ;){
            pushdown(now,val);
            nex=now->getFindSon(val);
            if(nex==now)
                return now;
            now=nex;
        }
        return NULL;
    }

    Node* rotate_zig(Node *now,int fp){//now是以哪个节点为根，fp是要转now的左边还是右边
        Node *p=now->p;
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
        Node *e,*pe, *p=now->p;
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
        Node *e,*pe, *p=now->p;
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
        Node *temp,*p,*pp;
        for(temp=node;temp->p;){
            p=temp->p;
            pp=p->p;
            if(p==root){
                temp=rotate_zig(p,temp->getfp());
                break;
            }else if(temp->getfp()==p->getfp()){
                temp=rotate_zigzig(pp,temp->getfp());
            }else{
                temp=rotate_zigzag(pp,1 - temp->getfp());
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
                linkNode(temp->p,temp->son[0],1);
            }
            temp->updataSumcnt(- now->val.cnt);
            now->updataSumcnt();
            now->updataSumcnt(now->val.cnt-1);
        }else{
            int fp=now->son[0]?0:1;
            if(now==root){
                root=now->son[fp];
                if(root)
                    root->p=NULL;
            }else{
                linkNode(now->p,now->son[fp],now->getfp());
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
            sum+=now->getSonSum(fp);
        for(;now!=root;now=now->p){
            if(now->getfp()!=fp){//是根或者右边才可以算
                sum+=now->p->val.cnt+now->p->getSonSum(fp);
            }
        }
        return sum;
    }
    Node *findRankNode(int x,int fp){//返回节点的D指针，fp=0(第K小的数),fp=1(第K大的数),
        int fp1,pr=0,r=root->getSonSum(fp)+1;
        Node *now=root,*last=NULL;
        while(1){
            if(x==r)
                return now;
            fp1=x>r?1-fp:fp;
            if(now->son[fp1]==NULL){
                for(now;fp1==fp&&now;now=now->p)
                    fp1=now->getfp();
                return now;
            }
            now=now->son[fp1];
            if(fp1!=fp){
                pr=r;
                last=now->p;
                r=pr +  now->getSonSum(fp) + now->p->val.cnt;
            }else{
                r=pr+now->getSonSum(fp);
                r+=last==NULL?1:last->val.cnt;
            }
        }
    }
    Node *getAdjoin(Node *now,int fp){//返回指针,找不到返回NULL，条件是now在数里存在，fp==0表示小于now的最大数，fp==1表示大于now的最小数
        Node *e=now->son[fp];
        if(e){
            for(;e->son[1-fp];e=e->son[1-fp]);
        }else{
            for(e=now;e->getfp()==fp;e=e->p);//没有fp方向上的子节点的情况下，向上找一个一个找
            e=e->p;
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
            for(now=last;now!=root&&now->getfp()==fp;now=now->p);
            if(now!=root)
                return now->p;
            return NULL;
        }else{
            return last;
        }
    }

    //区间操作:[l,r],这里之前build的区间是[1,r+2],[2,r+1]表示原来区间,
    //getSection后root的右的左，就是要找的区间，可以拿来用
    void getSection(int l,int r){//得到区间:[l,r],算法是把l-1调到根，把r1调到根的右
        Data val;
        val.init(ind[l-1],l-1);
        findNode(val);//把l-1挪到根节点
        Node *now,*temp,*p,*pp,*nex;
        val.init(ind[r+1],r+1);
         temprint(root);
            printf("\n");
        for(now=root; now ;){//找到r+1的节点，
            pushdown(now,val);
            nex=now->getFindSon(val);
            if(nex==now)
                break;
            now=nex;
        }

        for(temp=now;temp->p!=root;  ){//r+1的节点,把它放在旋转在根节点右儿子
            p=temp->p;
            pp=p->p;

            if(p==root->son[1]){
                temp=rotate_zig(p,temp->getfp());
                break;
            }else{
                if(temp->getfp()==p->getfp())
                    temp=rotate_zigzig(pp,temp->getfp());
                else
                    temp=rotate_zigzag(pp,1 - temp->getfp());
            }

        }
        // printf("%d \n",root->son[1]->val.d);
    }

    void temprint(Node *now){
        if(now){
            printf("%d %d %d --%d\n",now->val.d,now->son[0]!=NULL?now->son[0]->val.d:0,now->son[1]!=NULL?now->son[1]->val.d:0,now->val.a);
            temprint(now->son[0]);
            temprint(now->son[1]);
        }

    }
};

void Splay::reversal(Node *now){//交换区间，交换以某个节点为根的所有子节点，但会破坏平衡树结构
    if(now){
        now->val.lazy^=1;//交换标记变更
    }
}

int id=0;
void Splay::myprint(Node *now){
    if(now){
        pushdown(now);
        myprint(now->son[0]);
        if(now->val.a>1&&now->val.a<=N+1){
            printf("%d%s",now->val.a-1,id==N-1?"\n":" ");
            id++;
        }
        myprint(now->son[1]);
    }
}
int main(int argc,char *argv[]){
    //freopen("text/my1.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("myout.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,m,l,r;
    Node *e;
    Splay *t=new Splay();
    scanf("%d%d",&N,&m);

    t->build(N+2);
    //t->println();
    for(i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        t->getSection(l+1,r+1);
        t->reversal(t->root->son[1]->son[0]);
        t->temprint(t->root);
        printf("\n");
        //id=0;
        //t->getSection(2,N+1);
       // t->myprint(t->root);
    }
    t->getSection(2,N+1);
    t->myprint(t->root);

return 0;
}
/*
5 2
1 5
2 4

6 3
1 2
5 6
2 5
*/
