#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=20100403;
int N,M;
ll fac[2*MAX];
void getFac(ll m){
    fac[1]=1;
    for(ll i=2;i<m;i++){
        fac[i]=fac[i-1]*i%mod;
    }
}

void exgcd(LL  a,LL  b,LL & d,LL & x,LL & y){//求逆元
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

LL  inv(LL  a, LL  p){//返回逆元
    LL  d, x, y;
    exgcd(a, p, d, x, y);
    return d == 1 ? (x+p)%p : -1;
}

ll dfs(int n,int m){
    if(n==0&&m==0){
        return 1;
    }
    if(m>n){
        return 0;
    }
    ll ans=0;
    if(n){
        ans+=dfs(n-1,m);
    }
    if(m){
        ans+=dfs(n,m-1);
    }
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll ans,i,j,k,ac;
    getFac(2*MAX);
    //getCa(MAX);
    while(~scanf("%d%d",&N,&M)){
        //ac=dfs(N,M);
        ans=0;
        if(M<=N){
            k=N-M+1;
            ans=k*fac[N+M]%mod;
            k=fac[M]*fac[N+1]%mod;
            ans=ans*inv(k,mod)%mod;
        }
        printf("%lld\n",ans);
    }
return 0;
}
