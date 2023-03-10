#include <bits/stdc++.h>
using namespace std;
#define ll long long

int a[150][150];
int dp[(1<<11)][20];
int xx[20],yy[20];

int cnt;

double tsp(){
  int M = (1 << N);
  // M���ǵ��Ĳ�����˵��V��״̬������1<<N��ʾ2^N���ܹ���2^N��״̬
  dp[1][0] = 0;
  // ����̶�������Ϊ0����0�����ص�0�Ļ���Ϊ0��TSPֻҪ����һ����·�����Գ����������ѡ
  for (int i = 1; i < M; i ++){
  // ö��V��������״̬
    for (int j = 1; j < N; j ++){
    // ѡ����һ�����뼯�ϵĳ���
      if (i & (1 << j)) continue;
      // �����Ѿ�������V��֮��
      if (!(i & 1)) continue;
      // �������й̶�Ϊ0�ų���
      for (int k = 0; k < N; k ++){
      // ��V��������м����г���ÿһ����㣬��������Ž�
        if (i & (1 << k)){
        // ȷ��k�Ѿ��ڼ���֮�в�������һ��ת�ƹ����Ľ��
           dp[(1 << j) | i][j] = min(dp[(1 << j) | i][j], dp[i][k] + dis[k][j]); // ת�Ʒ���
          } // ��j����뵽i������
      }
    }
  }
  for (int i = 0; i < N; i ++)
  ans = min(dp[M - 1][i] + dis[i][0], ans);
  // ��Ϊ�̶��˳����㣬����Ҫ���ϵ�����0�ľ��롣����Ҫ�����е����������·�ļ���V����ѡ���������ת��
  return ans;
}

int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(a,0,sizeof(a));
        cnt=0;
        xx[0]=yy[0]=0;
        cnt++;
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            {
                int t;
                scanf("%d",&t);
                if(t)
                {
                    xx[cnt]=i,yy[cnt]=j;
                    a[i][j]=cnt++;
                }
            }
            printf("%d\n",dfs(1,0));
    }
    return 0;
}
