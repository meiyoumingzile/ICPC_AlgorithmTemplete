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

ll quickmi(ll a,ll b,ll mod){//����a^b���Ҷ�modȡ��
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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    ll i,j,a,b,c,m;
    while(1){
       scanf("%lld%lld%lld",&a,&b,&m);
        printf("%lld\n",quickmi(a,b,m));
    }
return 0;
}
