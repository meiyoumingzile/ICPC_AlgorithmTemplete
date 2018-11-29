#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

int N,M;
int dp[110][10010];//代表前i种菜花了j元的最大价值，价值等于花钱数
int A[110];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k;
    cin>>N>>M;
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            if(j<A[i-1]){
                dp[i][j]=dp[i-1][j];
            }else if(j==A[i-1]){
                dp[i][j]=dp[i-1][j]+1;
            }else{
                dp[i][j]=dp[i-1][j]+dp[i-1][j-A[i-1]];
            }
        }
    }
    printf("%d\n",dp[N][M]);
return 0;
}
