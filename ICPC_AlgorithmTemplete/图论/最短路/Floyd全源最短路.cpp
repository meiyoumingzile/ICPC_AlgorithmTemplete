#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=100000000;
const int MAX=110;

int adMatrix[MAX][MAX];//邻接矩阵，注意初始化为INF,下表从1开始
void initMatrix(int N){
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            adMatrix[i][j]=(j==i?0:INF);
        }
    }
}
int dis[MAX][MAX],path[MAX][MAX];//path代表是从i到j需要经过中介点是哪个
void FloydWarshall(int N){//dis初始化规则,i==j是0，否则是INF
    int i,j,k;
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
            dis[i][j]=adMatrix[i][j];//事实上dis数组初始就是初始的邻接矩阵
            path[i][j]=j;
        }
    }
    for(k=1;k<=N;k++){
        for(i=1;i<=N;i++){
            for(j=1;j<=N;j++){
                if(dis[i][k]==INF||dis[k][j]==INF){//i到i为无穷大INF

                }else if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];//变成最短路径
                    path[i][j]=path[i][k];//从i到j的最短路径的中介点变成从i到k的中介点

                }
            }
        }
    }
}
void printAll(int N){
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            printf("%d ",dis[i][j]);
        }printf("\n");
    }
}
int main(int argc,char *argv[]){
    int N,M,i,j,b,e,w;
    scanf("%d%d",&N,&M);
    initMatrix(N);
    for(i=0;i<M;i++){
        scanf("%d%d%d",&b,&e,&w);
        adMatrix[b][e]=min(w,adMatrix[b][e]);
       // adMatrix[e][b]=min(w,adMatrix[e][b]);
    }
    FloydWarshall(N);
    printAll(N);
return 0;
}
