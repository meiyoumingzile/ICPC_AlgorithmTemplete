#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=20010;
const int mod=998244353;
ll fac[20010];
void getFac(ll m){
    fac[1]=fac[0]=1;
    for(ll i=2;i<m;i++){
        fac[i]=fac[i-1]*i%mod;
    }
}

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
ll inv(ll  a,ll p){//������Ԫ,��չŷ����÷�,p���κ��������淽��û������
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}

bool isO(int n){
    return n%2==0;
}


ll getChebyshev(ll n,ll m){
    ll ans=1,i,k,j;
    if(m>n){
        return 0;
    }
    if(n%2==0){
        if(m%2==0){
            k=m/2;
            i=n+m-2;
            j=n-m;
            if(i==0){
                ans=ans*inv(2,mod)%mod;
            }else{
                for(;i>j;i-=2){
                    ans=ans*i%mod;
                }
            }

            ans=ans*n%mod;
            ans=ans*inv(fac[m],mod)%mod;
            if(!isO(n/2-k)){
                ans=-ans+mod;
            }
        }else{
            return 0;
        }
    }else{
        if(m%2==0){
            return 0;
        }else{
            k=(m+1)/2;
            j=n-2*k+1;
            for(i=n+2*k-3;i>j;i-=2){
                ans=ans*i%mod;
            }
            ans=ans*n%mod;
            ans=ans*inv(fac[2*k-1],mod)%mod;
            if(!isO((n+1)/2-k)){
                ans=-ans+mod;
            }
        }
    }
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰

    ll n,m,i,j;
    getFac(MAX);
    while(~scanf("%lld%lld",&n,&m)){
        printf("%lld\n",getChebyshev(n,m));
    }
return 0;
}
