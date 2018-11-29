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
const int MAX=1000010;
const int mod=1e9+7;
/*
�����3376Ϊ�������ݱȽ����⣬�������ݲ������໥����ıߣ��ڽӱ���Դ��淴��߱���Ż�����ʽǰ���ǿ�������������Ԫ�رߴ洢�෴�߷�ʽ�Ż���Ŀ��������o1ʱ���ҵ��෴�߶����ǵ���Ѱ�ҡ�
*/
struct Edge{
    int b,e,val,k;
    Edge(){}
    Edge(cint b,cint e,cint val,cint k){
        this->b=b;
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*5];
    Graphic(){
        clear();
    }
    void push(cint b,cint e,cint val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(b,e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
struct Dot{//bfs��
    int d,len;
    Dot(){}
    Dot(cint d,cint len){
        this->d=d;
        this->len=len;
    }
};

int layer[MAX],cur[MAX];//layer�Ƿֲ㣬cur��ǰ���Ż�
bool Dinic_bfs(Graphic &g){//�ֲ�,ֻ��Ҫ�ҵ�T�㼴��ֹͣ���Ҳ���T����false
    rg int i,minv=INF,b,e;
    queue<Dot>que;
    Dot now(g.S,0),next;
    memset(layer,-1,sizeof(layer));
    for(i=1;i<=g.V;i++)cur[i]=g.head[i];
    layer[g.S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.front();
        que.pop();
        if(now.d==g.T)
            return 1;
        for(i=g.head[now.d];i!=-1;i=g.edge[i].k){
            e=g.edge[i].e;
            if(layer[e]==-1&&g.edge[i].val>0){
                next.d=e;
                layer[e]=next.len=now.len+1;
                que.push(next);
            }
        }
    }
    return 0;
}
int Dinic_dfs(int now,Graphic &g,int minv){
    if(minv==0||now==g.T)
        return minv;
    int ans=0,val;
    for(int i=cur[now];i!=-1;i=g.edge[i].k){
        cur[now]=i;
        if(layer[g.edge[i].e]==layer[now]+1){
            val=Dinic_dfs(g.edge[i].e,g,min(minv,g.edge[i].val));
            if(val>0){
                ans+=val;
                minv-=val;
                g.edge[i].val-=val;
                g.edge[i^1].val+=val;
                if(minv<=0)
                    break;
            }
        }
    }
    return ans;
}
int s[MAX];
int Dinic(Graphic &g){
    int sumVal=0;
    while(Dinic_bfs(g)){//��ε���ֱ�����ֲܷ�
        int u = g.S, top = 0;
        while(1) {
            if(u == g.T) {
                int mini = INF, loc;
                for(int i = 0; i < top; i++) {
                    if(mini > g.edge[s[i]].val) {
                        mini = g.edge[s[i]].val;
                        loc = i;
                    }
				}
                for(int i = 0; i < top; i++) {
                    g.edge[s[i]].val-= mini;
                    g.edge[s[i]^1].val += mini;
                }
                sumVal += mini;
                top = loc;
                u = g.edge[s[top]].b;
            }
			int &i = cur[u];
            for(; ~i; i = g.edge[i].k) {
				int v = g.edge[i].e;
                if(g.edge[i].val && layer[v] == layer[u] + 1) break;
			}
            if(~i) {
                s[top++] = i;
                u = g.edge[i].val;
            }
            else {
                if(!top) break;
                layer[u] = -1;
                u = g.edge[s[--top]].b;
            }
        }
    }
    return sumVal;
}
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,b,e,v;
    scan(g.V);scan(g.E);scan(g.S);scan(g.T);
    for(i=0;i<g.E;i++){
        scan(b);scan(e);scan(v);
        g.push(b,e,v);
        g.push(e,b,0);
    }
    printf("%d\n",Dinic(g));
return 0;
}
