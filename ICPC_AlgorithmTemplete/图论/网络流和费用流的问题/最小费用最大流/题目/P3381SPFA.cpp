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
    int size=0;
    int head[MAX];
    Edge edge[400010];
    Graphic(){
        memset(head,-1,sizeof(head));
    }
    void push(int b,int e,int val,int cost){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,cost,t);
    }
};
Graphic g;
int dist[MAX];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
Edge p[MAX];//记录最短路径；
ll *SPFA_flow(){//用SPFA求最小费用最大流，返回最大流数值，以及最小费和
    register int i,j,k,minv;
    ll *res=new ll[2];
    res[0]=res[1]=0;//res[0]表示最大流，res[1]表示费用
    queue<int>dotQue;
    while(1){
        //求最短路的SPFA算法,不需要判断环
        for(i=1;i<=g.V;i++)//初始化除了第一个是0其他都是无穷大
            dist[i]=INF;
        dist[g.S]=0;
        dotQue.push(g.S);
        while(!dotQue.empty()){
            int que_head=dotQue.front();
            dotQue.pop();
            for(i=g.head[que_head];i!=-1;i=g.edge[i].k){
                const int endDot=g.edge[i].e;
                if(g.edge[i].val>0&&dist[que_head]+g.edge[i].cost<dist[endDot]){//这道题是单位流量
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
    return res;
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
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,b,e,val,cost;
    scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T);
    for(i=0;i<g.E;i++){
        scanf("%d%d%d%d",&b,&e,&val,&cost);
        g.push(b,e,val,cost);
        g.push(e,b,0,-cost);
    }
    ll *res=SPFA_flow();
    printf("%lld %lld\n",res[0],res[1]);
return 0;
}

