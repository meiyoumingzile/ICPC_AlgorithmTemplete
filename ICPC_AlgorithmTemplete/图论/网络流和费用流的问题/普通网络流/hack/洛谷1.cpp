// luogu-judger-enable-o2
#include<complex>
#include<cstdio>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e4+7,M=1e5+7;
struct node{
    int v,f,nxt;
}e[M<<1];
int n,m,s,t,Enum=1;
int front[N],cur[N],deep[N],num[N],pre[N];
int q[N];
char IN[1<<17],*A=IN,*B=IN;
inline char gc()
{
    if(A==B)
    {
        B=(A=IN)+fread(IN,1,1<<17,stdin);
        if(A==B)return EOF;
    }
    return *A++;
}
inline int qread()
{
    int x=0;
    char ch=gc();
    while(ch<'0' || ch>'9')ch=gc();
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=gc();}
    return x;
}
inline void Insert(int u,int v,int w)
{
    e[++Enum].v=v;e[Enum].f=w;e[Enum].nxt=front[u];front[u]=Enum;
    e[++Enum].v=u;e[Enum].nxt=front[v];front[v]=Enum;
}
void bfs(int t)
{
    for(int i=1;i<=n;i++)
        deep[i]=n;
    deep[t]=0;
    int head=1,tail=0,u,v;
    q[++tail]=t;
    while(head<=tail)
    {
        u=q[head++];
        for(int i=front[u];i;i=e[i].nxt)
        {
            v=e[i].v;
            if(deep[v]==n && e[i^1].f)
            {
                deep[v]=deep[u]+1;
                q[++tail]=v;
            }
        }
    }
}
int Augment(int s,int t)
{
    int flow=INF;
    for(int i=t;i!=s;i=e[pre[i]^1].v)
        flow=min(flow,e[pre[i]].f);
    for(int i=t;i!=s;i=e[pre[i]^1].v)
    {
        e[pre[i]].f-=flow;
        e[pre[i]^1].f+=flow;
    }
    return flow;
}
int ISAP(int s,int t)
{
    int x=s,maxflow=0;
    bfs(t);
    for(int i=1;i<=n;i++)
    {
        num[deep[i]]++;
        cur[i]=front[i];
    }
    while(deep[s]<n)
    {
        if(x==t)maxflow+=Augment(s,t),x=s;
        bool flag=0;
        for(int i=cur[x];i;i=e[i].nxt)
        {
            int v=e[i].v;
            if(deep[x]==deep[v]+1 && e[i].f)
            {
                flag=1;
                pre[v]=i;cur[x]=i;
                x=v;
                break;
            }
        }
        if(!flag)
        {
            int mins=n-1;
            for(int i=front[x];i;i=e[i].nxt)
                if(e[i].f)
                    mins=min(mins,deep[e[i].v]);
            num[deep[x]]--;
            if(!num[deep[x]])break;
            num[deep[x]=mins+1]++;
            cur[x]=front[x];
            if(x!=s)x=e[pre[x]^1].v;
        }
    }
    return maxflow;
}
int main()
{
    freopen("hack1.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("wa.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        Insert(u,v,w);
    }
    printf("%d\n",ISAP(s,t));
    return 0;
}
