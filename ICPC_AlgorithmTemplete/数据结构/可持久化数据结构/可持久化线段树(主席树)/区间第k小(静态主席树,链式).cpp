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
struct Node{//
    int sum=0;
    Node *son[2];
    Node* clone(){
        Node* now=new Node();
        now->sum=sum;
        now->son[0]=son[0];
        now->son[1]=son[1];
        return now;
    }
};
struct PersistentLineTree{
    int rlen=0;//root数组长度
    Node* root[MAX];//表示根节点集合，root[0]代表最原始的树
    void build(int l,int r){//建一颗空树，所有位置是0
        rlen=0;
        root[rlen++]=__build(l,r);
    }
    Node* __build(int l,int r){//建一颗空树，所有位置是0
        int mid=(l+r)/2;
        Node *now=new Node();
        if(r-l>1){
            now->son[0]=__build(l,mid);
            now->son[1]=__build(mid, r);
        }
        return now;
    }
    void insert(int tl,int tr,int x){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        Node *last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x);
    }
    Node* __insert(Node* other,int tl,int tr, int x){//单点修改,在other版本的树的基础上的x位置加1,x是离散化之后的数值
        Node *now=other->clone();//造一一个新节点,和other的这个位置的节点相同
        now->sum++;//增加一个
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//节点编号在左边，往右找
                now->son[0]=__insert(other->son[0],tl,mid,x);
            }else{//节点编号在右边，往右找
                now->son[1]=__insert(other->son[1],mid,tr,x);
            }
        }
        return now;
    }
    int searchKi(Node* root1,Node* root2,int tl,int tr,int k){//查询区间第k小，用法见文档
        if (tr-tl<=1)//是叶子结点
            return tl;
        Node* tl1=root1->son[0];
        Node* tl2=root2->son[0];
        int x=tl2->sum - tl1->sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return searchKi(tl1,tl2,tl,mid,k);
        else
            return searchKi(root1->son[1],root2->son[1],mid,tr,k-x);
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
