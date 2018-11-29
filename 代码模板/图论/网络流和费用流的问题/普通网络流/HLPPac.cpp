// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define MAXN 13000
#define N 250000
using namespace std;
const int inf=(1<<29);
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x)
{
    int s=0,w=1;
    char c=nc();
    while(!isdigit(c)){if(c=='-')w=-1;c=nc();}
    while(isdigit(c)){s=(s<<3)+(s<<1)+c-'0';c=nc();}
    x=s*w;
}
inline void write(int x)
{
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
template <class T,int max_size,bool compare(const T &a,const T &b)>class Heap
{
private:
  T heap[max_size];
  int heap_size;
  inline void swap(T &a,T &b)
  {
    T temp=a;
    a=b,b=temp;
  }
  void up(int now)
  {
    if(now==1)return ;
    int nxxt=now>>1;
    T temp=heap[now];
    while(compare(temp,heap[nxxt])&&now>1)
    {
        heap[now]=heap[nxxt];
        now=nxxt,nxxt>>=1;
    }
    heap[now]=temp;
  }
  void down(int now)
  {
    int nxxt=now<<1;
    T temp=heap[now];
    while(nxxt<=heap_size)
    {
        if(nxxt<heap_size&&compare(heap[nxxt+1],heap[nxxt]))
        nxxt++;
        if(compare(temp,heap[nxxt]))break;
        else
        {
            heap[now]=heap[nxxt];
            now=nxxt,nxxt<<=1;
        }
    }
    heap[now]=temp;
  }
public:
  Heap()
  {
    heap_size=0;
  }
  inline void push(T a)
  {
      heap[++heap_size]=a;
      up(heap_size);
  }
  inline void pop()
  {
    heap[1]=heap[heap_size--];
    down(1);
  }
  inline T top(){return heap[1];}
  inline T pop_out()
  {
    T temp=heap[1];
    heap[1]=heap[heap_size--];
    down(1);
    return temp;
  }
  inline void clear(){heap_size=0;}
  inline bool empty(){return !heap_size;}
  inline int size(){return heap_size;}
};
struct edge
{
    int to,nxxt,flow;
}e[N];
struct data
{
    int pos,h;
    data(int x=0,int y=0){pos=x,h=y;}
}t[MAXN];
inline bool cmp(const data &a,const data &b)
{
    return a.h>b.h;
}
int head[MAXN],cnt=-1,n,H[MAXN],F[MAXN],Gap[MAXN],m,ss,tt;
inline void add(int x,int y,int w)
{
    e[++cnt].to=y;
    e[cnt].nxxt=head[x];
    e[cnt].flow=w;
    head[x]=cnt;
}
Heap<data,MAXN,cmp>Q;
inline int HLPP(int S,int T)
{
    H[S]=n,F[S]=inf;
    Q.push(data(S,H[S]));
    while(!Q.empty())
    {
        int now=Q.top().pos;
        Q.pop();
        if(!F[now])continue;
        register int i;
        for(i=head[now];~i;i=e[i].nxxt)
        {
            if(now==S||H[e[i].to]+1==H[now])
            {
                int flow=min(F[now],e[i].flow);
                e[i].flow-=flow,e[i^1].flow+=flow;
                F[now]-=flow,F[e[i].to]+=flow;
                if(e[i].to^T&&e[i].to^S&&flow)
                Q.push(data(e[i].to,H[e[i].to]));
            }
        }
        if(now^S&&now^T&&F[now])
        {
            if(!(--Gap[H[now]]))
            {
                for(i=1;i<=n;i++)
                if(H[now]<H[i]&&H[i]<=n&&now^S&&now^T)H[i]=n+1;
            }
            ++Gap[++H[now]];
            Q.push(data(now,H[now]));
        }
    }
    return F[T];
}
int main()
{
    memset(head,-1,sizeof(head));
    read(n),read(m),read(ss),read(tt);
    for(register int i=1;i<=m;i++)
    {
        int u,v,w;
        read(u),read(v),read(w);
        add(u,v,w),add(v,u,0);
    }
    write(HLPP(ss,tt)),putchar(10);
}
