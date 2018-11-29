#include<stdio.h>
#include<math.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;

int pCnt;
bool vis[MAX];
ll prime[MAX];
ll phi[MAX];
void getPrime(int N){
    int i,j,k;
    pCnt=0;
    phi[1]=1;
    for(i=2;i<N;i++){
        if(!vis[i]){
            prime[pCnt++]=i;
            phi[i]=i-1;//如果i是素数，phi[i]=i-1
        }
        for(j=0;i*prime[j]<N;j++){
            k=i*prime[j];
            vis[k]=true;
            if(i%prime[j]==0){
                //i mod p = 0, 那么phi(i * p)=p * phi(i)
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }else{
                //i mod p ≠0,  那么phi(i * p)=phi(i) * (p-1)，p是素数
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
}

inline ll getEu(ll N){//根据公式，求一个数欧拉函数值,且数据较大有必要用筛法先求出素数,如果打表求很多个用下面的筛选方法
    register ll i,n=N,ans=N,m=1;
    if(N<MAX){
        return phi[N];
    }
    for(i=0;n!=1&&i<pCnt;i++){
        if(n%prime[i]==0){
            while(n%prime[i]==0)
                n/=prime[i];
            ans/=prime[i];
            m*=prime[i]-1;
        }
    }
    if(n>1){
        ans/=n;
        m*=n-1;
    }
    return ans*m;
}
inline ll getEu2(ll N){//根据公式，求一个数欧拉函数值，且数据较大有必要用筛法先求出素数,如果打表求很多个用下面的筛选方法
    register ll i,n=N,ans=N,m=1;
    if(N<MAX){
        return phi[N];
    }
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
inline ll pow(ll a,ll n,ll mod){
    register ll ans=1;
    a%=mod;
    while(n){
        if(n&1){
            ans=ans*a%mod;
        }
        n>>=1;
        a=a*a%mod;
    }
    return ans;
}
inline ll getAns(ll n,ll mod){
    register ll i,j,a=0,k,ans=0,sqrtn=(ll)sqrt(n);
    for(i=1;i<=sqrtn;i++){
        if(n%i==0){
            j=n/i;
            k=getEu2(j);
            a=pow(n,i-1,mod)*k%mod;
            ans=(ans+a)%mod;
            if(i!=j){
                k=getEu2(i);
                a=pow(n,j-1,mod)*k%mod;
                ans=(ans+a)%mod;
            }
        }
    }
    //printf("%lld\n",ans);
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	register ll i,j,k,T,n,m,N,P,ans;
	getPrime(MAX);
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&N,&P);
        ans=getAns(N,P);
        printf("%lld\n",ans);
    }
return 0;
}
/*
1000
1000000000 1000000007
*/
