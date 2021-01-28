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
    Edge edge[MAX*2];
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
        return dis>a.dis;//��Сֵ����
    }
    void sett(int i,int dis){
        this->i=i;
        this->dis=dis;
    }
};
int dist[MAX];//��ʾ��㵽���Ϊi�ĵ�����·����ʼֵ��INF��
priority_queue<Node>que;
//bool vis[MAXDOT];//��ʾ��û��������У�//0��ʾ��û��ӹ�
int last[MAX];//��ʾ��ǰ�����·���µ���һ�������ĸ�������������·��
void Dijkstra(int start){//���ƹ���,���㷨����޸����ߵ�ͼ
    int i,j,k;
    Node now,next;
    now.sett(start,0);//���ڳ�ʼֵ
    memset(dist,127,sizeof dist);
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.dis!=dist[now.i])//���Ż�����ʡ��
            continue;
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//��ʾ������ǰ���ܵ�������е�
            next.i=g.edge[i].e;
            next.dis=now.dis+g.edge[i].val;
            if(dist[next.i]>next.dis&&now.i!=next.i){//��һ�������ֵ������õ���ֵ�Ÿ���
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

int main(){
    int i,j,k,T,u,v,val,s;
    g.clear();
    scan(g.V);scan(g.E);scan(s);
    for(i=0;i<g.E;i++){
        scan(u);scan(v);scan(val);
        g.push(u,v,val);
       // g.push(v,u,val);
    }
    Dijkstra(s);
    for(i=1;i<=g.V;i++){
        printf("%d%c",dist[i],i==g.V?'\n':' ');
    }
return 0;
}
