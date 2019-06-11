#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int V,E;
ll ans[20],dp[30010][1024],cnt1[1030];
void println(ll *arr,int b,int e){//[b,e)
    printf("(%d:%d)",b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}
inline int getBit1(int n){
    return n?getBit1(n>>1)+(n&1):0;
}

inline bool exist(const int &n,const int &u,const int &v){
    return ((n>>u)&1)&&((n>>v)&1);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    rg int i,j,k,T,t,u,v,n;
    char kind[5];
    for(i=1;i<=1024;i++){
        cnt1[i]=getBit1(i);
    }
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&V,&E);
        n=1<<V;
        dp[0][0]=1;
        for(t=0;t<E;t++){
            memset(ans,0,sizeof(ans));
            scanf("%s%d%d",kind,&u,&v);
            u--;
            v--;
            k=(1<<u)+(1<<v);
            if(kind[0]=='+'){
                for(i=0;i<n;i++){
                    if(i>=k&&exist(i,u,v)){
                        dp[t+1][i]=(dp[t][i]+dp[t][i-k])%mod;
                    }else{
                        dp[t+1][i]=dp[t][i];
                    }
                    //printf("-------%d\n",getBit1(i));
                    ans[cnt1[i]]=(ans[cnt1[i]]+dp[t+1][i])%mod;
                }
            }else{
                for(i=0;i<n;i++){
                    if(i>=k&&exist(i,u,v)){
                        dp[t+1][i]=(dp[t][i]-dp[t+1][i-k]+mod)%mod;
                    }else{
                        dp[t+1][i]=dp[t][i];
                    }
                    //printf("-------%d\n",getBit1(i));
                    ans[cnt1[i]]=(ans[cnt1[i]]+dp[t+1][i])%mod;
                }
            }
            //println(dp[t+1],1,33);
            printf("%lld",ans[2]);
            for(i=4;i<=V;i+=2){
                printf(" %lld",ans[i]);
            }printf("\n");
        }
    }
return 0;
}
