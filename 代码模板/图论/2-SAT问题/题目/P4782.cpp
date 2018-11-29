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
const int MAX=2000010;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
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
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*2];
    Graphic(){
        clear();
    }

    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;

bool vis[MAX];//����ǲ��Ǳ��ҹ���
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
bool inSt[MAX];//�Ƿ���ջ����
int kind[MAX];//ĳ���������ĸ���ͨ����
int newCnt=0;
void tarjan(int now,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        next=g.edge[i].e;
        if(dfn[next]==0&&vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,len);
              //�ݹ�ĸ���low,����low�Ķ��壬���ĸ��ڵ�now,Ӧ���Ƕ��ӵ�����С�ģ�ÿ��dfs��������¸��ڵ�now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
            low[now]=min(low[now],low[next]);
        }else{//�ų���inSt[next]==0&&vis[next]==1���Ǿ�ʲô������

        }
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        newCnt++;
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            kind[k]=newCnt;
        }while(k!=now);
    }
}

int n,m;
bool getConnected(){
    rg int i,len;
    //memset(vis,0,sizeof(vis));
   // memset(dfn,0,sizeof(dfn));
    newCnt=0;
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            len=1;
            tarjan(i,len);
        }
    }
    for(i=1;i<=g.V;i+=2){
        if(kind[i]==kind[i+1]){
            return 0;
        }
    }
    return 1;
}
int toID(cint a,cint id){
    return id*2-a;
}
int inverse(int x){
    x--;
    return 1+(x^1);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,u,v,a,b;
	scan(n);scan(m);
    g.V=n*2;
    for(i=0;i<m;i++){
        scan(u);scan(a);scan(v);scan(b);
        u=toID(a,u);//��Ű���<1,2> <3,4> <5,6>...������a��true,u��ȡu*2-1;��false,u��ȥu*2
        v=toID(b,v);
        g.push(u,inverse(v),1);
        g.push(v,inverse(u),1);
    }
    if(getConnected()){
        printf("POSSIBLE\n");
        printf("%d",kind[1]>kind[1+1]);
        for(i=3;i<=g.V;i+=2){
            printf(" %d",kind[i]>kind[i+1]);
        }printf("\n");
    }else{
        printf("IMPOSSIBLE\n");
    }
return 0;
}
/*
10 15
7 0 5 1
7 1 2 0
1 0 6 1
10 1 5 0
4 1 5 1
3 1 4 0
5 1 10 1
9 0 5 0
4 0 10 0
5 0 5 1
9 1 9 1
8 1 9 1
1 0 8 1
1 0 3 0
8 1 2 0
*/
