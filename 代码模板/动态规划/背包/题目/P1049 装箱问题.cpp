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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
