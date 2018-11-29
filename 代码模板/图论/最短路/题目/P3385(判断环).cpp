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
const int INF=2139062143;////2139062143
const int MAX=2010;
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
    Graphic(){
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
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
    void pushMin(const int &b,const int &e,const int &val){//加入边如果存在更新成最小，可以修改这个函数
        rg int i;
        for(i=head[b];i!=-1&&edge[i].e!=e;i=edge[i].k);
        if(i==-1){
            push(b,e,val);
        }else{
            edge[i].val=min(edge[i].val,val);
        }
    }
};
Graphic g;

int dist[MAX];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
int updateTimes[MAX];

bool SPFA(int start,Graphic &g){//start是起点编号，V是点个数
    rg int i,j,now;
    queue<int>que;
    dist[start]=0;
    que.push(start);
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            cint endDot=g.edge[i].e;
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
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,j,k,t,T,n,w,u,v,val,mindis,s=1;
	scanf("%d",&T);
    while(T--){
        scanf("%d%d",&g.V,&g.E);
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            if(val<0){
                g.pushMin(u,v,val);
            }else{
                g.pushMin(u,v,val);
                g.pushMin(v,u,val);
            }
        }
        memset(updateTimes,0,sizeof(updateTimes));
        memset(dist,127,sizeof(dist));
        for(i=1;i<=g.V;i++){
            if(updateTimes[i]==0){
                if(SPFA(i,g)==0){
                    break;
                }
            }
        }
        if(i==g.V+1){
            printf("N0\n");
        }else{
            printf("YE5\n");
        }
    }
return 0;
}

