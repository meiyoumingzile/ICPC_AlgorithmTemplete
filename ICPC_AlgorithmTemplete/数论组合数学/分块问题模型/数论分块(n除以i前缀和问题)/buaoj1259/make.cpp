#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const ll MAX=1000010;
const int mod=1e9+7;
ll myrand(){
    ll i,j,k=1,n=0;
    for(i=0;i<9;i++){
        n+=k*(rand()%10);
        k*=10;
    }
    n+=k*(rand()%9+1);
    return n;
}
int main(int argc,char *argv[]){
    freopen("test4.in","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    srand(time(NULL));//有的OJ不能加这句话
    ll n,m,T,k=1000000000;
    T=100;
    printf("%lld\n",T);
    while(T--){
        n=myrand();
        m=myrand();
        printf("%lld %lld\n",n,m);
    }
return 0;
}

