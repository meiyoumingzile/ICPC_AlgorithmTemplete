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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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

