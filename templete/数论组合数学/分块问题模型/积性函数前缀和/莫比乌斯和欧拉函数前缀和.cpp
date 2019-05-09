#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
ll prime[MAX],mob[MAX],cnt,sum[MAX];
bool vis[MAX];
void init(int n){
    ll i,j;
    cnt=0;
    memset(vis,0,sizeof vis);
    memset(mob,0,sizeof mob);
    mob[1]=sum[1]=1;
    for(i=2;i<n;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            mob[i]=-1;
        }
        for(j=0;j<cnt&&i*prime[j]<n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]){
                mob[i*prime[j]]=-mob[i];
            }else{
                mob[i*prime[j]]=0;
                break;
            }
        }
    }
    for(i=2;i<n;i++)
        sum[i]=sum[i-1]+mob[i];
}
ll ind[MAX];
inline ll block(ll n,int d){//d是n/d的d
    if(n<=1e6) return sum[n];
    if(vis[d]) return ind[d];
    ll i,sqrtn=sqrt(n),ans=0,k,pre=n;
    for(i=2;i<=sqrtn;i++){//求n/i和i∈[2,n]
        k=n/i;
        ans+=block(k,d*i);
        ans+=(pre-k)*sum[i-1];//一定小于1e6
        pre=k;
    }
    ans+=(pre-sqrtn)*sum[sqrtn];//一定小于1e6
    ind[d]=1-ans;
    vis[d]=1;
    return ind[d];
}
ll getMob(ll n){
    return block(n,1);
}
ll getPhi(ll n){//莫比乌斯反演求得公式是sum(mob[i]*(n/i)^2)/2+1
    ll i,sqrtn=sqrt(n),ans=mob[1]*n*n,k,pre=n;
    for(i=2;i<=sqrtn;i++){
        k=n/i;
        ans+=k*k*mob[i];
        ans+=(i-1)*(i-1)*(block(pre,i-1)-block(k,i));
        pre=k;
    }
    ans+=sqrtn*sqrtn*(block(pre,sqrtn)-sum[sqrtn]);
    return ans/2+1;
}
int main(int argc,char *argv[]){
	ll T,n,m,s1,s2;
	init(1e6+1);
	cin>>T;
	while(T--){
        scanf("%lld",&n);
        memset(vis,0,sizeof(vis));
        printf("%lld %lld\n",getPhi(n),getMob(n));
	}
return 0;
}

