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


vector<Edge > adList[MAXDOT];
int dist[MAXDOT];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
int updateTimes[MAXDOT];

int V,E,S,T;//V是点个数，E是边个数，S是起点编号，T是终点的编号
int SPFA(int start,int V){//start是起点编号，V是点个数
    int i,j;
    queue<int>dotQue;
    memset(updateTimes,0,sizeof(updateTimes));
    for(i=0;i<=V;i++){//初始化除了第一个是0其他都是无穷大
        dist[i]=INF;
    }
    dist[start]=0;
    dotQue.push(start);
    while(!dotQue.empty()){
        int que_head=dotQue.front();
        dotQue.pop();
        for(i=0;i<adList[que_head].size();i++){
            int endDot=adList[que_head][i].e;
            if(dist[que_head]+adList[que_head][i].val<dist[endDot]){
                dist[endDot]=dist[que_head]+adList[que_head][i].val;
                dotQue.push(endDot);
                if(++updateTimes[endDot]>=V){
                    return -1;
                }
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    int i,j,k;
    Edge w;
    cin>>V>>E>>S>>T;
    for(i=0;i<E;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        adList[w.b].push_back(w);
    }
    if(SPFA(S,V)!=-1){
        for(i=1;i<=V;i++){
            printf("%d%c",dist[i],i==V?'\n':' ');
        }
    }
return 0;
}
