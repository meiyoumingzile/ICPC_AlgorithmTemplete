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
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

ll exgcd(ll a,ll b,ll &x,ll &y){  //��һ��д�����������Լ��
    if(!b){
        x=1;y=0;return a;
    }
    int e=exgcd(b,a%b,x,y);
    int kkz=x;x=y;y=kkz-a/b*y;
    return e;
}


int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("debug\\out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll i,j,ans,x0,y0,x,y,m,n,L,a,b,c,g,d;
    scanf("%lld%lld%lld%lld%lld",&x0,&y0,&m,&n,&L);
    a=n-m;
    b=L;
    c=x0-y0;
    g=exgcd(a,b,x,y);
    if(c%g!=0){
        printf("Impossible\n");
    }else{
        ans=x*c/g;
        d=b/g;
        ans=((ans%d)+d)%d;
        printf("%lld\n",ans);
    }
return 0;
}
