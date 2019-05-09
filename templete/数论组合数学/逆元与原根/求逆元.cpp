#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define ll long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

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
ll inv1(ll  a,ll p){//返回逆元,扩展欧几里得法,p是任何数，常规方法没有限制
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}


ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll inv2(ll a,ll p){//费马小定理，p必须是素数
    return quickmi(a,p-2,p);
}
ll divMod(ll a,ll b,ll mod){//当且仅当a/b能整除,求a/b%mod,但是注意，这里b和mb都不能取过模，也就是他们太大的话这个方法一点也不好用
    ll M=b*mod;
    return (a%M)/b;
}
ll inv3(ll a,ll p){//a|(p+1),且p是个素数
    if((p+1)%a==0){
        return (p+1)/a;
    }
    return -1;
}

ll INV[MAX];
void getInv(ll MAX,ll p){//打表法求很多个逆元,p是素数
    INV[1] = 1;
    for (int i=2;i<MAX;i++) {
        INV[i]=(ll)(p-p/i)*INV[p%i]%p;
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NUll));//有的OJ不能加这句话a
    ll a,b,i;
    getInv(MAX,mod);
    for(i=1;i<100;i++){
        printf("%lld:%lld=%lld ",i,INV[i],i*INV[i]%mod);
    }printf("\n");
    while(~scanf("%lld%lld",&a,&b)){//求a模mod的逆元
        printf("%lld\n",inv1(a,b));
    }
return 0;
}
