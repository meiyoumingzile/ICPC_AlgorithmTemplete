#include<bits/stdc++.h>
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll mygcd(ll a,ll b){
    while(b!=0){
        ll temp=a;
        a=b;
        b=temp%b;
    }
    return a;
}
//����
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b){//˳��д��lcm
    return a/gcd(a,b)*b;
}

int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("debug\\out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll i,j,k,a,b,c,ans,n2;
    while(1){
        scanf("%lld%lld",&a,&b);
        printf("%lld %lld\n",gcd(a,b),lcm(a,b));
    }
return 0;
}
