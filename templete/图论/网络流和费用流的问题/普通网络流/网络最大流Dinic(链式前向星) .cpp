#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
/*
以洛谷3376为例，数据比较特殊，输入数据不存在相互反向的边，邻接表可以储存反向边编号优化，链式前向星可以用数组相邻元素边存储相反边方式优化，目的是能用o1时间找到相反边而不是迭代寻找。
*/
struct Edge{
    int e,val,k;
    Edge(){}
    Edge(cint e,cint val,cint k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{//链式前向星实现
    int V,E,S,T;//点数边数，起点终点
    int size;
    int head[MAX];
    Edge edge[300010];
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void fpush(const int &b,const int &e,const int &val){
        push(b,e,val);
        push(e,b,0);
    }
};
Graphic g;
struct Dot{//bfs用
    int d,len;
    Dot(){}
    Dot(cint d,cint len){
        this->d=d;
        this->len=len;
    }
};

int layer[MAX],cur[MAX];//layer是分层，cur当前弧优化
bool Dinic_bfs(Graphic &g){//分层,只需要找到T点即可停止，找不到T返回false
    rg int i,minv=INF,b,e;
    queue<Dot>que;
    Dot now(g.S,0),next;
    memset(layer,-1,sizeof(layer));
    for(i=1;i<=g.V;i++)cur[i]=g.head[i];
    layer[g.S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.front();
        que.pop();
        if(now.d==g.T)
            return 1;
        for(i=g.head[now.d];i!=-1;i=g.edge[i].k){
            e=g.edge[i].e;
            if(layer[e]==-1&&g.edge[i].val>0){
                next.d=e;
                layer[e]=next.len=now.len+1;
                que.push(next);
            }
        }
    }
    return 0;
}
int Dinic_dfs(int now,Graphic &g,int minv){
    if(minv==0||now==g.T)
        return minv;
    int ans=0,val;
    for(int i=cur[now];i!=-1;i=g.edge[i].k){
        cur[now]=i;
        if(layer[g.edge[i].e]==layer[now]+1){
            val=Dinic_dfs(g.edge[i].e,g,min(minv,g.edge[i].val));
            if(val>0){
                ans+=val;
                minv-=val;
                g.edge[i].val-=val;
                g.edge[i^1].val+=val;
                if(minv<=0)
                    break;
            }
        }
    }
    return ans;
}
int Dinic(Graphic &g){
    int sumVal=0;
    while(Dinic_bfs(g)){//多次调用直到不能分层
        sumVal+=Dinic_dfs(g.S,g,INF);
    }
    return sumVal;
}
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
	int i,j,k,b,e,v;
    scan(g.V);scan(g.E);scan(g.S);scan(g.T);
    g.clear();
    for(i=0;i<g.E;i++){
        scan(b);scan(e);scan(v);
        g.push(b,e,v);
        g.push(e,b,0);
    }
    printf("%d\n",Dinic(g));
return 0;
}

