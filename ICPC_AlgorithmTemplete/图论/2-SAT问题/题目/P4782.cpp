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

bool vis[MAX];//标记是不是被找过了
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
stack<int>st;
bool inSt[MAX];//是否在栈里面
int kind[MAX];//某个点属于哪个联通分量
int newCnt=0;
void tarjan(int now,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        next=g.edge[i].e;
        if(dfn[next]==0&&vis[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,len);
              //递归的更新low,按照low的定义，它的父节点now,应该是儿子当做最小的，每次dfs出来后更新父节点now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
            low[now]=min(low[now],low[next]);
        }else{//排除，inSt[next]==0&&vis[next]==1，那就什么都不做

        }
    }
    if(dfn[now]==low[now]){//没更新过low,说明有强联通分量，以这个点为开始.那些点正好是栈顶的，那么从栈弹出元素直到弹出当前点now
        newCnt++;
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//把它更新成不在栈里；
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
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,u,v,a,b;
	scan(n);scan(m);
    g.V=n*2;
    for(i=0;i<m;i++){
        scan(u);scan(a);scan(v);scan(b);
        u=toID(a,u);//编号按照<1,2> <3,4> <5,6>...排所以a是true,u就取u*2-1;是false,u就去u*2
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
