#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
ll inv2=500000004%mod;//逆元
ll phi[MAX];
ll sum[MAX];
int prime[MAX];
bool v[MAX];
int pCnt;
map<ll,ll>ind;

void getPrime(){
    int i,j,k;
    phi[1]=1;
    for(i=2;i<MAX;i++){
        if(v[i]==false){
            prime[pCnt++]=i;
            phi[i]=i-1;
        }
        for(j=0;i*prime[j]<MAX;j++){
            v[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }else{
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
}

void getSumArray(){
    for(int i=1;i<MAX;i++){
        sum[i]=(sum[i-1]+phi[i])%mod;
    }
}
ll calcsum(ll n){
    if(n<MAX){
        return sum[n];
    }else if(ind[n]>0){
        return ind[n];
    }else{
        ll ans=(n%mod*((n+1)%mod))%mod*inv2%mod;
        //printf("%lld\n",ans);
        ll i,j,k,sqrtn,num;
        sqrtn=(ll)sqrt(n);
        for(i=2;i<=n/sqrtn;i++){
            k=calcsum(n/i);
            ans=(ans-k+mod)%mod;
        }
        for(i=1;i<sqrtn;i++){
            k=calcsum(i);
            num=(n/i-n/(i+1))%mod*(k%mod)%mod;
            ans=(ans-num+mod)%mod;
        }
        ind[n]=ans;
        return ans;
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll N;
    getPrime();
    getSumArray();
    cin>>N;
    printf("%lld\n",calcsum(N));
return 0;
}

