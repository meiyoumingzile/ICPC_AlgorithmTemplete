#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
int T,N;
int dp[100010];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,x,y;
    cin>>T>>N;
    for(i=0;i<N;i++){
        scanf("%d%d",&x,&y);
        for(j=x;j<=T;j++){
            k=1;
            dp[j]=max(dp[j],dp[j-k*x]+y*k);
        }
    }
    printf("%d\n",dp[T]);
return 0;
}
