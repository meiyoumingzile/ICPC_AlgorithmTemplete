#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=20010;
const int mod=998244353;
ll fac[20010];
void getFac(ll m){
    fac[1]=fac[0]=1;
    for(ll i=2;i<m;i++){
        fac[i]=fac[i-1]*i%mod;
    }
}

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){//求逆元
    if(!b){
        d=a;
        x=1;
        y=0;
    }else{
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
ll inv(ll  a,ll p){//返回逆元,扩展欧几里得法,p是任何数，常规方法没有限制
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}

bool isO(int n){
    return n%2==0;
}


ll getChebyshev(ll n,ll m){
    ll ans=1,i,k,j;
    if(m>n){
        return 0;
    }
    if(n%2==0){
        if(m%2==0){
            k=m/2;
            i=n+m-2;
            j=n-m;
            if(i==0){
                ans=ans*inv(2,mod)%mod;
            }else{
                for(;i>j;i-=2){
                    ans=ans*i%mod;
                }
            }

            ans=ans*n%mod;
            ans=ans*inv(fac[m],mod)%mod;
            if(!isO(n/2-k)){
                ans=-ans+mod;
            }
        }else{
            return 0;
        }
    }else{
        if(m%2==0){
            return 0;
        }else{
            k=(m+1)/2;
            j=n-2*k+1;
            for(i=n+2*k-3;i>j;i-=2){
                ans=ans*i%mod;
            }
            ans=ans*n%mod;
            ans=ans*inv(fac[2*k-1],mod)%mod;
            if(!isO((n+1)/2-k)){
                ans=-ans+mod;
            }
        }
    }
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话

    ll n,m,i,j;
    getFac(MAX);
    while(~scanf("%lld%lld",&n,&m)){
        printf("%lld\n",getChebyshev(n,m));
    }
return 0;
}
