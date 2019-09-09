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
struct PersistentLineTree{
    int size,rlen,up;
    int root[MAX];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX<<5];
    void build(int l,int r){
        size=rlen=1;
        root[0]=__build(l,r);
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
    void insert(int tl,int tr,int x){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        int last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x);
    }
    int __insert(int other,int tl,int tr, int x){//单点修改,在other版本的树的基础上的x位置加1,x是离散化之后的数值
        int now=size++;
        Node &t=tree[now];//t去引用tree[now]，以后t就是tree[now]
        t=tree[other];//把历史版本的一个复制给tree[now]
        t.sum++;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//节点编号在左边，往右找
                t.son[0]=__insert(tree[other].son[0],tl,mid,x);
            }else{//节点编号在右边，往右找
                t.son[1]=__insert(tree[other].son[1],mid,tr,x);
            }
        }
        return now;
    }
    int searchKi(int l,int r,int tl,int tr,int k){//查询区间[l,r]的第k小
        return __searchKi(root[l-1],root[r],tl,tr,k);
    }
    int __searchKi(int root1,int root2,int tl,int tr,int k){//查询区间第k小，用法见文档
        if (tr-tl<=1)//是叶子结点
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return __searchKi(tl1,tl2,tl,mid,k);
        else
            return __searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
    }
};
PersistentLineTree tr;
struct v2{
    int x,y;
};
v2 A[MAX];
int disA[MAX];//离散化之后的原数组
int discrete(v2 *A,int *disA,int n){//离散化
    sort(A,A+n,[](const v2 &a,const v2 &b){
         return a.x<b.x;
    });
    int k=0;
    disA[A[0].y]=k;
    for(int i=1;i<n;i++){
        k+=A[i].x!=A[i-1].x;
        disA[A[i].y]=k;
        A[k]=A[i];
    }
    return k+1;
}
int main(){
	int i,l,r,k,n,m,up,ans;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i].x);
        A[i].y=i;
	}
    tr.up=discrete(A,disA,n);
    tr.build(0,tr.up);
    for(i=0;i<n;i++){
        tr.insert(0,up,disA[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&l,&r,&k);//l和r从1开始
        ans=tr.searchKi(l,r,0,up,k);
        printf("%d\n",A[ans].x);
    }
return 0;
}
