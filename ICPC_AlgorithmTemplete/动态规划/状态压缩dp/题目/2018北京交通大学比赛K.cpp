#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=40010;
const int mod=1e9+7;

int dp[MAX][16];

int dis[20][20];
int p2[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};

bool getBin(int x,int i){//二进制位是1返回false;
     return (x >> i ) % 2==0;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,h,next,n,up,mindp;

    cin>>n;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&dis[i][j]);
        }
    }
    if(n<=1){
        printf("0\n");
        return 0;
    }
    up=p2[n]-1;
    mindp=INF;
    for(h=0;h<n;h++){
        memset(dp,-1,sizeof(dp));
        dp[p2[h]][h]=0;
        for(i=p2[h];i<=up;i++){
            for(j=0;j<n;j++){
                if(dp[i][j]==-1)
                    continue;
                for(k=0;k<n;k++){
                    if(getBin(i,k)){
                        next=i+p2[k];
                        if(dp[next][k]>-1){
                            dp[next][k]=min(dp[next][k],dp[i][j]+dis[j][k]);
                        }else{
                            dp[next][k]=dp[i][j]+dis[j][k];
                        }
                    }
                }
            }
        }
        k=INF;
        for(i=0;i<n;i++){
            if(i!=h){
                k=min(k,dp[up][i]+dis[i][h]);
            }
        }
        //printf("%d ",k);
        mindp=min(mindp,k);
    }
    printf("%d\n",mindp);
return 0;
}
/*
3
0 2 5
1 0 6
3 3 0
*/
