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
const int MAX=100010;
const int mod=1e9+7;

struct Edge{
    int e,val,k,time;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX],len[MAX];
    Edge edge[MAX];
    void push(const int &b,const int &e,const int &val){
        len[b]++;
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
        memset(len,0,sizeof(len));
    }
};
Graphic g,g1;

int du[MAX],ve[MAX],vl[MAX];//代表点的入度
int dist[MAX],next[MAX];
map<pair<int,int>,int>ge,gl;
bool exKahn(){//有向图存在环返回0
    int i,j,k,now;
    memset(du,0,sizeof(du));
    memset(ve,0,sizeof(ve));
    memset(vl,127,sizeof(vl));
    ve[g.S]=0;
    stack<int>st;
    for(i=1;i<=g.V;i++){
        for(j=g.head[i];~j;j=g.edge[j].k){
            du[g.edge[j].e]++;
        }
    }
    for(i=1;i<=g.V;i++){
        if(du[i]==0)
            st.push(i);
    }
    while(!st.empty()){
        now=st.top();
        st.pop();
       // printf("%d ",now);
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            const int &v=g.edge[i].e;
            ve[v]=max(ve[v],ve[now]+g.edge[i].val); //
            g.edge[i].time=ve[now];  //
            if((--du[v])==0){
                st.push(v);
            }
        }
    }
    //以上是正拓扑排序
    for(i=1;i<=g.V;i++){//检测是不是无环图
        if(du[i]>0){
            return 0;
        }
    }
    //以下是逆拓扑排序
    vl[g.T]=ve[g.T];
    for(i=1;i<=g.V;i++){
        du[i]=g.len[i];
    }
    for(i=1;i<=g.V;i++){
        if(du[i]==0)
            st.push(i);
    }
    while(!st.empty()){
        now=st.top();
        st.pop();
       // printf("%d ",now);
        for(i=g1.head[now];i!=-1;i=g1.edge[i].k){
            const int &v=g1.edge[i].e;
            vl[v]=min(vl[v],vl[now]-g1.edge[i].val); //
            g1.edge[i].time=vl[now]-g1.edge[i].val;  //
            if((--du[v])==0){
                st.push(v);
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
	int i,u,v,val,j;
	/*
	输入一个图，如果是DAG输出关键路径和相关属性，否则输出"图中有环"
	*/
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        g1.clear();
        scanf("%d%d",&g.S,&g.T);
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            g.push(u,v,val);
            g1.push(v,u,val);
        }
        if(exKahn()){
            printf("i,ve,vl\n");
            for(i=1;i<=g.V;i++){
                printf("%d:(%d %d) ",i,ve[i],vl[i]);
            }printf("\n");
            for(i=1;i<=g.V;i++){
                printf("%d:: ",i);
                for(j=g.head[i];~j;j=g.edge[j].k){
                    printf("(%d->%d):(%d %d) ",i,g.edge[j].e,g.edge[j].time,g1.edge[j].time);
                }printf("\n");
            }
        }else{
            printf("有向图存在环\n");
        }
	}
return 0;
}
/*
6 8
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5

6 9
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5
5 6

9 12
1 9
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 1
5 7 5
5 8 3
5 6 0
6 8 4
7 9 2
8 9 4
*/
