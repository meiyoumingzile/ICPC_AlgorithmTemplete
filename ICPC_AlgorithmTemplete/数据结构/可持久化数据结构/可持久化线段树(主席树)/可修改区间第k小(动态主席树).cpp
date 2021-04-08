#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
/*
未在节点保存端点，而是放在递归函数里(记作tl,tr)来节省空间
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{//动态持久化化线段树
    int size,rlen,up;
    int root[MAX];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX<<5];
    int BITtree[MAX];
    //树状数组节点,维护root[]数组,而root[]代表根节点集合的地址，所以BITtree[i]代表在树状数组编号为i的节点对应到主席树中的根节点的地址
    int path[MAX];//path[i]代表在树状数组编号为i的节点对应到主席树中的根节点的地址
    int lowbit(int x){
        return x&(-x);
    }

    void init(int n){//建立一刻空的主席树
        size=rlen=1;
        root[0]=__init(0,n);
        up=n;
        memset(BITtree,0,sizeof BITtree);
    }
    int __init(int l,int r){
        int now=size++,mid=(l+r)/2;
        tree[now].sum=0;
        if(r-l>1){
            tree[now].son[0]=__init(l,mid);
            tree[now].son[1]=__init(mid, r);
        }
        return now;
    }
    void BIT_insert(int BITx,int n,int pos,int val){
        //对线段树进行可持久化添加，沿着树状数组的路径，BITx是树状数组节点号，n是树状数组节点个数，pos是位置，val是增量
        for(int i=BITx;i<=n;i+=lowbit(i))//i要大于0
            BITtree[i]+=__insert(BITtree[i],0,up,pos,val);//持久化插入，但不更新版本
    }
    void insert(int x,int cnt=1){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        root[rlen++]=__insert(root[rlen-1],0,up,x,cnt);//更新版本
    }
    int __insert(int other,int tl,int tr,int x,int cnt){//单点修改,在other版本的树的基础上的x位置加1,x是离散化之后的数值
        int now=size++;
        Node &t=tree[now];//t去引用tree[now]，以后t就是tree[now]
        t=tree[other];//把历史版本的一个复制给tree[now]
        t.sum+=cnt;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//节点编号在左边，往右找
                t.son[0]=__insert(tree[other].son[0],tl,mid,x,cnt);
            }else{//节点编号在右边，往右找
                t.son[1]=__insert(tree[other].son[1],mid,tr,x,cnt);
            }
        }
        return now;
    }
    int searchKi(int root1,int root2,int tl,int tr,int k){//查询区间第k小，非递归查询
        if (tr-tl<=1)//是叶子结点
            return tl;
       /* auto getLeftSum=[](int now){//得到当前节点做节点的sum值
            int ans=0;
            for(int i=now;i>0;i-=lowbit(i))//i要大于0
                ans+=this->BITtree[i];
            return ans;

        };*/
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return searchKi(tl1,tl2,tl,mid,k);
        else
            return searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
    }
};
PersistentLineTree tr;

struct v2{
    int x,y,k;
};
v2 question[MAX];
int A[MAX*2];//输入序列


struct DataCompress{//数据压缩类
    int *toval;
    int up;
    int compress(int *A,int n){//返回离散化后个数
        int i,k=1,t;
        toval=new int[n];
        for(i=0;i<n;i++){
            toval[i]=A[i];
        }
        sort(toval,toval+n);
        t=toval[0];
        for(i=1;i<n;i++){
            if(toval[i]!=t){
                t=toval[i];
                toval[k++]=toval[i];
            }
        }
        up=k;
        return k;
    }
    int ind(int x){//压缩数据变为真实数据
        return lower_bound(toval,toval+up,x)-toval;//调用二分查找函数，x是离散化后的数据，也可以用map实现。
    }
};
DataCompress data;//数据压缩类

int main(){
    char kind;
	int i,l,r,k,n,m,up,ans,x;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
	up=n;
	for(i=0;i<m;i++){
        getchar();
        scanf("%c",&kind);//l和r从1开始
        if(kind=='Q'){
            scanf("%d%d%d",&question[i].x,&question[i].y,&question[i].k);//l和r从1开始
        }else if(kind=='C'){
            scanf("%d%d",&question[i].x,&question[i].y);
            question[i].k=-1;//y是-1代表修改
            A[up++]=question[i].y;
        }
    }
    up=data.compress(A,up);
    //以上树输入和离散化，下面开始建动态时持久化线段树

    tr.init(up);
    for(i=0;i<n;i++){
        tr.insert(0,data.ind(A[i]));
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
            printf("%d\n",data.toval[ans]);
        }else{
            tr.insert(x,-1);
            A[question[i].x]=question[i].y;
            x=data.ind(question[i].y);//调用二分查找函数，x是离散化后的数据
            tr.insert(x);
        }
    }
return 0;
}
