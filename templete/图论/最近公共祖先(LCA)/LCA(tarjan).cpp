#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;

struct Edge {
    int b,e,val;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
        this->val=0;
    }
};
vector<Edge>adList[MAX];//储存树,有向图
vector<Edge>li[MAX];//储存查询
int V,E;//V个点
bool lcavis[MAX];
int p[MAX];//当前节点的父节点是哪个,用了确定那个是根，因为根节点没有父节点

struct Union{
    int father[MAX];
    int rank[MAX];
    void init(int n){
        for(int i=0;i<n;i++){
            father[i]=i;
            rank[i]=1;
        }
    }
    int GetFather(int son) {
        if(father[son]!=son)
            father[son]=GetFather(father[son]);
        return father[son];
    }
    void merge(int x, int y){//普通合并，把y变成x的子树可能降低查询效率，但是可以控制根节点是哪个
        father[y]=x;
    }
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
void tarjan(int now,Union &un){//参数，now是当前到的点，un是一个并查集对象
    int i,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        tarjan(next,un);
        un.merge(now,next);//用普通连接江next连到now
        lcavis[next]=1;
    }
    for(i=0;i<li[now].size();i++){
        k=li[now][i].e;
        if(lcavis[k]){
            printf("(%d,%d)==%d\n",now,k,un.GetFather(k));//正常来说要求按照题目的输入顺序输出，存到li表的val值里即可
        }
    }
}

int main(int argc,char *argv[]){
    int i,j,k,n,m,T,b,e,root;
    Edge edge;
    cin>>T;
    while(T--){
        scanf("%d",&V);

        for(i=1;i<=V;i++){
            adList[i].clear();
            li[i].clear();
        }
        memset(lcavis,0,sizeof(lcavis));
        memset(p,0,sizeof(p));
        for(i=0;i<V-1;i++){
            scanf("%d%d",&b,&e);
            edge.sett(b,e);
            adList[b].push_back(edge);
            p[e]=b;
        }
        for(i=1;i<=V;i++){//寻找根节点
            if(p[i]==0){
                root=i;
                break;
            }
        }
        scanf("%d",&m);
        for(i=0;i<m;i++){
            scanf("%d%d",&b,&e);
            edge.sett(b,e);
            li[b].push_back(edge);
            edge.sett(e,b);
            li[e].push_back(edge);//记录查询的关联点对
        }
        un.init(V+1);
        tarjan(root,un);
    }
return 0;
}
/*
1
9
1 3
1 2
2 4
2 5
3 6
5 7
5 8
7 9
5
9 8
4 6
7 5
1 9
5 3
*/
