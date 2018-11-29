#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int dp[2][1010];
int A[1010];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k=-1,n;
    cin>>n;
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            scanf("%d",&A[j]);
            dp[1][j]=A[j]+max(dp[0][j-1],dp[0][j]);
        }
        memcpy(dp[0],dp[1],sizeof(dp[0]));
    }

    for(i=1;i<=n;i++){
        k=max(k,dp[0][i]);
    }
    printf("%d\n",k);
return 0;
}

