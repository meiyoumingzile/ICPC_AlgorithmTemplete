#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=5001;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

struct Edge{
    int b,e,val;
};
struct Graphic{//边集数组即可
    int V,E,S,T,size;
    Edge edge[400010];
    void push(const int &b,const int &e,const int &val){
        edge[size].b=b;
        edge[size].e=e;
        edge[size++].val=val;
    }
	void clear(){
        size=0;
    }
};
Graphic g;
struct Union{
    int father[MAX];
    int rank[MAX];
    void init(int n){//初始化
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
    void insMerge(int x, int y) {
        int fx=GetFather(x);
        int fy=GetFather(y);
        if(fx==fy) return;
        if(rank[fx]>rank[fy]){
            father[fy]=fx;
            rank[fx]+=rank[fy];
        }else{
            father[fx] = fy;
            rank[fy]+=rank[fx];
        }
    }
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
int MST_kruskal(){//范围是int,如果longlong就要改变最大值INF,必须是联通图
    rg int i,k,b,ans=0,minval;
    un.init(g.V+1);
    sort(g.edge,g.edge+g.size,[](const Edge &a,const Edge &b){
         return a.val<b.val;
         });
    for(i=0;i<g.size;i++){
        if(!un.isSameSet(g.edge[i].b,g.edge[i].e)){
            ans+=g.edge[i].val;
            un.insMerge(g.edge[i].b,g.edge[i].e);
        }
    }
    return ans;
}

int main(int argc,char *argv[]){
    int i,j,k,u,v,val,ans;
    while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){//要判断重复边，自环不用考虑
            scan(u);
            scan(v);
            scan(val);
            g.push(u,v,val);
        }
        ans=MST_kruskal();
        printf("%d\n",ans);
    }
return 0;
}
