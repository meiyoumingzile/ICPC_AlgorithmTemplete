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

int adMatrix[MAX][MAX];//�ڽӾ���ע���ʼ��ΪINF,�±��1��ʼ
void initMatrix(int N){
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            adMatrix[i][j]=(j==i?0:INF);
        }
    }
}
int dis[MAX][MAX],path[MAX][MAX];//path�����Ǵ�i��j��Ҫ�����н�����ĸ�
void FloydWarshall(int N){//dis��ʼ������,i==j��0��������INF
    int i,j,k;
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
            dis[i][j]=adMatrix[i][j];//��ʵ��dis�����ʼ���ǳ�ʼ���ڽӾ���
            path[i][j]=j;
        }
    }
    for(k=1;k<=N;k++){
        for(i=1;i<=N;i++){
            for(j=1;j<=N;j++){
                if(dis[i][k]==INF||dis[k][j]==INF){//i��iΪ�����INF

                }else if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];//������·��
                    path[i][j]=path[i][k];//��i��j�����·�����н���ɴ�i��k���н��

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
