#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=20000010;


int a[MAX],A[MAX];
void solve(cint n,cint m){
    rg int i,j,t,f,b;
    ll ans1=0,ans2=0;
    f=MAX/2;
    b=f+1;
    t=n-m+1;
    for(i=n;i>t;i--){
        while(f>=b&&A[a[b]]<=A[i]){
            b++;
        }
        a[--b]=i;
        while(a[f]-i>=m){
            f--;
        }
    }
    for(i=t;i>0;i--){
        while(f>=b&&A[a[b]]<=A[i]){
            b++;
        }
        a[--b]=i;
        while(a[f]-i>=m){
            f--;
        }
        ans1+=A[a[f]]^i;
        ans2+=(f-b+1)^i;
    }
    printf("%lld %lld\n",ans1,ans2);
}

inline void scan(int &x){//快读
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,k,T,n,m,p,q,r,mod;
	scanf("%d",&T);
	while(T--){
        scan(n);scan(m);scan(k);scan(p);scan(q);scan(r);scan(mod);
        for(i=1;i<=k;i++){
            scan(A[i]);
        }
        for(i=k+1;i<=n;i++){
            A[i] = ((ll)p*A[i-1]%mod+(ll)q*i%mod+r%mod)%mod;
        }
        solve(n,m);
	}
return 0;
}

