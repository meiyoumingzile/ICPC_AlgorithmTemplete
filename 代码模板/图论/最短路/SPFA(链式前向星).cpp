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
#include<set>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*5];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;

int dist[MAX],updateTimes[MAX];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
bool SPFA(int start,Graphic &g){//start是起点编号，V是点个数
    rg int i,j,now;
    queue<int>que;
    memset(updateTimes,0,sizeof(updateTimes));
    for(i=0;i<=g.V;i++){//初始化除了第一个是0其他都是无穷大
        dist[i]=INF;
    }
    dist[start]=0;
    que.push(start);
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            int endDot=g.edge[i].e;
            if(dist[now]+g.edge[i].val<dist[endDot]){
                dist[endDot]=dist[now]+g.edge[i].val;
                que.push(endDot);
                if(++updateTimes[endDot]>=g.V){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
	rg int i,j,k,t,T,n,w,u,v,val,mindis,s;
    while(~scanf("%d%d%d",&g.V,&g.E,&s)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            g.push(u,v,val);
        }
        if(SPFA(s,g)){
            for(i=1;i<=g.V;i++){
                printf("%d%c",dist[i],i==g.V?'\n':' ');
            }
        }
    }
return 0;
}

