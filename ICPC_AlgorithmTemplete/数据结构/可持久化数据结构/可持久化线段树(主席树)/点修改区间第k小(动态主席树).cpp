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
struct PersistentLineTree{
    int size,rlen;
    int root[MAX];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX<<5];
    int lowbit(int x){
        return x&(-x);
    }
    int getsum(int x){//得到前缀和
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//i要大于0
                ans+=BITtree[i];
        }
        return ans;
    }
    void build(int l,int r){
        size=rlen=1;
        root[0]=__build(l,r);
        memset(BITtree,0,sizeof BITtree);
    }
    int __build(int l,int r){
        int now=size++,mid=(l+r)/2;
        tree[now].sum=0;
        if(r-l>1){
            tree[now].son[0]=__build(l,mid);
            tree[now].son[1]=__build(mid, r);
        }
        return now;
    }
    void insert(int tl,int tr,int x,int cnt=1){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        int last=root[rlen-1];
        for(int i=x;i<=n;i+=lowbit(i)){
            root[rlen++]=__insert(last,tl,tr,x,cnt);
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
    int searchKi(int root1,int root2,int tl,int tr,int k){//查询区间第k小，用法见文档
        if (tr-tl<=1)//是叶子结点
            return tl;
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

int toval[MAX*2],A[MAX*2];
int compress(int *A,int n){//返回离散化后个数
    int i,k=1,t;
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
    return k;
}


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
    up=compress(A,up);
    tr.build(0,up);
    for(i=0;i<n;i++){
        x=lower_bound(toval,toval+up,A[i])-toval;//调用二分查找函数，x是离散化后的数据，也可以用map
        tr.insert(0,up,x);
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
            printf("%d\n",toval[ans]);
        }else{
            tr.insert(0,up,x,-1);
            A[question[i].x]=question[i].y;
            x=lower_bound(toval,toval+up,question[i].y)-toval;//调用二分查找函数，x是离散化后的数据
            tr.insert(0,up,x);
        }
    }
return 0;
}
