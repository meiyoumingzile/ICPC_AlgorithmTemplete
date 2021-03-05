#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX=100010;
int fer[4]={5,17,257,65537};
int ferg[4]={2,3,3,3};
ll N,constP=1004535809;
ll x[MAX];
ll F[MAX];
int seq[MAX];
int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
int grn[21]={3,1004535808,483363861,395918948,691095095,67253981,89059135,337291080,317143553,8295483,327081633,714163887,295244910,2062645,524615618,333849333,50393163,925609281,615614863,862977694,848723745};

ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

void DTT(const ll *x,int N,int kind){//kind表示是否是逆变换，逆变换和正变换差不多
    ll i,j,k,bit,n;
    for(bit=0,n=N;n;n/=2,bit++);
    bit--;
    for(k=0;k<N;k++){//grn相当于w
        for(i=0;i<N;i++){
            F[k]=(F[k]+x[i]%constP*quickmi(grn[bit],i*k,constP)%constP)%constP;
        }
    }
}


int main(){
    int i,j,k,n;
    while(~scanf("%lld",&N)){
        for(i=0;i<N;i++){
            scanf("%lld",&x[i]);
        }
        DTT(x,N,-1);
        for(i=0;i<N;i++){
            printf("%lld\n",F[i]);
        }
    }
return 0;
}
/*
8
1
2
3
4
5
6
7
9
*/
