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
const int MAX=10010;
const int mod=1e9+7;
/*
给定一个n个点m条边有向图，每个点有一个权值，求一条路径，使路径经过的点权值之和最大。你只需要求出这个权值和。
允许多次经过一条边或者一个点，但是，重复经过的点，权值只计算一次。
*/
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
    Edge edge[100010];
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
Graphic g,g1;

bool vis[MAX],inSt[MAX];//标记是不是被找过了,inSt是否在栈里面
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
stack<int>st;
int kind[MAX],kval[MAX],dval[MAX];//某个点属于哪个联通分量
int newCnt=0;
void tarjan(int now,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        next=g.edge[i].e;
        if(dfn[next]==0&&vis[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,len);
              //递归的更新low,按照low的定义，它的父节点now,应该是儿子当做最小的，每次dfs出来后更新父节点now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
            low[now]=min(low[now],low[next]);
        }else{//排除，inSt[next]==0&&vis[next]==1，那就什么都不做
        }
    }
    if(dfn[now]==low[now]){//没更新过low,说明有强联通分量，以这个点为开始.那些点正好是栈顶的，那么从栈弹出元素直到弹出当前点now
        newCnt++;
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//把它更新成不在栈里；
            kind[k]=newCnt;
            kval[newCnt]+=dval[k];
        }while(k!=now);
    }
}

int n,m;
void getConnected(){
    int i,j,len;
    //memset(vis,0,sizeof(vis));
   // memset(dfn,0,sizeof(dfn));
    newCnt=0;
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            len=1;
            tarjan(i,len);
        }
    }
    g1.V=newCnt;
    for(i=1;i<=g.V;i++){//缩点入两个点属于不同联通分量就加边，当然这么做必然有重边
        for(j=g.head[i];j!=-1;j=g.edge[j].k){
            cint e=g.edge[j].e;
            if(kind[i]!=kind[e]){
                g1.push(kind[i],kind[e],1);
            }
        }
    }
}
int rem[MAX];
int dfs(cint now){
    if(rem[now]!=0){
        return rem[now];
    }
    rg int i,j,k,maxVal=0;
    for(i=g1.head[now];i!=-1;i=g1.edge[i].k){
        cint e=g1.edge[i].e;
        maxVal=max(maxVal,dfs(e));
    }
    rem[now]=max(rem[now],maxVal+kval[now]);
    return rem[now];
}
int main(int argc,char *argv[]){
	int i,u,v,a,b,maxVal;
	scanf("%d%d",&n,&m);
	g.clear();
	g1.clear();
    g.V=n;
    for(i=1;i<=n;i++){
        scanf("%d",&dval[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v,1);
    }
    getConnected();
    maxVal=-1;
    for(i=1;i<=g1.V;i++){
        dfs(i);
        maxVal=max(maxVal,rem[i]);
    }
    printf("%d\n",maxVal);
return 0;
}
