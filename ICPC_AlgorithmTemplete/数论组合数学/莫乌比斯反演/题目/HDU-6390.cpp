#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
#include <cstdlib>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define dd double
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000001;
int prime[MAX],mob[MAX],phi[MAX],pcnt;
bool vis[MAX];
void getPrime(int n){
    rg int i,j,k;
    pcnt=0;
    mob[1]=phi[1]=vis[1]=1;
    for(i=2;i<n;i++){
        if(!vis[i]){
            prime[pcnt++]=i;
            phi[i]=i-1;
            mob[i]=-1;
        }
        for(j=k=0;i*prime[j]<n;j++){
            k=i*prime[j];
            vis[k]=1;
            if(i%prime[j]==0){
                phi[k]=phi[i]*prime[j];
                mob[k]=0;
                break;
            }else{
                mob[k]=-mob[i];
                phi[k]=phi[i]*(prime[j]-1);
            }
        }
    }
}
ll inv[MAX],g[MAX];
void getInv(ll m,cint p){
    inv[1]=1;
    for(ll i=2;i<m;i++){
        inv[i]=(p-p/i)*inv[p%i]%p;
    }
    for(ll i=1;i<m;i++){
        g[i]=i*inv[phi[i]]%p;
    }
}
int main(){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
	rg int i,j,a,b,k,t,T,n,m,nm;
    getPrime(MAX);
	scanf("%d",&T);
	while(T--){
        scanf("%d%d%d",&n,&m,&k);
        const int p=k;
        nm=min(n,m);
        getInv(nm+1,p);
        ll ans=0,sum;
        for(i=1;i<=nm;++i){
            a=n/i;
            b=m/i;
            t=min(a,b);
            sum=0;
            for(j=1;j<=t;j++){
                sum=(sum+(ll)(a/j)*(b/j)*mob[j]+p)%p;
            }
            ans=(g[i]*sum%p+ans)%p;
        }
        printf("%lld\n",ans);
	}
return 0;
}

