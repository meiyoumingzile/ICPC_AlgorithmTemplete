#include<bits/stdc++.h>
#define ll long long
const int MAX=110;

struct PRIME{
    const int MT=5;
    bool vis[MAX];
    int prime[MAX];
    int pCount;
    int init(int n){
        memset(vis,1,sizeof(vis));
        int i,j,primeCount=0;
        for(i=2;i<n;i++){
            if(vis[i]){
                prime[primeCount++]=i;
            }
            for(j=0;i*prime[j]<n;j++){
                vis[i*prime[j]]=false;
                if(i%prime[j]==0){
                    break;
                }
            }
        }
        pCount=primeCount;
        return primeCount;
    }
ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod){
        if(b&1)
            ans=ans*a%mod;
    }
    return ans;
}
    int TwiceDetect(ll a, ll b, ll k) {
        int t = 0;
        ll x, y;
        while ((b & 1) == 0) {
            b >>= 1;
            t++;
        }
        y = x = quickmi(a, b, k);
        while (t--) {
            y =x*x%k;
            if (y == 1 && x != 1 && x != k - 1)///注意y!=1的时候是不做判断的,即对应
                return 0;///递归时在某一环节x==p-1的情况,对此x开方则无意义,但是迭代的话不能break,只能ignore并继续.
            x = y;///继续向高次迭代,那么至少最后一次应该是等于1的(Fermat小定理)
        }
        return y;
    }

    int isPrime(ll n) {
        if(n<=1){
            return -1;
        }else if(n&1==0){
            return 0;
        }
        int i;
        ll tmp;
        for (i=0;i<MT;i++){//测试次数
            tmp=prime[i];
            if(n==prime[i]) return 1;
            if(TwiceDetect(tmp, n - 1, n) != 1)
                break;
        }
        return (i == MT);
    }
};
PRIME pr;//一定要声明全局的

int getEu(int N){//¸ù¾Ý¹«Ê½
    if(N==1){
        return 1;
    }else if(pr.isPrime(N)==1){
        return N-1;
    }
    int i,j,n=N,ans=N,m=1;
    for(i=2;n!=1;i++){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            ans/=i;
            m*=i-1;
        }
    }
    if(ans==N){
        return N-1;
    }

    return ans*m;
}

ll fac(ll n){
    ll i,sum=0,k,ans=0;
    ll sqrtn=(ll)sqrt(n);

    for(i=1;i<sqrtn;i++){
        if(n%i==0){
            ans++;
            k=n/i;
            sum+=i*getEu(k);
            sum+=k*getEu(i);
        }
    }

    if(sqrtn*sqrtn==n){
        sum+=sqrtn*getEu(sqrtn);
    }else{
        if(n%i==0){
            sum+=i*getEu(n/i);
            sum+=n/i*getEu(i);
        }
    }
    return sum;
}

int main(){
    pr.init(100);
    ll i,j,n,a,b;
    while(~scanf("%lld",&n)){
        printf("%lld\n",fac(n));
    }
return 0;
}
