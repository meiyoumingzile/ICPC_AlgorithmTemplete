#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct v2{
    ll x,y,i;
};


v2 A[MAX];
ll ANS[MAX];
inline ll quickmi(ll a,ll b,const ll &mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll  fac[MAX],facInv[MAX],pos[MAX];//pos[i]代表N==i的数据的分块编号，分块是按照一定范围分的(这里是每500一块)。目的是为了把N相近的数据放到同一块里
bool cmp(const v2 &a,const v2 &b){
    if(pos[a.x]==pos[b.x])//同一块 按照M排序,否则按照N,按照pos排序分块
        return a.y<b.y;
    return a.x<b.x;
}
inline ll CC(ll n,ll m){
    if(m==0)
        return 1;
    return fac[n]*facInv[m]%mod*facInv[n-m]%mod;
}
void init(){
    rg int i,j,k;
    fac[0]=facInv[0]=fac[1]=facInv[1]=1;
    for(i=2;i<MAX;i++){
        fac[i]=fac[i-1]*i%mod;
        facInv[i]=quickmi(fac[i],mod-2,mod);
    }
}
ll getSum(int n,int m){
    ll ans=1;
    for(int i=1;i<=m;i++){
        ans=(ans+CC(n,i))%mod;

    }
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg ll i,j,k,T,m,n,sqrtT;
	ll ans;
	init();
	cin>>T;
	sqrtT=sqrt(MAX);
	for(i=0;i<T;i++){
        scanf("%lld%lld",&A[i].x,&A[i].y);
        pos[A[i].x]=A[i].x/sqrtT;
        A[i].i=i;
	}
	sort(A,A+T,cmp);
	ans=getSum(A[0].x,A[0].y);
    ANS[A[0].i]=ans;
    for(i=1;i<T;i++){
        for(j=A[i-1].x;j<A[i].x;j++){
            ans=(ans*2%mod-CC(j,A[i-1].y)+mod)%mod;
        }
        for(j=A[i-1].x;j>A[i].x;j--){
            ans=(ans+CC(j-1,A[i-1].y))%mod*inv2%mod;
        }
        for(j=A[i-1].y;j<A[i].y;j++){
            ans=(ans+CC(A[i].x,j+1))%mod;
        }
        for(j=A[i-1].y;j>A[i].y;j--){
            ans=(ans-CC(A[i].x,j)+mod)%mod;
        }
        ANS[A[i].i]=ans;
    }
    for(i=0;i<T;i++){
        printf("%lld\n",ANS[i]);
    }
return 0;
}

