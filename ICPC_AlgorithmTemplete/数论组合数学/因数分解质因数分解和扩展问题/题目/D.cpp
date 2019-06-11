#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

bool vis[MAX];
int p[MAX];
int num[MAX];
int pi[MAX];
ll F[MAX];
int cnt=0;
void getPrimes(int n){
    int i,j;
    for(i=2;i<n;i++){
        if(vis[i]==0){
            p[cnt++]=i;
        }
        for(j=0;i*p[j]<n;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                break;
            }
        }
    }
}


ll cmp(ll x){//定义的函数，
    return pi[x];
}
ll divSum(ll n,ll m){//sum(n/i),i的范围是，[1,m]
    if(n<m){
        printf("错误");
        return -1;
    }
    ll ans=0,i,j,k,sqrtn;
    if(m*m<=n){//小于等于sqrtn的情况
        for(i=1;i<=m;i++){
            ans+=cmp(n/i);
        }
    }else{
        sqrtn=(ll)sqrt(n);
        for(i=1;i<=sqrtn;i++){
            ans+=cmp(n/i);
        }
        k=n/sqrtn-sqrtn;
        if(sqrtn+k>=m){//在(sqrtn,n/sqrtn]
            ans+=(m-sqrtn)*cmp(sqrtn);//
            return ans;
        }//以下是在(n/sqrtn,n]的
        i=sqrtn+k+1;
        j=sqrtn;
        ans+=k*cmp(sqrtn);//
        while(j>1){
            k=n/(j-1)-n/j;
            j--;
            if(i+k<=m){
                ans+=cmp(n/i)*k;//
                i+=k;
            }else{
                ans+=cmp(n/i)*(m-i+1);//
                return ans;
            }
        }
    }
    return ans;
}


int main(int argc,char *argv[]){
    //freopen("data//in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("data//my.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll i,j,k,a,b,ans,sqrtb;
    getPrimes(MAX);
    for(i=1;i<MAX/2;i++){
        for(j=0;j<cnt&&p[j]*i<MAX;j++){
            num[p[j]*i]++;
        }
    }
    for(i=2;i<MAX;i++){
        F[i]=F[i-1]+num[i];
    }
    for(i=2;i<MAX;i++){
        pi[i]=pi[i-1];
        if(vis[i]==0){
            pi[i]++;
        }
    }
    while(~scanf("%lld%lld",&a,&b)){
        if(a>b){
            a==b;
        }

        printf("%lld\n",F[b]-divSum(b,a-1));
    }
return 0;
}

