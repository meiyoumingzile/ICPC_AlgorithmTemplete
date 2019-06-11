#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct BIT{
    int n;
    int tree[MAX];
    void init(int n){
        this->n=n;
        memset(tree,0,sizeof(tree));
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int y){//单点x下标增加y,x下标从1开始
        for(int i=x;i<=n;i+=lowbit(i))
            tree[i]+=y;
    }
    int getsum(int x){//得到前缀和
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//i要大于0
                ans+=tree[i];
        }
        return ans;
    }
    int getsum(int x,int y){//得到区间[x,y]的和，x，y下标从1开始
        if(x>y)
            return 0;
        return getsum(y)-getsum(x-1);
    }
};
BIT b;
int A[MAX];
int main(int argc,char *argv[]){
    int i,n,m,kind,l,r,x,last;
    while(~scanf("%d%d",&n,&m)){
        b.init(n);
        for(i=last=0;i<n;i++){//树状数组维护差分
            scanf("%d",&A[i]);
            b.add(i+1,A[i]-last);
            last=A[i];
        }
        for(i=0;i<m;i++){
            scanf("%d",&kind);
            if(kind==1){
                scanf("%d%d%d",&l,&r,&x);//下标从1开始
                b.add(l,x);
                b.add(r+1,-x);
            }else if(kind==2){
            	scanf("%d",&l);//下标从1开始
            	printf("%d\n",b.getsum(l));
            }
        }
    }
return 0;
}
