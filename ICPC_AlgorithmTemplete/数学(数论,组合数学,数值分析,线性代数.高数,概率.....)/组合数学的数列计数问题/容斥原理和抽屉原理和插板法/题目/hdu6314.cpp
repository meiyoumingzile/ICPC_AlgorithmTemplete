#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=998244353;

inline ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll p2[9*MAX];
ll facInv[3010];
ll fac[3010][3010];

inline ll CC(const ll &n,const ll &m){
    if(m==0)
        return 1;
    return fac[n-m+1][n]*facInv[m]%mod;
}

ll getAns(int n,int m,int a,int b){
    ll ans=0,i,j,k;
    for(i=a;i<=n;i++){
        for(j=b;j<=m;j++){
             k=(i+j)&1?-1:1;
            ans=(ans+p2[(n-i)*(m-j)]*CC(n,i)%mod*CC(m,j)%mod*k+mod)%mod;
        }
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("hdu6314.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,j,k,T,m,n,a,b;
	rg ll ans;
	p2[0]=1;
	for(i=1;i<9000001;i++){
        p2[i]=(p2[i-1]<<1)%mod;
	}
	facInv[1]=ans=1;
	for(i=2;i<3001;i++){
        ans=ans*i%mod;
        facInv[i]=quickmi(ans,mod-2,mod);
	}
    for(i=1;i<3001;i++){//[i,j]乘积
        fac[i][i]=i;
        for(j=i+1;j<3001;j++){
            fac[i][j]=fac[i][j-1]*j%mod;
        }
    }
    while(~scanf("%d%d%d%d",&n,&m,&a,&b)){
        ans=0;
        for(i=a;i<=n;i++){
            for(j=b;j<=m;j++){
                k=(i+j)&1?-1:1;
                //ans=(ans+p2[(n-i)*(m-j)]*CC(n,i)%mod*CC(m,j)%mod+mod)%mod;
                ans=(ans+getAns(n-i,m-j,0,0)*CC(n,i)%mod*CC(m,j)%mod)%mod;
            }
        }
        printf("%lld\n",ans);
    }
return 0;
}

