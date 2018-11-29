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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
