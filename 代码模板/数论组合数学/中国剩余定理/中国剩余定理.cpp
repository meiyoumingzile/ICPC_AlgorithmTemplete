#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
ll A[50],P[50];
ll quickmi(ll a,ll b,ll mod){//快速幂
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

int main(int argc,char *argv[]){
    int N,i;
    cin>>N;
    ll M=1,mi,inv,ans=0,ansi;
    for(i=0;i<N;i++){//P[i]是模数，A[i]是结果，X%P[i]==A[i]
        scanf("%lld%lld",&P[i],&A[i]);
        M*=P[i];
    }
    for(i=0;i<N;i++){
        mi=M/P[i];
        mi%=M;
        inv=quickmi(mi,P[i]-2,P[i]);
        ansi=A[i]%M*mi%M*inv%M;
        ans=(ans+ansi)%M;
    }
    printf("%lld\n",ans);
return 0;
}
