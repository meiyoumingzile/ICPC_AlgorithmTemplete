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
const int MAX=200010;
const int mod=1e9+7;
/*
未在节点保存端点，而是放在递归函数里(记作tl,tr)来节省空间
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{//动态持久化化线段树
    int size,rlen,n;//n是树状数组的上限，不一定等于线段树叶子节点个数
    int root[MAX];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX<<6];
    int BITtree[MAX];//BITtree[i]代表第i颗权值线段树的根节点在root中的编号
    //树状数组节点,维护root[]数组,而root[]代表根节点集合的地址，所以BITtree[i]代表在树状数组编号为i的节点对应到主席树中的根节点的地址

    int BITpath[2][MAX];//记录树状数组的路径,查找区间第k小时候用
    int BITpath_len[2];
    int rememberBITpath(int pos,int *path){//记录路径数组
        int len=0;
        for(int i=pos;i>0;i-=lowbit(i)){
            path[len++]=root[i];
        }
        return len;
    }
    void updateBITpath(int *path,int len,int fp){//更新路径数组
        for(int i=0;i<len;i++){
            path[i]=tree[path[i]].son[fp];
        }
    }
    int getSumBITpath(int *path,int len,int fp){//树状数组查询，前pos位置的线段树中，x的出现次数
        int ans=0;
        for(int i=0;i<len;i++){
            ans+=tree[tree[path[i]].son[fp]].sum;
        }
        return ans;
    }
    int lowbit(int x){
        return x&(-x);
    }

    void init(int n,int m){//建立一刻空的主席树,n是树状数组上限，m是线段树宽度
        size=rlen=1;
        this->n=n;
        root[0]=__init(0,m);
        memset(BITtree,0,sizeof BITtree);//初始阶段树状数组为空，全都指向root[0]
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
    void insert(int pos,int x,int val,int up){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        for(int i=pos;i<=n;i+=lowbit(i)){//i要大于0
            int last=root[i];
            root[i]=__insert(root[i],0,up,x,val);//更新版本
        }
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

    int searchKi(int l,int r,int k,int up){//查询区间[l,r]的第k小，,使用树状数组的更新
        BITpath_len[0]=rememberBITpath(l,BITpath[0]);
        BITpath_len[1]=rememberBITpath(r,BITpath[1]);
        return __searchKi(root[l],root[r],0,up,k);
    }

    int __searchKi(int root1,int root2,int tl,int tr,int k){//查询区间第k小，用法见文档
        if (tr-tl<=1)//是叶子结点
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=getSumBITpath(BITpath[1],BITpath_len[1],0)-getSumBITpath(BITpath[0],BITpath_len[0],0);
        int mid=(tl+tr)/2;
        if(x>=k){
            updateBITpath(BITpath[0],BITpath_len[0],0);//更新路径数组
            updateBITpath(BITpath[1],BITpath_len[1],0);
            return __searchKi(tl1,tl2,tl,mid,k);
        }else{
            updateBITpath(BITpath[0],BITpath_len[0],1);//更新路径数组
            updateBITpath(BITpath[1],BITpath_len[1],1);
            return __searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
        }
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
    int ind(int x){//返回离散化后数据
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

    tr.init(n,up);
    for(i=0;i<n;i++){//下标[1,n]
        tr.insert(i+1,data.ind(A[i]),1,up);
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(l-1,r,k,up);
            printf("%d\n",data.toval[ans]);
        }else{
            tr.insert(question[i].x,data.ind(A[question[i].x-1]),-1,up);
            A[question[i].x-1]=question[i].y;
            tr.insert(question[i].x,data.ind(question[i].y),1,up);
        }
    }
return 0;
}
/*
5 5
25957 6405 15770 26287 26465
Q 2 2 1
Q 3 4 1
Q 4 5 1
Q 1 2 2
Q 4 4 1
*/
