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
    if(dp[i][j]){
        return dp[i][j];
    }else if(i==j){
        dp[i][j]=1;
    }else if(j-i==1){
        dp[i][j]=str[i]==str[j]?2:1;
    }else if(str[i]==str[j]){
        dp[i][j]=getdp(i+1,j-1)+2;
    }else{
        dp[i][j]=max(getdp(i,j-1),getdp(i+1,j));
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
    memset(dp,0,sizeof(dp));
    for(i=0,maxLen=0;i<len;i++){
        //printf("");
        for(j=i;j<len;j++){

            maxLen=max(maxLen,getdp(i,j));

        }
    }
    printf("%d\n",maxLen);
return 0;
}
