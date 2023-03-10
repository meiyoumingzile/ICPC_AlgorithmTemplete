#include <bits/stdc++.h>
using namespace std;
#define ll long long

int a[150][150];
int dp[(1<<11)][20];
int xx[20],yy[20];

int cnt;

double tsp(){
  int M = (1 << N);
  // M就是第四部分所说的V’状态总数，1<<N表示2^N，总共有2^N种状态
  dp[1][0] = 0;
  // 假设固定出发点为0，从0出发回到0的花费为0。TSP只要求是一个环路，所以出发点可以任选
  for (int i = 1; i < M; i ++){
  // 枚举V’的所有状态
    for (int j = 1; j < N; j ++){
    // 选择下一个加入集合的城市
      if (i & (1 << j)) continue;
      // 城市已经存在于V’之中
      if (!(i & 1)) continue;
      // 出发城市固定为0号城市
      for (int k = 0; k < N; k ++){
      // 在V’这个城市集合中尝试每一个结点，并求出最优解
        if (i & (1 << k)){
        // 确保k已经在集合之中并且是上一步转移过来的结点
           dp[(1 << j) | i][j] = min(dp[(1 << j) | i][j], dp[i][k] + dis[k][j]); // 转移方程
          } // 将j点加入到i集合中
      }
    }
  }
  for (int i = 0; i < N; i ++)
  ans = min(dp[M - 1][i] + dis[i][0], ans);
  // 因为固定了出发点，所以要加上到城市0的距离。另外要从所有的完成整个环路的集合V’中选择，完成最后的转移
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
