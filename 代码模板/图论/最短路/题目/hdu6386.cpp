#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
//#include<windows.h>
using namespace std;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

/*
//���·СС���Σ��ߵ�·���Ȳ���Ȩֵ�������ǿ�����һ����Ȩֵ�Ƿ���ȣ�����ȳ�������1,����Ͳ���Ҫ���ѳ���
�ڵϽ�˹�����Ķ��нṹ�����ά��һ��val��ʾ�ϸ��ߵ�Ȩֵ���ɣ����߿��������ʾҲ����
*/

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int e,const int val,const int k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,sz;
    int head[MAX];
    Edge edge[4*MAX];
    Graphic(){
        this->clear();
    }
    void push(const int b,const int e,const int val){
        int t=head[b];
        head[b]=sz;
        edge[sz++]=Edge(e,val,t);
    }
	void clear(){
        sz=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
struct Node{
    int i,dis,val;
    bool operator < (const Node a) const {
        return dis>a.dis;//��Сֵ����
    }
};
int dist[MAX];//��ʾ��㵽���Ϊi�ĵ�����·����ʼֵ��INF��
priority_queue<Node>que;
//bool vis[MAXDOT];//��ʾ��û��������У�//0��ʾ��û��ӹ�
void Dijkstra(int start){//���ƹ���,���㷨����޸����ߵ�ͼ
    int i,j,k;
    Node now,next;
    now.i=start;
    now.dis=0;
    now.val=0;
    for(i=1;i<=g.V;i++)
        dist[i]=INF;
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//��ʾ������ǰ���ܵ�������е�
            next.i=g.edge[i].e;
            next.dis=dist[now.i]+(now.val!=g.edge[i].val);
            if(dist[next.i]>next.dis){//��һ�������ֵ������õ���ֵ�Ÿ���
                next.val=g.edge[i].val;
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}

int main(){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,T,u,v,val;
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            if(u!=v){

                    g.push(u,v,val);
                    g.push(v,u,val);

            }
        }
        Dijkstra(1);
        if(dist[g.V]==INF){
            dist[g.V]=-1;
        }
        printf("%d\n",dist[g.V]);
	}
return 0;
}

