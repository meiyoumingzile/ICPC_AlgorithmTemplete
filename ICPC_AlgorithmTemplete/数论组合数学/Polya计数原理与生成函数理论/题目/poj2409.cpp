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
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll pow(ll a,ll n){
    ll ans=1;
    while(n){
        if(n&1){
            ans*=a;
        }
        n>>=1;
        a*=a;
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	register ll i,d,T,c,n,m,ans;
	while(~scanf("%lld%lld",&c,&n)){
        if(c==0&&n==0)
            break;
        ans=0;
        for(i=1;i<=n;i++){
            ans+=pow(c,gcd(i,n));
        }
        if(n&1){
            d=2*n;
            m=(n>>1)+1;
            ans+=pow(c,m)*n;
        }else{
            d=2*n;
            m=n>>1;
            ans+=pow(c,m)*(n/2);
            m++;
            ans+=pow(c,m)*(n/2);
        }
        ans/=d;
        printf("%lld\n",ans);
	}
return 0;
}

