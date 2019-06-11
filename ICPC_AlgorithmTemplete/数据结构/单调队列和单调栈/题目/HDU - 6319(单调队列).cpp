#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=20000010;


int a[MAX],A[MAX];
void solve(cint n,cint m){
    rg int i,j,t,f,b;
    ll ans1=0,ans2=0;
    f=MAX/2;
    b=f+1;
    t=n-m+1;
    for(i=n;i>t;i--){
        while(f>=b&&A[a[b]]<=A[i]){
            b++;
        }
        a[--b]=i;
        while(a[f]-i>=m){
            f--;
        }
    }
    for(i=t;i>0;i--){
        while(f>=b&&A[a[b]]<=A[i]){
            b++;
        }
        a[--b]=i;
        while(a[f]-i>=m){
            f--;
        }
        ans1+=A[a[f]]^i;
        ans2+=(f-b+1)^i;
    }
    printf("%lld %lld\n",ans1,ans2);
}

inline void scan(int &x){//���
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,k,T,n,m,p,q,r,mod;
	scanf("%d",&T);
	while(T--){
        scan(n);scan(m);scan(k);scan(p);scan(q);scan(r);scan(mod);
        for(i=1;i<=k;i++){
            scan(A[i]);
        }
        for(i=k+1;i<=n;i++){
            A[i] = ((ll)p*A[i-1]%mod+(ll)q*i%mod+r%mod)%mod;
        }
        solve(n,m);
	}
return 0;
}

