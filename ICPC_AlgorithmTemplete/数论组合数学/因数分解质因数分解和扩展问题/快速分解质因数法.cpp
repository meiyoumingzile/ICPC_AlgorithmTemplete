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
struct PRIME{
    const int MT=5;
    vector<ll>fac;
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
    ll quickmi(ll a,ll b,cll mod){
        ll ans=1;
        for(a%=mod;b;b/=2,a=(__int128)a*a%mod){
            if(b%2==1)
                ans=(__int128)ans*a%mod;
        }
        return ans;
    }
    const int bace[5]={2,3,7,61,24251};
    bool isPrime(cll x){
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
    ll gcd(cll a,cll b){
        return b?gcd(b,a%b):a;
    }
    ll pollard_rho(cll n, int c){
        ll i =1,k=2,x,y;
        y=x=(__int128)rand()*rand()*rand()*rand()%(n-1)+1;
        while(1){
            i++;
            x=((__int128)x*x%n+c)%n;
            ll p = gcd((y-x+n)%n, n);
            if(p != 1 && p != n)	return p;
            if(y == x)	return n;
            if(i == k){
                y = x;
                k <<= 1;
            }
        }
    }
    void resolution(ll n,ll c=12111){//c是一个随机质数即可
        if(n>1){
            if(isPrime(n)){
                fac.push_back(n);
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
    int findFac(cll n){//得到不同质数个数
        fac.clear();
        fac.reserve(100);
        resolution(n,2137342);
        sort(fac.begin(),fac.end());//排序
        return fac.size();
    }
};
PRIME pr;
int main(){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	ll n,i,T,cnt;
	pr.init(100);
	scanf("%lld",&T);
	while(T--){
        scanf("%lld",&n);
        cnt=pr.findFac(n);
        if(cnt==1&&pr.fac[0]==n){
            printf("Prime\n");
        }else{
            printf("%lld\n",pr.fac[cnt-1]);
        }
	}
	return 0;
}
