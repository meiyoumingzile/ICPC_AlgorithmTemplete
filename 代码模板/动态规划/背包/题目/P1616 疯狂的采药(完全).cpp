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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
