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
struct Node{//主席树不维护左右区间
    int sum,son[2];
};
struct enduringLineTree{
    int size,rlen;
    int root[MAX];//表示根节点集合，root[0]代表最原始的数
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
    void insert(int l,int r,int x){//单点修改，l r一般是[0,up),因为l r代表线段树的左右端点
        int p=root[rlen-1];
        root[rlen++]=__insert(p,l,r,x);
    }
    int __insert(int b,int l,int r, int x){//单点修改,权值线段树插入x,x是离散化之后的数值
        int now=size++;//造一一个新节点
        Node &t=tree[now];
        t=tree[b];
        t.sum++;
        if(r-l>1){
            int mid=(l+r)/2;
            if(x<mid){//节点编号在左边，往右找
                t.son[0]=__insert(tree[b].son[0],l,mid,x);
            }else{//节点编号在右边，往右找
                t.son[1]=__insert(tree[b].son[1],mid,r,x);
            }
        }
        return now;
    }
    int searchKi(int root1,int root2,int l,int r,int k){//查询区间分别查询数root1和root2，l和r代表线段树左右端点。
        if (r-l<=1)//是叶子结点
            return l;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(l+r)/2;
        if(x>=k)
            return searchKi(tl1,tl2,l,mid,k);
        else
            return searchKi(tree[root1].son[1],tree[root2].son[1],mid,r,k-x);
    }
};
enduringLineTree tr;
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
    up=discrete(A,disA,n);
    tr.build(0,up);
    for(i=0;i<n;i++){
        tr.insert(0,up,disA[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&l,&r,&k);//l和r从1开始
        ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
        printf("%d\n",A[ans].x);
    }
return 0;
}
