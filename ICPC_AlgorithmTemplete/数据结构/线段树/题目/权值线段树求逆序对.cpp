#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

struct v2{
    int x,i;
};
v2 A[MAX];
bool cmp1(const v2 &a,const v2 &b){
    return a.x<b.x;
}
bool cmp2(const v2 &a,const v2 &b){
    return a.i<b.i;
}


struct Node{
    int l,r,sum;
};
Node tree[MAX*4];
void buildTree(int now,int l,int r){
    Node &t=tree[now];
    t.l=l;
    t.r=r;
    t.sum=0;
    if(r==l+1){
        return;
    }
    int mid=(l+r)>>1;
    buildTree(now*2,l,mid);
    buildTree(now*2+1,mid,r);
}
void update(int now,int l,int a){
    Node &t=tree[now];
    if(t.l==l&&t.r==l+1){
        t.sum+=a;
    }else{
        int mid=(t.l+t.r)>>1;
        if(mid<=l){
            update(now*2+1,l,a);
        }else{
            update(now<<1,l,a);
        }
        t.sum=tree[now*2].sum+tree[now*2+1].sum;
    }
}
int searchSum(int now,int l,int r){
    Node &t=tree[now];
    if(t.r==r&&t.l==l){
        return t.sum;
    }else{
        int mid=(t.l+t.r)>>1;
        if(mid>=r){
            return searchSum(now<<1,l,r);
        }else if(mid<=l){
            return searchSum(now*2+1,l,r);
        }else{
            return searchSum(now*2+1,mid,r)+searchSum(now<<1,l,mid);
        }
    }
}
void clear(){
    memset(tree,0,sizeof(tree));
}
void compress(v2 *A,int n){//压缩
    rg int i,k=A[0].x;
    A[0].x=0;
    for(i=1;i<n;i++){
        if(A[i].x==k){
            k=A[i].x;
            A[i].x=A[i-1].x;
        }else{
            k=A[i].x;
            A[i].x=A[i-1].x+1;
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T,n;
	ll ans;
	while(~scanf("%d",&n)){
        clear();
        buildTree(1,0,n);
        for(i=0;i<n;i++){
            scanf("%d",&A[i].x);
            A[i].i=i;
        }
        sort(A,A+n,cmp1);
        compress(A,n);
        sort(A,A+n,cmp2);
        for(i=ans=0;i<n;i++){
            update(1,A[i].x,1);
            ans+=i-searchSum(1,0,A[i].x+1)+1;//大于A[i]的数个数
        }
        printf("%lld\n",ans);
	}

return 0;
}

