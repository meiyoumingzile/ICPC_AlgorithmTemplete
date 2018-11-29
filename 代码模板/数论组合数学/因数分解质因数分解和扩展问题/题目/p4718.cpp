#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

#define ctz __builtin_ctzll
struct PRIME{
    const int MT=5;
    ll maxFac=-1;
    ll quickmi(ll a,ll b,cll mod){
        ll ans=1;
        for(a%=mod;b;b/=2,a=mul(a,a,mod)){
            if(b%2==1)
                ans=mul(ans,a,mod);
        }
        return ans;
    }
    const int bace[5]={2,3,7,61,24251};
    inline ll mul(ll a,ll b,ll m){
        ll d=((long double)a/m*b+1e-8);
        ll r=a*b-d*m;
        return r<0?r+m:r;
    }
    inline bool isPrime(cll x){
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
                r=mul(r,r,x);
                if(r==x-1)
                    break;
            }
            if(i>ti)return 0;
        }
        return 1;
    }
    inline ll gcd(ll a,ll b){//听说二进制算法特快
        if(!a)return b;
        if(!b)return a;
        int t=ctz(a|b);
        a>>=ctz(a);
        do{
            b>>=ctz(b);
            if(a>b){ll t=b;b=a,a=t;}
            b-=a;
        }while(b);
        return a<<t;
    }
    inline ll pollard_rho(cll n,ll c){
        ll x=0,y=x,t=1,q=1;
        int M=M=(1<<7)-1;
        for(int k=2;;k<<=1,y=x,q=1){//相当于重新迭代
            for(int i=1;i<=k;++i){
                x=(mul(x,x,n)+c)%n;
                q=mul(q,abs(x-y),n);
                if(!(i&M)){//应该巧妙利用了生日悖论
                    t=gcd(q,n);
                    if(t>1)break;
                }
            }
            if(t>1||(t=gcd(q,n))>1)break;
        }
        return t;
    }
    inline void resolution(ll n,ll c=12111){//c是一个随机质数即可
        if(n>1){
            if(isPrime(n)){
                maxFac=max(maxFac,n);
                return;
            }
            ll p=n;
            while(p==n)
                p = pollard_rho( p, c-- );
            while(n%p==0)
                n/=p;
            resolution( p, c );
            resolution( n, c );
        }
    }
};
PRIME pr;
int main(){
    //freopen("testdata.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	ll n,i,T,cnt;
	scanf("%lld",&T);
	while(T--){
        scanf("%lld",&n);
        pr.maxFac=-1;
        pr.resolution(n);
        if(pr.maxFac==n){
            printf("Prime\n");
        }else{
            printf("%lld\n",pr.maxFac);
        }
	}
	return 0;
}
