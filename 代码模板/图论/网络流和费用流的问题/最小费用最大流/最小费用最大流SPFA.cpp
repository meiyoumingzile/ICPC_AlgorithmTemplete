#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct Edge{
    int e,val,cost,k;
    Edge(){}
    Edge(int e,int val,int cost,int k){
        this->e=e;
        this->k=k;
        this->val=val;
        this->cost=cost;
    }
};
struct Graphic{
   int V,E,S,T;
    int size;
    int head[MAX];
    Edge edge[400010];
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(int b,int e,int val,int cost){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,cost,t);
    }
};
Graphic g;
ll dist[MAX];//ά�������������ڶ�̬�滮��dp���飻�����������ʵ��ȡ���ڵ��������ͬ,�±����㣬һ���1��ʼ
Edge p[MAX];//��¼���·����
ll SPFA_flow(ll &cost){//��SPFA����С����������������������ֵ��cost������С�Ѻ�
    int i,j,k,minv;
    ll res[2];
    res[0]=res[1]=0;//res[0]��ʾ�������res[1]��ʾ����
    queue<int>dotQue;
    while(1){
        for(i=1;i<=g.V;i++)//��ʼ�����˵�һ����0�������������
            dist[i]=INF;
        dist[g.S]=0;
        dotQue.push(g.S);
        while(!dotQue.empty()){
            int que_head=dotQue.front();
            dotQue.pop();
            for(i=g.head[que_head];i!=-1;i=g.edge[i].k){
                const int endDot=g.edge[i].e;
                if(g.edge[i].val>0&&dist[que_head]+g.edge[i].cost<dist[endDot]){//������ǵ�λ����
                    p[endDot].e=que_head;
                    p[endDot].val=i;
                    dist[endDot]=dist[que_head]+g.edge[i].cost;
                    dotQue.push(endDot);
                }
            }
        }
        if(dist[g.T]==INF)
            break;
        for(i=g.T,minv=INF;i!=g.S;i=p[i].e){
            minv=min(minv,g.edge[p[i].val].val);
        }
        res[0]+=minv;
        res[1]+=dist[g.T]*minv;
        for(i=g.T;i!=g.S;i=p[i].e){
            k=p[i].val;
            g.edge[k].val-=minv;
            g.edge[k^1].val+=minv;
        }
    }
    cost=res[1];
    return res[0];
}
void print(Graphic &g){
    for(int i=1;i<=g.V;i++){
        for(int j=g.head[i];j!=-1;j=g.edge[j].k){
            //if(g.edge[j].val>0){
                printf("(%d %d %d)",i,g.edge[j].e,g.edge[j].val);
            //}
            //printf("(%d %d %d) ",i,g.edge[j].e,g.edge[j].val);
        }printf("\n");
    }
}
int main(int argc,char *argv[]){
	int i,j,k,b,e,val,cost;
	ll r1,r2; 
	g.clear();
    scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T);
    for(i=0;i<g.E;i++){
        scanf("%d%d%d%d",&b,&e,&val,&cost);
        g.push(b,e,val,cost);
        g.push(e,b,0,-cost);
    }
    r1=SPFA_flow(r2);
    printf("%lld %lld\n",r1,r2);
return 0;
}

