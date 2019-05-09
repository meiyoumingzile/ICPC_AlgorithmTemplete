#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
#define ll long long
const int MAX=1000010;
const int mod=1e9+7;
int N,M;
ll fac[2*MAX];
ll ca[MAX];
void getFac(ll m){
    fac[0]=1;
    for(ll i=1;i<m;i++){
        fac[i]=fac[i-1]*i%mod;
    }
}

ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

ll Catalan(ll n,ll m){//卡特兰矩阵
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
    ll ans,i,j,n,m;
    getFac(2*MAX);
    //getCa(MAX);
    while(~scanf("%lld%lld",&n,&m)){
        printf("%lld\n", Catalan(n,m));
    }
return 0;
}
