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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int limPrice,N,i,j;
    scanf("%d%d",&limPrice,&N);
    for(i=1;i<=N;i++){
        scanf("%d%d",&pr[i],&val[i]);
    }
    for(i=1;i<=N;i++){
        for(j=limPrice;j>=pr[i];j--){
            dp[i][j]=max(dp[i-1][j-pr[i]]+pr[i]*val[i],dp[i-1][j]);//������ǰi-1���ļ�ֵ���þ��ǣ�[i-1][j-pr[i]]�ļ�ֵ���ݹ������ϵ���
        }
        for(;j>=0;j--){
            dp[i][j]=dp[i-1][j];
        }
    }
    printf("%d\n",dp[N][limPrice]);
return 0;
}
