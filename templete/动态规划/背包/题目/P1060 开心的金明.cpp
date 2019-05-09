#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=30010;
const int mod=1e9+7;
int dp[30][MAX];
int pr[30];
int val[30];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int limPrice,N,i,j;
    scanf("%d%d",&limPrice,&N);
    for(i=1;i<=N;i++){
        scanf("%d%d",&pr[i],&val[i]);
    }
    for(i=1;i<=N;i++){
        for(j=limPrice;j>=pr[i];j--){
            dp[i][j]=max(dp[i-1][j-pr[i]]+pr[i]*val[i],dp[i-1][j]);//不拿是前i-1个的价值，拿就是，[i-1][j-pr[i]]的价值传递过来加上当的
        }
        for(;j>=0;j--){
            dp[i][j]=dp[i-1][j];
        }
    }
    printf("%d\n",dp[N][limPrice]);
return 0;
}
