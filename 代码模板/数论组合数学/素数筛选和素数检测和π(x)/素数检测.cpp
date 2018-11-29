#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
const int MAX=1010;

struct PRIME{
    const int MT=5;
    bool vis[MAX];
    ll prime[MAX];
    int pCnt;
    int init(int n=MAX){
        memset(vis,1,sizeof(vis));
        pCnt=0;
        for(int i=2;i<n;i++){
            if(vis[i]){
                prime[pCnt++]=i;
            }
            for(int j=0;i*prime[j]<n;j++){
                vis[i*prime[j]]=0;
                if(i%prime[j]==0){
                    break;
                }
            }
        }
        return pCnt;
    }
    ll quickmi(ll a,ll b,const ll &mod){
        ll ans=1;
        for(a%=mod;b;b/=2,a=(__int128)a*a%mod){
            if(b%2==1)
                ans=(__int128)ans*a%mod;
        }
        return ans;
    }
    const int bace[5]={2,3,7,61,24251};
    bool isPrime(ll x){
        if(x==46856248255981ll||x<2)return 0;//小于x或者是强伪素数
        ll y,r;
        int ti=0,i,k;
        for(auto a : bace){
            if(a==x){
                return 1;
            }
        }
        for(y=x-1;y%2==0;y>>=1,ti++);
        for(k=0;k<MT;k++){//检测次数
            r=quickmi(bace[k],y,x);
            if(r==1||r==x-1)continue;
            for(i=1;i<=ti;i++){
                r=(__int128)r*r%x;
                if(r==x-1)
                    break;
            }
            if(i>ti)return 0;
        }
        return 1;
    }
};
PRIME pr;

int main(int argc,char *argv[]){
    ll n,T;
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        printf("%s\n",pr.isPrime(n)?"Yes":"No");//1代表是素数
    }
return 0;
}
