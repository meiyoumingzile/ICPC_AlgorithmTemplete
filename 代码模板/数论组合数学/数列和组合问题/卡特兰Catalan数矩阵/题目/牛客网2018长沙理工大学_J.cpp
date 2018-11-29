#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=3000010;
const int mod=1e9+7;

ll fac[MAX];
ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

ll Catalan(ll n,ll m){
    ll ans=0;
    if(n>=m&&n>=0&&m>=0){
        ll inv=quickmi(fac[m]*fac[n+1]%mod,mod-2,mod);
        ans=fac[m+n]*(n-m+1)%mod;
        ans=ans*inv%mod;
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll n,m,i,j,k,ans,T,cat;
    fac[0]=1;
    for(i=1;i<MAX;i++){
        fac[i]=fac[i-1]*i%mod;
    }
    cin>>T;
    while(T--){
        scanf("%lld%lld%lld",&n,&m,&k);
        ans=Catalan(m-1,m-k)*Catalan(n-m+k,n-m)%mod;

        printf("%lld\n",ans%mod);
    }
return 0;
}

