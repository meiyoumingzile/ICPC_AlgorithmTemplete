#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=19260817;
inline void scan(int &x){
    char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

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
    int V,E,S,T,size;
    int head[MAX];
    Edge edge[MAX*4];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void println(){
        int i,j,next;
        for(i=1;i<=V;i++){
            printf("%d:::",i);
            for(j=head[i];j!=-1;j=edge[j].k){
                printf("%d ",edge[j].e);
            }printf("\n");
        }
    }
};
Graphic g,g1;

bool vis[MAX],inSt[MAX];//����ǲ��Ǳ��ҹ���,inSt�Ƿ���ջ����
int dfn[MAX],low[MAX],kind[MAX],kind_cnt[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��,kind[i]ĳ���������ĸ���ͨ����
stack<int>st;
int newCnt=0;
void tarjan(int now,int &len,int p){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        next=g.edge[i].e;
        if(next!=p){
            if(dfn[next]==0&&vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
                tarjan(next,len,now);
                  //�ݹ�ĸ���low,����low�Ķ��壬���ĸ��ڵ�now,Ӧ���Ƕ��ӵ�����С�ģ�ÿ��dfs��������¸��ڵ�now
                low[now]=min(low[now],low[next]);
            }else if(inSt[next]==1){
                low[now]=min(low[now],low[next]);
            }else{//�ų���inSt[next]==0&&vis[next]==1���Ǿ�ʲô������
            }
        }
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        newCnt++;
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            kind[k]=newCnt;
            kind_cnt[newCnt]++;
        }while(k!=now);
    }
}

int n,m;
void getConnected(){
    int i,j,len;
    //memset(vis,0,sizeof(vis));
   // memset(dfn,0,sizeof(dfn));
    newCnt=0;
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            len=1;
            tarjan(i,len,-1);
        }
    }
    g1.V=newCnt;
    for(i=1;i<=g.V;i++){//���������������ڲ�ͬ��ͨ�����ͼӱߣ���Ȼ��ô����Ȼ���ر�
        for(j=g.head[i];j!=-1;j=g.edge[j].k){
            cint e=g.edge[j].e;
            if(kind[i]!=kind[e]){
                g1.push(kind[i],kind[e],1);
            }
        }
    }
   // g1.println();
}
ll dp[MAX],ANS=0;
void dfsG(const Graphic &g,int now,int p){
    dp[now]=kind_cnt[now]>2;
    ll ans=0,sum=0;
    for(int j=g.head[now];j!=-1;j=g.edge[j].k){
        cint e=g.edge[j].e;
        if(e!=p){
            dfsG(g,e,now);
            ans=(ans+sum*dp[e]%mod)%mod;
            sum=(sum+dp[e])%mod;
            dp[now]=(dp[now]+(kind_cnt[now]>2?dp[e]*2%mod:dp[e]))%mod;
        }
    }
    ANS=(ANS+(kind_cnt[now]>2?(ans*2%mod+sum)%mod:ans))%mod;
}

int main(int argc,char *argv[]){
	int i,u,v,a,b;
	scan(n);scan(m);
	g.clear();
	g1.clear();
    g.V=n;
    for(i=0;i<m;i++){
        scan(u);scan(v);
        g.push(u,v,1);
        g.push(v,u,1);
    }
    getConnected();
    dfsG(g1,1,-1);

    printf("%lld\n",ANS);
return 0;
}
/*
4 5
1 2
2 3
3 1
1 4
3 4
*/
