#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

//��EK+spfa��ת���������������ʱ����Ϊ�кܶ�������
struct Edge{
    int e,val,k,cost;
    Edge(){}
    Edge(const int &e,const int &val,const int &cost,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
        this->cost=cost;
    }
};
struct Graphic{//�������ͼ����ʽǰ����
    int V,E,size,S,T;
    int head[MAX];
    Edge edge[2000010];
    inline void push(const int &b,const int &e,const int &val,const int &cost){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,cost,t);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;

int dist[MAX];//ά�������������ڶ�̬�滮��dp���飻�����������ʵ��ȡ���ڵ��������ͬ,�±����㣬һ���1��ʼ
Edge p[MAX];//��¼���·����
ll SPFA_flow(ll &cost){//��SPFA����С����������������������ֵ���Լ���С�Ѻ� res[0]��ʾ�������res[1]��ʾ����,��ֵ��cost���� 
    int i,j,k,minv;
    ll res[2];
    res[0]=res[1]=0;
    queue<int>dotQue;
    while(1){
        for(i=1;i<=g.V;i++)//��ʼ�����˵�һ����0�������������
            dist[i]=-INF;
        dist[g.S]=0;
        dotQue.push(g.S);
        while(!dotQue.empty()){
            int que_head=dotQue.front();
            dotQue.pop();
            for(i=g.head[que_head];i!=-1;i=g.edge[i].k){
                const int endDot=g.edge[i].e;
                if(g.edge[i].val>0&&dist[que_head]+g.edge[i].cost>dist[endDot]){//�����������
                    p[endDot].e=que_head;
                    p[endDot].val=i;
                    dist[endDot]=dist[que_head]+g.edge[i].cost;
                    dotQue.push(endDot);
                }
            }
        }
        if(dist[g.T]==-INF)
            break;
        for(i=g.T,minv=INF;i!=g.S;i=p[i].e)
            minv=min(minv,g.edge[p[i].val].val);
        res[0]+=minv;
        res[1]+=dist[g.T];
        for(i=g.T;i!=g.S;i=p[i].e){
            k=p[i].val;
            g.edge[k].val-=minv;
            g.edge[k^1].val+=minv;
        }
    }
    cost=res[1];
    return res[0];
}
int main(){
	int i,j,k,T=0,n,cost;
	ll ans;//��С���� 
    while(~scanf("%d",&n)){//x���ϱ�Ż���ԭ���ģ�y����ż�n
        g.clear();
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                scanf("%d",&cost);
                g.push(i,j+n,INF,cost);
                g.push(j+n,i,0,-cost);
            }
        }
        g.V=2*n+2;
        g.S=2*n+1;//���
        g.T=2*n+2;//�յ�
        for(i=1;i<=n;i++){//�����㵽x���ϵı�
            g.push(g.S,i,1,0);
            g.push(i,g.S,0,0);
        }
        for(i=1;i<=n;i++){//���y���ϵ��յ�ı�
            g.push(i+n,g.T,1,0);
            g.push(g.T,i+n,0,0);
        }
        SPFA_flow(ans);
        printf("%lld\n",cost);//res[1]����
    }
return 0;
}

