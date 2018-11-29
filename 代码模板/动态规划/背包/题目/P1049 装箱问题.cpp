#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
int dp[20010];
int n;

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,val,V;
    cin>>V>>n;
    for(i=0;i<n;i++){
        scanf("%d",&val);
        for(j=V;j>=val;j--){
            dp[j]=max(dp[j],dp[j-val]+val);
        }
    }
    printf("%d\n",V-dp[V]);
return 0;
}
