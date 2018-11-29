#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct Edge{//边，这里只存了终止点
    int b=0,e=0;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
    }
};

vector<Edge>adList[MAX];
int V,E,cutEdgeCnt;//V代表多少个点，E代表多少条边
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
bool vis[MAX];
stack<Edge>st;//用来找边双联通分量
void popStack(stack<Edge> &st,Edge tar){//出栈直到边等于tar,输出边双联通分量的边集合
    Edge now;
    int len=0;
    while(!st.empty()){
        now=st.top();
        st.pop();
        len++;
        if(tar.b!=now.b||tar.e!=now.e)
            printf("(%d %d) ",now.b,now.e);
        else
            break;
    }
    printf("\n");
}
void tarjan(int now,int p,int &len){//递归代码，now从任意[1,V]开始都可以，但要注意可能不会被都走到，p代表搜索树的父节点初始化是-1，len代表深度
    int i,j,k,next;
    dfn[now]=low[now]=len++;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(vis[next]==0){//把dfn当做dfs的vis数组判断走没走过
            st.push(adList[now][i]);
            tarjan(next,now,len);
            low[now]=min(low[now],low[next]);
            if(dfn[now]<low[next]){
                cutEdgeCnt++;
                popStack(st,adList[now][i]);
            }
         }else if(dfn[next] < dfn[now]&&next!=p){//树是有向的，但原图是无向图，要检测是不是父节点,不能更新父节点
             //如果next访问过了，那么也至少更新当节点now的low是自己和dfn[next]最小c
            // 且对于无向图应该只对dfn小于now的next操作，因为较大的没有意义
            st.push(adList[now][i]);
            low[now]=min(low[now],dfn[next]);
        }
    }
}

int getCutEdge(){
    int len,i,j;
    memset(vis,0,sizeof(vis));
    cutEdgeCnt=0;//割点初始化
    Edge edge;//初始化一个不存在的边用来找边双联通分量的边集合
    for(i=1;i<=V;i++){
        if(vis[i]==0){
            len=1;//初始化访问顺序
            tarjan(i,-1,len);
            popStack(st,edge);
        }
    }
    return cutEdgeCnt;
}

int main(int argc,char *argv[]){
    int i,j,k,b,e;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&e);
        edge.sett(b,e);
        adList[b].push_back(edge);//无向图
        edge.sett(e,b);
        adList[e].push_back(edge);//无向图
    }
    //图可能是不连通的，应该多次判断知道所有点都被走过tarjan为止。这样才能找到每一块的割点，具体看题了
    printf("%d\n",getCutEdge());
return 0;
}
/*
7 9
1 2
2 3
3 4
4 5
3 5
2 4
6 7
1 6
1 7
*/
