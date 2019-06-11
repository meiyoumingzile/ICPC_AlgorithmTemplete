#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
int dp[32222];
bool vis[32222][65];
int cnt[32222];

int N,M;

struct v2{
    int x,y,q,i;
};
v2 A[65];

bool cmp(const v2 &a,const v2 &b){
    return a.q<b.q;
}


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k;
    cin>>N>>M;
    for(i=0;i<M;i++){
        scanf("%d%d%d",&A[i].x,&A[i].y,&A[i].q);
    }
    sort(A,A+M,cmp);
    for(i=0;i<M;i++){
        if(A[i].q==0){
            for(j=N;j>=A[i].x;j--){
                if(dp[j]<=dp[j-A[i].x]+A[i].x*A[i].y){
                    dp[j]=dp[j-A[i].x]+A[i].x*A[i].y;
                    vis[j][i]=true;
                }
            }
        }else{
            for(j=N;j>=A[i].x;j--){
                if(vis[j][A[i].q]&&cnt[j]<2&&dp[j]<=dp[j-A[i].x]+A[i].x*A[i].y){
                    dp[j]=dp[j-A[i].x]+A[i].x*A[i].y;
                    cnt[j]=max(cnt[j],cnt[j-A[i].x]+1);
                }
            }
        }
    }
    printf("%d\n",dp[N]);
return 0;
}
