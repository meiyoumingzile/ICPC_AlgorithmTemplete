#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
int dp[1010];//1ά�����01����д��
int T,N;

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,x,y;
    cin>>T>>N;
    for(i=0;i<N;i++){
        scanf("%d%d",&x,&y);
        for(j=T;j>=x;j--){
            dp[j]=max(dp[j],dp[j-x]+y);
        }
    }
    printf("%d\n",dp[T]);


return 0;
}
