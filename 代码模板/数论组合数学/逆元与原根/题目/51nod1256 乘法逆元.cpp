#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){//求逆元
    if(!b){
        d=a;//根据方程ax-py=1，此处a应该等于1否则说明没有逆元
        x=1;
        y=0;
    }else{
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
ll getinv(ll  a,ll p){//返回逆元,扩展欧几里得法,p是任何数，常规方法没有限制
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll n,m,ans;
    scanf("%lld%lld",&n,&m);
    ans=getinv(n,m);
    printf("%lld\n",ans);
return 0;
}

