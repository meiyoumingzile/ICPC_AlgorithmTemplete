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

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){//����Ԫ
    if(!b){
        d=a;
        x=1;
        y=0;
    }else{
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
ll inv1(ll  a,ll p){//������Ԫ,��չŷ����÷�,p���κ��������淽��û������
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}


ll quickmi(ll a,ll b,ll mod){//���д��
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
ll inv2(ll a,ll p){//����С����p����������
    return quickmi(a,p-2,p);
}
ll divMod(ll a,ll b,ll mod){//���ҽ���a/b������,��a/b%mod,����ע�⣬����b��mb������ȡ��ģ��Ҳ��������̫��Ļ��������һ��Ҳ������
    ll M=b*mod;
    return (a%M)/b;
}
ll inv3(ll a,ll p){//a|(p+1),��p�Ǹ�����
    if((p+1)%a==0){
        return (p+1)/a;
    }
    return -1;
}

ll INV[MAX];
void getInv(ll MAX,ll p){//�����ܶ����Ԫ,p������
    INV[1] = 1;
    for (int i=2;i<MAX;i++) {
        INV[i]=(ll)(p-p/i)*INV[p%i]%p;
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NUll));//�е�OJ���ܼ���仰a
    ll a,b,i;
    getInv(MAX,mod);
    for(i=1;i<100;i++){
        printf("%lld:%lld=%lld ",i,INV[i],i*INV[i]%mod);
    }printf("\n");
    while(~scanf("%lld%lld",&a,&b)){//��aģmod����Ԫ
        printf("%lld\n",inv1(a,b));
    }
return 0;
}
