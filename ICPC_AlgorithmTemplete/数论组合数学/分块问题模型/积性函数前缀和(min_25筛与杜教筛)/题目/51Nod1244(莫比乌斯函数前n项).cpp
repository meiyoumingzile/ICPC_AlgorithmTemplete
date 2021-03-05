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
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000000;
const int mod=1e9+7;
ll ad[MAX];
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
Mobius mo;
map<ll,ll>ind;

ll sum(ll n){
    if(n<MAX){
       // printf("%lld\n",ad[n]);
        return ad[n];
    }
    if(ind.count(n)){
        return ind[n];
    }
    ll sqrtn=sqrt(n);
    ll ad=(ll)ceil(n/2.0),i,last,ans;
    for(i=2,last=n/2;i<sqrtn;i++){
        ad+=sum(i)*(last-n/(i+1));
        ad+=sum(n/i);
        last=n/(i+1);
    }

    if(n/sqrtn==sqrtn){
        ad+=sum(n/sqrtn);
    }else{
        ad+=sum(sqrtn)*(last-sqrtn);
        ad+=sum(n/sqrtn);
    }
    ans=1-ad;
    ind[n]=ans;
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll a,b,sa,sb;
    int i,j,k;
    mo.getMob(MAX);
    ad[1]=mo.mob[1];
    ad[0]=0;
    for(i=2;i<MAX;i++){
        ad[i]=ad[i-1]+mo.mob[i];
    }
    //printf("%lld %lld\n",ad[5000000],ad[4999999]);
    scanf("%lld%lld",&a,&b);
    a--;
    if(a<MAX){
        sa=ad[a];
    }else{
        sa=sum(a);
    }
    if(b<MAX){
        sb=ad[b];
    }else{
        sb=sum(b);
    }
    printf("%lld\n",sb-sa);
return 0;
}
/*
5000000 5000000
*/
