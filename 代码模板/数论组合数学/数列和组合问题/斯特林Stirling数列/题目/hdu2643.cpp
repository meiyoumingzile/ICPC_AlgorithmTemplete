#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=110;
const int mod= 20090126;
ll S[110][110];
ll f[110];
void init(){
    f[1]=1;
    for(int i=2;i<MAX;i++){
        f[i]=f[i-1]*i%mod;
    }
}

ll quickmi(ll a,ll b,ll mod){//���д��
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

ll SS(ll a,ll b){
    if(S[a][b]!=-1){
        return S[a][b];
    }else if(a==b){
        return 1;
    }else if(b==0){
        return 0;
    }
    ll ans=(SS(a-1,b-1)+SS(a-1,b)*b%mod)%mod;
    S[a][b]=ans;
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,t,n;
    memset(S,-1,sizeof(S));
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        ll ans=0;
        for(i=1;i<=n;i++){
            ans=(ans+SS(n,i)*f[i]%mod)%mod;
        }
        printf("%lld\n",ans);
    }
return 0;
}
