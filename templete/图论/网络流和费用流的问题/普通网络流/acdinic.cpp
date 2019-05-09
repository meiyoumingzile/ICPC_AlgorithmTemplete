// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int ch_top=4e6;
char ch[ch_top],*now_r=ch-1;
#define c (*now_r)
#define gc (*++now_r)
int read()
{
    while(gc<'-');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc
#undef c

pii operator +(const pii &a,const pii &b)
{
    return pii(a.first+b.first,a.second+b.second);
}
typedef int Type;
const int N=1200+5,M=120000+5;
const Type inf=(1LL<<31)-1;
namespace MF
{
struct Edge
{
    int to,f,*nf;bool is_rev;
};
Edge qa[M*2],*nt[N],*t[N];
pii g[N];bool have[N];
int n,m,S,T;
bool bfs()
{
    rep(i,1,n){g[i]=pii(N,N);have[i]=0;}
    g[S]=pii(0,0);
    deque<int>q1,q2;
    q1.push_back(S);
    while(!q1.empty()||!q2.empty())
    {
        int x;
        if(!q1.empty()&&(q2.empty()||g[q1.front()]<g[q2.front()]))
        {
            x=q1.front();q1.pop_front();
        }
        else
        {
            x=q2.front();q2.pop_front();
        }
        if(x==T)return 1;
        if(have[x])continue;have[x]=1;
        for(auto i=t[x];i!=t[x+1];++i)
        if(i->f)
        {
            pii now=g[x]+pii(i->is_rev,1);
            int y=i->to;
            if(g[y]<=now)continue;
            g[y]=now;
            if(i->is_rev)q2.push_back(y);
            else q1.push_back(y);
        }
    }
    return 0;
}
int dfs(int x,int f)
{
    if(x==T)return f;
    int f0=f;
    for(auto &i=nt[x];i!=t[x+1];++i)
    if(i->f&&g[i->to]==g[x]+pii(i->is_rev,1))
    {
        int del=dfs(i->to,min(f,i->f));
        i->f-=del;//*i->nf+=del;
        if(!(f-=del))return f0;
    }
    g[x]=pii(N,N);
    return f0-f;
}
struct Edge0
{
    int x,y,f;
    int *dy1,*dy2,f0;
};
Edge0 e[M];
void init2()
{
    rep(i,1,m)
    {
        *e[i].dy2+=e[i].f0-*e[i].dy1;
        e[i].f0=*e[i].dy1=e[i].f-*e[i].dy2;
    }
}
Type qiu()
{
    Type ans=0;
    while(bfs())
    {
        do
        {
            memcpy(nt+1,t+1,n*sizeof(*t));
            ans+=dfs(S,inf);
        }while(bfs());
        init2();
    }
    return ans;
}
int cnt[N];
void init()
{
    n=read();m=read();S=read();T=read();
    rep(i,1,m)
    {
        e[i]=(Edge0){read(),read(),read()};
        ++cnt[e[i].x];++cnt[e[i].y];
    }
    t[1]=qa;
    rep(i,1,n)t[i+1]=t[i]+cnt[i];
    rep(i,1,m)
    {
        int x=e[i].x,y=e[i].y;
        --cnt[x];--cnt[y];
        t[x][cnt[x]]=(Edge){y,e[i].f,&((t[y]+cnt[y])->f),0};
        t[y][cnt[y]]=(Edge){x,0,&((t[x]+cnt[x])->f),1};
        e[i].dy1=&t[x][cnt[x]].f;
        e[i].dy2=&t[y][cnt[y]].f;
        e[i].f0=e[i].f;
    }
}
};


int main()
{
#ifdef kcz
    freopen("1.in","r",stdin);
#endif
    fread(ch,1,ch_top,stdin);
    MF::init();
    cout<<MF::qiu()<<endl;
}