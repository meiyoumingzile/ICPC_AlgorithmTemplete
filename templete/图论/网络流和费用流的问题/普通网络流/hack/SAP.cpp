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
const int INF=2147483647;////2139062143
const int MAX=10010;
const int mod=1e9+7;
/*
以洛谷3376为例，数据满足链式前向星实现
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
struct Graphic{//链式前向星实现
    int V,E,S,T;//点数边数，起点终点
    int size;
    int head[MAX];
    Edge edge[250010];
    Graphic(){}
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void fpush(const int &b,const int &e,const int &val){
        push(b,e,val);
        push(e,b,0);
    }
};
Graphic g;
Edge p[MAX];//储存路径，p[i]代表上个节点
int layer[MAX],gap[MAX],cur[MAX];//cur是当前弧优化
void SAP_bfs(Graphic &g){//按照逆向分层，
    queue<int>que;
    int now=g.T;
    memset(layer,-1,sizeof(layer));
    memset(gap,0,sizeof(gap));
    layer[g.T]=0;
    que.push(now);
    gap[0]++;
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(int i=g.head[now];i!=-1;i=g.edge[i].k){
            int e=g.edge[i].e;
            if(layer[e]==-1&&g.edge[i].val==0){
                layer[e]=layer[now]+1;
                gap[layer[e]]++;
                que.push(e);
            }
        }
    }
}

ll SAP(){//dfs寻找路径，load储存的是路径，load[i].b是起点，e代表这条边在邻接表中编号。
    int i,j,k,u,v,now,next,minVal;
    ll sumVal=0;
    SAP_bfs(g);
    for(i=1;i<=g.V;i++)
        cur[i]=g.head[i];//当前满足d[i] = d[j] + 1的边的为第一条边
    now=g.S;
    p[g.S].e=g.S;
    while(layer[g.S]<g.V){//某个点层数被更新的大于等于总点数，说明一定出现了断层，退出循环
        for(i=cur[now];i!=-1;i=g.edge[i].k){//遍历看看有没有可以走的
            next=g.edge[i].e;
            if(g.edge[i].val>0&&layer[now]==layer[next]+1){
                break;
            }
        }
        if(i!=-1){//找到一条可以走的路
            p[next].e=now;
            p[next].k=i;
            now=next;
            if(now==g.T){
                for(v=g.T,minVal=INF;v!=g.S;v=u){
                    u=p[v].e;
                    minVal=min(minVal,g.edge[p[v].k].val);
                }
                sumVal+=minVal;
                for(v=g.T;v!=g.S;v=u){
                    /*
                    printf("%d ",v);//此处得到路径
                    */
                    u=p[v].e;
                    k=p[v].k;
                    g.edge[k].val-=minVal;
                    g.edge[k^1].val+=minVal;
                }//printf("%d\n",v);//此处得到路径
                now=g.S;

            }
        }else{
            minVal=g.V;
            cur[now]=g.head[now];
            for(i=g.head[now];i!=-1;i=g.edge[i].k){//寻找一条最小的边
                next=g.edge[i].e;
                if(g.edge[i].val>0&&layer[next]<minVal&&layer[next]!=-1)
                    minVal=layer[next];
            }
            if(--gap[layer[now]]==0)//找不到可改变的或者出现断层
                break;
            layer[now]=minVal+1;
            gap[layer[now]]++;
            now=p[now].e;//退出一层
        }
    }
    return sumVal;//返回找到的可行的方案权值总和，没有自然就是0
}
char c;
void scan(int &x){
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
    //freopen("hack1.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("wa.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,b,e,val;
	while(~scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T)){
	    g.clear();
        for(i=0;i<g.E;i++){
            scan(b);scan(e);scan(val);
            g.push(b,e,val);
            g.push(e,b,0);
        }
        printf("%lld\n",SAP());
	}
return 0;
}

