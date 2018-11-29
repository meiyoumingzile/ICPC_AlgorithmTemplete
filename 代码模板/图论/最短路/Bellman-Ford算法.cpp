#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int MAXDOT=10010;
const int MAXEDGE=10010;
const int INF=2147483647;


struct Edge{//表示边，且是有向边从·b到·e;w是权值
    int b,e,val;
    void sett(int b,int e,int val){
        this->b=b;
        this->e=e;
        this->val=val;
    }
};
vector<Edge>edge;//和迪杰斯特拉算法不一样，要用普通数组储存的是边；邻接表反而麻烦
int dist[MAXDOT];//和迪杰斯特拉算法一样，dist还是代表原点到编号为i的边的最短路

int N,M,S,E;//N是点个数，M是边个数，B是起点编号，E是终点的编号

int BellmanFord(int start,int N){
    int i,j;
    bool isDistUpdate=true;
    for(i=1;i<=N;i++){//初始化除了第一个是0其他都是无穷大
        dist[i]=INF;
    }
    dist[start]=0;
    for(j=1;j<N&&isDistUpdate==true;j++){//循环dotNum-1次·
        isDistUpdate=false;
        for(i=0;i<edge.size();i++){//对于每一条有向边如果满足Distant[u] + w(u, v) < Distant[v]；就让Distant[v] = Distant[u]+w(u, v)
            if(dist[edge[i].b]+edge[i].val<dist[edge[i].e]){
                dist[edge[i].e]=dist[edge[i].b]+edge[i].val;
                isDistUpdate=true;
            }
        }
    }
    for(i=0;i<edge.size();i++){//再遍历一次，判断是否有负环，存在Distant[u] + w(u, v)>Distant[v]则有负环返回-1
        if(dist[edge[i].b]+edge[i].val<dist[edge[i].e]){
            return -1;
        }
    }
    return 1;
}


int main(int argc,char *argv[]){
    int i,j,k;
    Edge w;
    cin>>N>>M>>S>>E;
    edge.reserve(MAXEDGE);
    for(i=0,j=0;i<M;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        edge.push_back(w);
    }
    if(BellmanFord(S,N)!=-1){
        for(i=1;i<=N;i++){
            printf("%d%c",dist[i],i==N?'\n':' ');
        }
    }
    /*for(i=E;i!=0;i=last[i]){
        printf("%d ",i);
    }*/
return 0;
}
/*
4 5
1 2 2
2 3 4
4 3 1
4 2 -2
1 4 1
*/
