#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAX=110;
const int mod=1e9+7;
int dp[MAX][MAX];
int ad[MAX];
int A[MAX];

int sum(int l,int r){
    return ad[r]-ad[l-1];
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,N,r,mindp;
    cin>>N;
    for(i=1;i<=N;i++){
        scanf("%d",&A[i]);
        ad[i]=ad[i-1]+A[i];
    }
    for(k=1;k<N;k++){
        for(i=1;i+k<=N;i++){
            r=i+k;
            for(j=0,mindp=INF;j<k;j++){
                mindp=min(mindp,dp[i][i+j]+dp[i+j+1][r]);
            }
            dp[i][r]=mindp+sum(i,r);
        }
    }
    printf("%d\n",dp[1][N]);
return 0;
}
