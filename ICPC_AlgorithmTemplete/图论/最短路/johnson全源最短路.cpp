#include<bits/stdc++.h>
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
const int MAX=3010;
const int mod=1e9+7;

struct Edge{
    int e,k;
    ll val;
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
    Edge edge[MAX*4];
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

struct Node{
    int i,dis;
    bool operator < (const Node a) const {
        return dis>a.dis;//最小值优先
    }
    void sett(int i,int dis){
        this->i=i;
        this->dis=dis;
    }
};
ll dist[MAX][MAX];//表示起点到编号为i的点的最短路，初始值是INF；
priority_queue<Node>que;
void Dijkstra(int start,Graphic &g){//类似广搜,此算法针对无负数边的图
    int i,j,k;
    Node now,next;
    now.sett(start,0);//等于初始值
    for(i=0;i<=g.V;i++){//初始化除了第一个是0其他都是无穷大
        dist[start][i]=INF;
    }
    dist[start][start]=0;

    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.dis!=dist[start][now.i])//大优化，勿省略
            continue;
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//表示遍历当前点能到达的所有点
            next.i=g.edge[i].e;
            next.dis=now.dis+g.edge[i].val;
            if(dist[start][next.i]>next.dis&&now.i!=next.i){//下一个本身的值大于求得的新值才更新
                dist[start][next.i]=next.dis;
                que.push(next);
            }
        }
    }
}


int h[MAX],updateTimes[MAX];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
bool isQue[MAX];//有没有在队列中
bool SPFA(int start,Graphic &g){//start是起点编号，V是点个数
    rg int i,j,now;
    queue<int>que;
    memset(updateTimes,0,sizeof(updateTimes));
    memset(isQue,0,sizeof isQue);
    for(i=0;i<=g.V;i++){//初始化除了第一个是0其他都是无穷大
        h[i]=INF;
    }
    h[start]=0;
    isQue[start]=1;
    que.push(start);
    while(!que.empty()){
        now=que.front();
        que.pop();
        isQue[now]=0;
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            int endDot=g.edge[i].e;
            if(h[now]+g.edge[i].val<h[endDot]){
                h[endDot]=h[now]+g.edge[i].val;
                if(!isQue[endDot]){
                    isQue[endDot]=1;
                    que.push(endDot);
                    if(++updateTimes[endDot]>=g.V+1){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

bool Johnson(Graphic &g){//返回有无负环,g会被改造
    int i,j,k;
    for(i=1;i<=g.V;i++){
        g.push(0,i,0);
    }
    if(SPFA(0,g)){
        for(i=1;i<=g.V;i++){
            for(j=g.head[i];j!=-1;j=g.edge[j].k){
                g.edge[j].val+=h[i]-h[g.edge[j].e];
                if( g.edge[j].val < 0){
                    printf("erro\n");
                    return 0;
                }
            }
        }
        for(i=1;i<=g.V;i++){
            Dijkstra(i,g);
            for(j=1;j<=g.V;j++){
                if(dist[i][j]!=INF)
                    dist[i][j]+=h[j]-h[i];
            }
        }
    }else{
        return 0;
    }
    return 1;
}



int main(){

   // freopen("P5905_11.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
   // freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    int i,j,k,T,u,v,val,s;
    g.clear();
    scanf("%d",&g.V);
    scanf("%d",&g.E);
    for(i=0;i<g.E;i++){
        scanf("%d",&u);
        scanf("%d",&v);
        scanf("%d",&val);
        g.push(u,v,val);
       // g.push(v,u,val);
    }
    if(Johnson(g)){
        for(i=1;i<=g.V;i++){
            ll sum=0;
            for(j=1;j<=g.V;j++){
                if(dist[i][j]==INF)
                    dist[i][j]=1e9;
                sum+=j*dist[i][j];
            }
            printf("%lld\n",sum);
        }
    }else{
        printf("-1\n");
    }
return 0;
}
/*
3 3
1 2 4
1 3 2
3 2 -4

*/
