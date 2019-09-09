#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
ll A[MAX],P[MAX];
ll quickmi(ll a,ll b,ll mod){//快速幂
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll exgcd(ll a,ll b,ll &x,ll &y){//扩展欧几里得
    if(!b){
        x=1;y=0;return a;
    }
    ll e=exgcd(b,a%b,x,y);
    ll kkz=x;x=y;y=kkz-a/b*y;
    return e;
}
ll quickMul(ll a,ll b,ll mod){//整数相乘，看看是否溢出，溢出就快速乘
    if(a==0&&b==0)
        return 0;
    int sga=a>0?1:-1,sgb=b>0?1:-1;
    a=abs(a);
    b=abs(b);
    if(a*b>=a)
        return a*b%mod*sga*sgb;
    return (__int128)a*b%mod*sga*sgb;
}
ll exCRT(ll *A,ll *P,int n){//无解返回-1，否则返回最小正整数解
    ll c,g,b,bg,x,y,a,m=P[0],ans=A[0];
    for(int i=1;i<n;i++){//得到不定方程m1*x1+m2*x2=a2-a1
        a=m;
        b=P[i];
        c=(A[i]-ans%b+b)%b;//因为ans%P[i]相当于
        g=exgcd(a,b,x,y);
        if(c%g)
            return -1;
        bg=b/g;
        x=quickMul(x%bg,c/g%bg,bg);// 不超ll可以直接x=x*(c/g)%bg;
        ans+=x*m;
        m*=bg;
        ans=(ans%m+m)%m;
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("testdata9.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    int N,i;
    cin>>N;
    for(i=0;i<N;i++){//P[i]是模数，A[i]是结果，X%P[i]==A[i]
        scanf("%lld%lld",&P[i],&A[i]);
    }
    printf("%lld\n",exCRT(A,P,N));
return 0;
}
