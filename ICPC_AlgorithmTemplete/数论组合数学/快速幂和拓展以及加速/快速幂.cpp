#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll quickmul(ll a, ll b, ll mod){
    ll res=0;
    while(b){
        if(b&1){
            res=(res+a)%mod;
        }
        b>>=1;
        a=a*2%mod;
    }
    return res;
}

ll quickmi(ll a,ll b,ll mod){//计算a^b并且对mod取余
    ll ans=1;
    a%=mod;
    while(b){
        if(b&1)
            ans=ans*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ans;
}


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll i,j,a,b,c,m;
    while(1){
       scanf("%lld%lld%lld",&a,&b,&m);
        printf("%lld\n",quickmi(a,b,m));
    }
return 0;
}
