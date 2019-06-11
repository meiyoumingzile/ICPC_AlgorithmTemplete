#include<stdio.h>
#include<math.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;

int pCnt;
bool vis[MAX];
ll prime[MAX];
ll phi[MAX];
void getPrime(int N){
    int i,j,k;
    pCnt=0;
    phi[1]=1;
    for(i=2;i<N;i++){
        if(!vis[i]){
            prime[pCnt++]=i;
            phi[i]=i-1;//���i��������phi[i]=i-1
        }
        for(j=0;i*prime[j]<N;j++){
            k=i*prime[j];
            vis[k]=true;
            if(i%prime[j]==0){
                //i mod p = 0, ��ôphi(i * p)=p * phi(i)
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }else{
                //i mod p ��0,  ��ôphi(i * p)=phi(i) * (p-1)��p������
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
}

inline ll getEu(ll N){//���ݹ�ʽ����һ����ŷ������ֵ,�����ݽϴ��б�Ҫ��ɸ�����������,��������ܶ���������ɸѡ����
    register ll i,n=N,ans=N,m=1;
    if(N<MAX){
        return phi[N];
    }
    for(i=0;n!=1&&i<pCnt;i++){
        if(n%prime[i]==0){
            while(n%prime[i]==0)
                n/=prime[i];
            ans/=prime[i];
            m*=prime[i]-1;
        }
    }
    if(n>1){
        ans/=n;
        m*=n-1;
    }
    return ans*m;
}
inline ll getEu2(ll N){//���ݹ�ʽ����һ����ŷ������ֵ�������ݽϴ��б�Ҫ��ɸ�����������,��������ܶ���������ɸѡ����
    register ll i,n=N,ans=N,m=1;
    if(N<MAX){
        return phi[N];
    }
    for(i=2;n!=1;i++){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            ans/=i;
            m*=i-1;
        }
    }
    if(ans==N){
        return N-1;
    }
    return ans*m;
}
inline ll pow(ll a,ll n,ll mod){
    register ll ans=1;
    a%=mod;
    while(n){
        if(n&1){
            ans=ans*a%mod;
        }
        n>>=1;
        a=a*a%mod;
    }
    return ans;
}
inline ll getAns(ll n,ll mod){
    register ll i,j,a=0,k,ans=0,sqrtn=(ll)sqrt(n);
    for(i=1;i<=sqrtn;i++){
        if(n%i==0){
            j=n/i;
            k=getEu2(j);
            a=pow(n,i-1,mod)*k%mod;
            ans=(ans+a)%mod;
            if(i!=j){
                k=getEu2(i);
                a=pow(n,j-1,mod)*k%mod;
                ans=(ans+a)%mod;
            }
        }
    }
    //printf("%lld\n",ans);
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	register ll i,j,k,T,n,m,N,P,ans;
	getPrime(MAX);
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&N,&P);
        ans=getAns(N,P);
        printf("%lld\n",ans);
    }
return 0;
}
/*
1000
1000000000 1000000007
*/
