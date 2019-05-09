#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
int dp[1010][1010];
char str[1010];

int getdp(int i,int j){
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
    if(i==j){
        dp[i][j]=1;
    }else if(j-i==1){
        dp[i][j]=str[i]==str[j];
    }else{
        dp[i][j]=str[i]==str[j]&&getdp(i+1,j-1);
    }
    return dp[i][j];
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,n,len,maxLen;
    cin>>str;
    len=strlen(str);
    memset(dp,-1,sizeof(dp));

    for(i=0,maxLen=0;i<len;i++){
        for(j=i;j<len;j++){
            if(getdp(i,j)==1){
                maxLen=max(maxLen,j-i+1);
            }
        }
    }
    printf("%d\n",maxLen);
return 0;
}
