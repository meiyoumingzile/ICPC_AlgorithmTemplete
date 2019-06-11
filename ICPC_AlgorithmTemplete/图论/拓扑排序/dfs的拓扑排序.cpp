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
        clear();
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
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
	/*void pop(int u,int i){
        if(edge[i].p==-1){
            head[u]=edge[i].k;
            edge[head[u]].p=-1;
        }else{
            edge[edge[i].p].k=edge[i].k;
            edge[edge[i].k].p=edge[i].p;
        }
    }*/
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
Graphic g;

int du[MAX],vis[MAX];//代表点的入度
bool dfs(int now){//保证每次搜索都是入度为0的点
    int i,ans=1;
    printf("%d ",now);
    /*
    做操作
    */
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        du[g.edge[i].e]--;
        if(du[g.edge[i].e]==0){//保证每次搜索都是入度为0的点
            ans*=dfs(g.edge[i].e);
        }else if(du[g.edge[i].e]<0){//-1说明有环
            return 0;
        }
    }
    return ans;
}
bool topologicalSort(Graphic &g){//有向图存在环返回0
    rg int i,j;
    memset(du,0,sizeof(du));
    for(i=1;i<=g.V;i++){
        for(j=g.head[i];j!=-1;j=g.edge[j].k){
            du[g.edge[j].e]++;
        }
    }
    stack<int>st;
    for(i=1;i<=g.V;i++){//应该存下来再dfs
        if(du[i]==0)
            st.push(i);
    }
    while(!st.empty()){
        if(dfs(st.top())==0){//dfs结果是0代表右环
            return 0;
        }
        st.pop();
    }
    for(i=1;i<=g.V;i++){//检测是不是无环图
        if(du[i]>0){
            return 0;
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,u,v,val;
	/*
	输入一个图，如果是有向无环图输出拓扑序，否则输出图中有环
	*/
	while(1){
        g.clear();
        scanf("%d%d",&g.V,&g.E);
        for(i=0;i<g.E;i++){
            scanf("%d%d",&u,&v);
            g.push(u,v,val);
        }
        if(topologicalSort(g)){

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
*/
