#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

int N,M;
int dp[110][10010];//����ǰi�ֲ˻���jԪ������ֵ����ֵ���ڻ�Ǯ��
int A[110];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
