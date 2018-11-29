#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAX=1000010;
const int dotNum=10010;
const int mod=1e9+7;

struct Edge{//表示边，且是有向边从·b到·e;w是权值
    int b,e,val;
    void sett(int b,int e,int val){
        this->b=b;
        this->e=e;
        this->val=val;
    }
};
struct number{
    int i,dis;
    bool operator < (const number &a) const {
        return dis>a.dis;//最小值优先
    }
    void sett(int i,int dis){
        this->i=i;
        this->dis=dis;
    }
};
vector<Edge>adList[dotNum];//邻接表，adList[i][j]表示编号为I的点到它可以到达的第j条边的信息，j从0开始
int dist[dotNum];//表示起点到编号为i的点的最短路，初始值是INF；
priority_queue<number>que;
//bool vis[dotNum];//表示有没有入过队列；//0表示还没入队过
//int last[dotNum];//表示当前点最短路径下的上一个点是哪个，用了输出最短路径

int N,M,S,E;//N是点个数，M是边个数，B是起点编号，E是终点的编号

void Dijkstra(int start){//类似广搜,此算法针对无负数边的图
    int i,j,k;
    number now,next;
    now.sett(start,0);//等于初始值
    for(i=1;i<=N;i++)
        dist[i]=INF;
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        for(i=0;i<adList[now.i].size();i++){//表示遍历当前点能到达的所有点
            next.i=adList[now.i][i].e;
            next.dis=dist[now.i]+adList[now.i][i].val;
            if(dist[next.i]>=next.dis){//下一个本身的值大于求得的新值才更新
                dist[next.i]=next.dis;
                que.push(next);
                last[next.i]=now.i;
            }
        }
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k;
    Edge w;
    cin>>N>>M>>S;
    for(i=0;i<M;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        adList[w.b].push_back(w);
    }
    Dijkstra(S);
    for(i=1;i<=N;i++){
        printf("%d%c",dist[i],i==N?'\n':' ');
    }
return 0;
}
