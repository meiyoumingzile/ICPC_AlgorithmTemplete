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
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
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
vector<Edge>adList[MAX];//储存树
vector<Edge>li[MAX];//储存查询
int V,E;//V个点
bool lcavis[MAX];
int p[MAX];//当前节点的父节点是哪个,用了确定那个是根，因为根节点没有父节点

struct Union{
    int *father;
    int *rank;
    Union(int n){//n代表人数；编号[0,n)
        init(n);
    }
    ~Union(){
        clear();
    }
    void init(int n){
        father=new int[n];
        rank=new int[n];
        for(int i=0;i<n;i++){
                father[i]=i;
                rank[i]=1;
        }
    }
    void clear(){
        delete []father;
        delete []rank;
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

void tarjan(int now,Union *un){//参数，now是当前到的点，un是一个并查集对象
    int i,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        tarjan(next,un);
        un->merge(now,next);//用普通连接江next连到now
        lcavis[next]=1;
    }
    for(i=0;i<li[now].size();i++){
        k=li[now][i].e;
        if(lcavis[k]){
            printf("%d\n",un->GetFather(k));
        }
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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

        scanf("%d%d",&b,&e);
        edge.sett(b,e);
        li[b].push_back(edge);
        edge.sett(e,b);
        li[e].push_back(edge);//记录查询的关联点对

        Union *un=new Union(V+1);
        tarjan(root,un);
        delete un;
    }
return 0;
}
/*
2
16
1 14
8 5
10 16
5 9
4 6
8 4
4 10
1 13
6 15
10 11
6 7
10 2
16 3
8 1
16 12
16 7
5
2 3
3 4
3 1
1 5
3 5
*/
