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
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define ll __int64
#define lld I64d
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct Mobius{
    ll *prime,*mob,cnt;
    bool *vis;
    void getMob(int Max){
        ll i,j;
        cnt=0;
        prime=new ll[Max];//看情况减小
        mob=new ll[Max];
        vis=new bool[Max];
        memset(vis,0,sizeof(bool)*Max);
        memset(mob,0,sizeof(ll)*Max);
        mob[1]=1;
        for(i=2;i<Max;i++){
            if(!vis[i]){
                prime[cnt++]=i;
                mob[i]=-1;
            }
            for(j=0;j<cnt&&i*prime[j]<Max;j++){
                vis[i*prime[j]]=1;
                if(i%prime[j]){
                    mob[i*prime[j]]=-mob[i];
                }else{
                    mob[i*prime[j]]=0;
                    break;
                }
            }
        }

    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    Mobius mo;
    mo.getMob(MAX);
    ll a,b,c,d,k,t,T,i,j,ans,f1,minbd,n;
    scanf("%lld",&T);
    for(t=1;t<=T;t++){
        scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&k);
        if(k==0){
            f1=0;
        }else{
            b/=k;
            d/=k;
            for(f1=0,i=1;i<=min(b,d);i++){
                minbd=min(b/i,d/i)-1;
                n=(minbd+1)*minbd/2;
                f1+=mo.mob[i]*(b/i*(d/i)-n);
            }
        }
        printf("Case %lld: %lld\n",t,f1);
    }
return 0;
}
