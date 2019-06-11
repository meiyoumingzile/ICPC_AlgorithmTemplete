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
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=1010;
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
    int V,E,S,T,size;
    int head[MAX];
    Edge edge[200010];
    Graphic(){}
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void pushMin(const int &b,const int &e,const int &val){//�����������ڸ��³���С�������޸��������
        rg int i;
        for(i=head[b];i!=-1&&edge[i].e!=e;i=edge[i].k);
        if(i==-1){
            push(b,e,val);
        }else{
            edge[i].val=min(edge[i].val,val);
        }
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
	void println(){
        int i,j,next;
        for(i=1;i<=V;i++){
            printf("%d:::",i);
            for(j=head[i];j!=-1;j=edge[j].k){
                printf("%d ",edge[j].e);
            }printf("\n");
        }
    }
};
Graphic g,ig;//ig�Ƿ���ͼ
struct Node{
    int i;
    ll dis;
    bool operator < (const Node a) const {
        return dis>a.dis;//��Сֵ����
    }
    void sett(cint i,cll dis){
        this->i=i;
        this->dis=dis;
    }
};
ll dist[MAX];//��ʾ��㵽���Ϊi�ĵ�����·����ʼֵ��INF��
priority_queue<Node>que;//a*�͵Ͻ�˹��������һ����
void Dijkstra(Graphic &g){
    int i,j,k;
    Node now,next;
    now.sett(g.S,0);//���ڳ�ʼֵ
    memset(dist,-1,sizeof dist);//-1��ʾ�����
    dist[g.S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.dis!=dist[now.i])//���Ż�����ʡ��
            continue;
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//��ʾ������ǰ���ܵ�������е�
            next.i=g.edge[i].e;
            next.dis=now.dis+g.edge[i].val;
            if(dist[next.i]==-1||dist[next.i]>next.dis){//��һ�������ֵ������õ���ֵ�Ÿ���
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}

ll A_star(Graphic &g,int K){//Ѱ�ҵ�k��·���ҵ�������ֵ��û�ҵ�����-1
    if(dist[g.S]==-1)
        return -1;
    Node now,next;
    int tcnt=0;//�յ���Ӵ���
    now.sett(g.S,dist[g.S]);
    que.push(now);
    if(g.T==g.S)//����յ���ͬһ����,��ʼ�������һ�Σ�Ҫ������
        K++;
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.i==g.T){
            tcnt++;
            if(tcnt==K)
                return now.dis;
        }
        for(int i=g.head[now.i];i!=-1;i=g.edge[i].k){
            next.dis=now.dis-dist[now.i]+g.edge[i].val+dist[g.edge[i].e];
            next.i=g.edge[i].e;
            que.push(next);
        }
    }
    return -1;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,u,v,val;
	while(~scanf("%d%d",&g.V,&g.E)){//k��·
	    g.clear();
	    ig.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            g.push(u,v,val);
            ig.push(v,u,val);
        }
        scanf("%d%d%d",&g.S,&g.T,&k);
        ig.S=g.T;
        Dijkstra(ig);//��ʼ���������·����Ϊa*��h(x);
        printf("%lld\n",A_star(g,k));
	}
return 0;
}

