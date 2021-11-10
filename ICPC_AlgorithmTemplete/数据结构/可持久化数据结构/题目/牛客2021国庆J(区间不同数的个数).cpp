#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=200010;
const int mod=1e9+7;
inline void scan(int &x){
    char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}


/*
未在节点保存端点，而是放在递归函数里(记作tl,tr)来节省空间
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen,up;
    int root[MAX*3];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX<<6];
    void init(int n){
        size=rlen=1;
        root[0]=__init(0,n);
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
    void insert(int tl,int tr,int x,int ad=1){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        int last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x,ad);
    }
    int __insert(int other,int tl,int tr, int x,int ad){//单点插入,在other版本的树的基础上的x位置加1,x是离散化之后的数值
        int now=size++;
        Node &t=tree[now];//t去引用tree[now]，以后t就是tree[now]
        t=tree[other];//把历史版本的一个复制给tree[now]
        t.sum+=ad;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//节点编号在左边，往右找
                t.son[0]=__insert(tree[other].son[0],tl,mid,x,ad);
            }else{//节点编号在右边，往右找
                t.son[1]=__insert(tree[other].son[1],mid,tr,x,ad);
            }
        }
        return now;
    }
    int getSum(int other,int l,int r,int tl,int tr){//查询区间other版本[l,r]的和
        return __getSum(root[other],l,r,tl,tr);
    }
    int __getSum(int now,int l,int r,int tl,int tr){//查询区间第k小，用法见文档
        Node &t=tree[now];//t去引用tree[other]，以后t就是tree[other]
        if(l==tl&&r==tr){
            return t.sum;
        }
        int mid=(tl+tr)/2;
        if(r<=mid){
            return __getSum(t.son[0],l,r,tl,mid);
        }else if(l>=mid){
            return __getSum(t.son[1],l,r,mid,tr);
        }else{
            return __getSum(t.son[0],l,mid,tl,mid)+__getSum(t.son[1],mid,r,mid,tr);
        }
    }
    void print(int other,int tl,int tr){
        __print(root[other],tl,tr);
        printf("\n");
    }
    void __print(int now,int tl,int tr){
        Node &t=tree[now];//t去引用tree[other]，以后t就是tree[other]
        printf("(%d~%d %d)",tl,tr,t.sum);
        int mid=(tl+tr)/2;
        if(tr-tl>1){
            __print(t.son[0],tl,mid);
            __print(t.son[1],mid,tr);
        }
    }
};
PersistentLineTree tr;

int ind[MAX],A[MAX],version[MAX];
int main(int argc,char *argv[]){
	int i,j,t,n,m,a,ans,l,r;
	while(~scanf("%d%d",&n,&m)){
        memset(ind,-1,sizeof(ind));
        for(i=0;i<n;i++){
            scan(A[i]);
            A[i+n]=A[i];
        }
        n*=2;
        tr.init(n);
        for(i=0;i<n;i++){
            tr.insert(0,n,i,1);
            if(ind[A[i]]>-1){//在最新版本修改
                tr.insert(0,n,ind[A[i]],-1);
            }
            version[i]=tr.rlen-1;
            ind[A[i]]=i;
        }
        for(i=0;i<m;i++){
            scan(l);
            scan(r);
            t=l;
            l=r;
            r=t+n/2;
            ans=tr.getSum(version[r-1],0,r,0,n)-tr.getSum(version[r-1],0,l-1,0,n);
            printf("%d\n",ans);
        }
	}

return 0;
}
/*
6 8
1 2 3 4 3 5
1 2
3 5
2 6
1 1
2 2
3 3
4 4
1 5
*/
