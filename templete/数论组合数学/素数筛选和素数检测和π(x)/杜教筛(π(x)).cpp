//Meisell-Lehmer
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX= 5e6 + 2;
bool vis[MAX];
int pcnt[MAX],p[MAX];
void getp(int n){
    vis[0]=vis[1]=1;
    pcnt[0]=pcnt[1]=0;
    int cnt=0;
    for(int i=2;i<n;i++){
        if(!vis[i]) p[++cnt]=i;
        pcnt[i]=cnt;
        for(int j=1;i*p[j]<n;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
const int M = 7;
const int PM = 2 * 3 * 5 * 7 * 11 * 13 * 17;
int phi[PM+1][M+1],sz[M+1];
void init(){
    getp(MAX);
    sz[0]=1;
    for(int i =0;i <=PM; ++i) phi[i][0] = i;
    for(int i =1; i<=M; ++i){
        sz[i] = p[i] * sz[i - 1];
        for(int j = 1; j <= PM; ++j)
            phi[j][i]=phi[j][i-1]-phi[j/p[i]][i-1];
    }
}
int sqrt2(ll x){
    ll r=sqrt(x);
    while(r*r<= x) r++;
    return r-1;
}
int sqrt3(ll x){
    ll r=cbrt(x);
    while(r*r*r<= x)r++;
    return r-1;
}
ll getphi(ll x,int s){
    if(s == 0) return x;
    if(s <= M) return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];
    if(x <= p[s]*p[s]) return pcnt[x] - s + 1;
    if(x <= p[s]*p[s]*p[s] && x < MAX){
        int s2x = pcnt[sqrt2(x)];
        ll ans = pcnt[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
        for(int i = s + 1; i <= s2x; ++i) ans += pcnt[x / p[i]];
        return ans;
    }
    return getphi(x,s-1)-getphi(x/p[s],s-1);
}
ll getpcnt(ll x){
    if(x < MAX)return pcnt[x];
    ll ans = getphi(x, pcnt[sqrt3(x)]) + pcnt[sqrt3(x)] - 1;
    for(int i=pcnt[sqrt3(x)]+1,ed = pcnt[sqrt2(x)];i<=ed;++i)
        ans-=getpcnt(x/p[i])-i+1;
    return ans;
}
ll lehmer_pcnt(ll x){
    if(x < MAX)  return pcnt[x];
    int a = (int)lehmer_pcnt(sqrt2(sqrt2(x)));
    int b = (int)lehmer_pcnt(sqrt2(x));
    int c = (int)lehmer_pcnt(sqrt3(x));
    ll sum = getphi(x, a) +(ll)(b + a - 2) * (b - a + 1) / 2;
    for (int i=a+1;i<=b;i++){
        ll w=x/p[i];
        sum -=lehmer_pcnt(w);
        if (i>c)continue;
        ll lim=lehmer_pcnt(sqrt2(w));
        for (int j=i;j<=lim;j++)
            sum-=lehmer_pcnt(w/p[j])-(j-1);
    }
    return sum;
}
int main(){
    init();
    ll n;
    while(~scanf("%lld",&n)){
        printf("%lld\n",lehmer_pcnt(n));
    }
    return 0;
}
