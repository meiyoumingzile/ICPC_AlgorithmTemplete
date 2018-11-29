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
#define dd double
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=3010;
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
    int V1,V2,E,size;
    int head[2][MAX];
    Edge edge[2000010];
    Graphic(){
        clear();
    }
    inline void push(const int &b,const int &e,const int &val,int fp=0){
        int t=head[fp][b];
        head[fp][b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int vis[MAX],ytox[MAX],xtoy[MAX],dx[MAX],dy[MAX],DIS;
bool HC_search(){
    queue<int>que;
    DIS=INF;
    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    for(int i=1;i<=g.V1;i++){
        if(xtoy[i]==0){
            que.push(i);
            dx[i] = 1;
        }
    }
    while(!que.empty()){
        cint now=que.front();
        que.pop();
        if(dx[now]>DIS)
            break;
        for(int i=g.head[0][now];i!=-1;i=g.edge[i].k){
            cint next=g.edge[i].e;
            if(dy[next]==0) {
                dy[next]=dx[now] + 1;
                if(ytox[next]){
                    dx[ytox[next]]=dy[next]+1;
                    que.push(ytox[next]);
                }else{
                    DIS=dy[next];
                }
            }
        }
    }
    return DIS!=INF;
}
inline bool HC_dfs(int now){//找到一个最大匹配
    for(rg int i=g.head[0][now];i!=-1;i=g.edge[i].k){
        int next=g.edge[i].e;
        if(!vis[next]){
            vis[next]=1;
            if(ytox[next]&&dy[next]==DIS) continue;
            if(ytox[next]==0||HC_dfs(ytox[next])){
                ytox[next]=now;
                xtoy[now]=next;
                return true;
            }
        }
    }
    return false;
}

int HC(){
    rg int i,cnt=0;
    memset(xtoy,0,sizeof(xtoy));
    memset(ytox,0,sizeof(ytox));
    memset(vis,0,sizeof(vis));
    while(HC_search()){
        memset(vis,0,sizeof(vis));
        for(i=1;i<=g.V1;i++)
            if(xtoy[i]==0&&HC_dfs(i))
                cnt++;
    }
    return cnt;
}
int main(){
	rg int i,b,e,E,n,m,cnt=0;
	scanf("%d%d%d",&n,&m,&E);
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&e);
        if(b<=m&&e<=m){
            g.push(b,e,0,0);
        }
	}
	g.V1=n;
	g.V2=m;
	printf("%d\n",HC());
return 0;
}
