#include<bits/stdc++.h>
//#include<windows.h>
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
ll fac[MAX],inv[MAX],facinv[MAX];
void getFac(ll m,cll p){//别忘了初始化阶乘
    fac[1]=inv[1]=facinv[1]=1;
    for(ll i=2;i<m;i++){
        fac[i]=fac[i-1]*i%p;
        inv[i]=(p-p/i)*inv[p%i]%p;
        facinv[i]=inv[i]*facinv[i-1]%p;
    }
}
ll quickmi(ll a,ll b,const ll &mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll miCC(cll n,cll m,cll mod){//计算C(n,m)//mod>n>=m
    if(m==0||m==n)
        return 1;
    return fac[n]*quickmi(fac[m]*fac[n-m]%mod,mod-2,mod)%mod;
}
ll CC(cll n,cll m,cll mod){//计算C(n,m)//mod>n>=m
    if(m==0||m==n)
        return 1;
    return fac[n]*facinv[m]%mod*facinv[n-m]%mod;
}
ll lucasCC(cll n,cll m,cll mod){
    if(n<mod&&m<mod)
        return CC(n,m,mod);
    return lucasCC(n/mod,m/mod,mod)*lucasCC(n%mod,m%mod,mod)%mod;
}
int main(int argc,char *argv[]){
    ll n,m,T,p;
    cin>>T;
    while(T--){//求CC(n+m,m,p)
        scanf("%lld%lld%lld",&n,&m,&p);
        getFac(n+m+1,p);
        printf("%lld\n",lucasCC(n+m,m,p));
    }
return 0;
}
